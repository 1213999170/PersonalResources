<#
    Module: functions
    Usage :
#>

Import-Module "$PSScriptRoot\variables.psm1"
<#
    cmd:  process command
#>
function ProcessCommand([string] $commandStr) {
    $date = Get-Date
    Add-Content $CommandHistoryFile "[$date]:   $CommandStr"

    Write-Output $CommandStr;
    if ($TestMode)
    {
        return "";
    }

    $ret = (cmd /c ($CommandStr))
    Add-Content $CommandPrintHistoryFile $ret

    return $ret;
}

function PrintInfo($logStr) {
    Add-Content $PrintHistoryFile $logStr
    Write-Output $logStr
}

$SparsePrintInfo_count = 0
function SparsePrintInfo([string] $logStr, [int] $interval = 100) {
    if ($Script:SparsePrintInfo_count % $interval -eq 0) {
        Write-Output $Script:SparsePrintInfo_count
        PrintInfo $logStr
    }
    $Script:SparsePrintInfo_count += 1
}

function Assert-Statement([bool]$Statement, [string]$Description="") {
    if (!$Statement) {
        throw "Assert failed: $Description."
    }
}

# MatchParams $Param1 $Param2 ([ref]$ScriptPath) ([ref]$VCDescr) "script"
function MatchParams([string] $Param1, [string] $Param2, [ref] $ParamA, [ref] $ParamB, [string] $PatternA) {
    if ([string]::IsNullOrEmpty($Param1)) {
        return;
    }
    if ([string]::IsNullOrEmpty($Param2)) {
        if ($Param1.Contains($PatternA)) {
            $ParamA.Value = $Param1
        }else {
            $ParamB.Value = $Param1
        }
    }else {
        if ($Param1.Contains($PatternA)) {
            $ParamA.Value = $Param1
            $ParamB.Value = $Param2
        }else {
            $ParamA.Value = $Param2
            $ParamB.Value = $Param1
        }
    }
}

<#
    scope:  path / file name handling
#>
function Inline_SplitDelimiter([string] $path, [string] $delimiter, [int] $index = -1) {
    if ($path.Contains($delimiter)) {
        return $path.Split($delimiter)[$index]
    }
    return $path
}

function GetFileName([string] $fullFilePath) {
    $copyFullFilePath = $fullFilePath
    foreach ($pathDelimiter in $PathDelimiters) {
        $copyFullFilePath = Inline_SplitDelimiter $copyFullFilePath $pathDelimiter
    }
    return $copyFullFilePath
}

function GetFileNameWithoutExt([string] $fullFilePath) {
    $copyFullFilePath = GetFileName $fullFilePath
    return Inline_SplitDelimiter $copyFullFilePath $ExtDelimiter 0
}

function GetPath([string] $fullFilePath) {
    $index = -1
    foreach ($pathDelimiter in $PathDelimiters) {
        $id = $fullFilePath.LastIndexOf($pathDelimiter)
        if ($id -gt $index) {
            $index = $id
        }
    }
    if ($index -eq -1) {
        return "."
    }
    return $fullFilePath.Substring(0, $index)
}

function PathJoin($paths, [string] $pathDelimiter) {
    if ($paths.Length -lt 0) {
        return
    }

    $fullPath = $paths[0]
    for ($i = 1; $i -lt $paths.Length; $i++) {
        $element = $paths[$i]
        $fullPath = "$fullPath$pathDelimiter$element"
    }
    return $fullPath
}

function RemoveHead([string] $targetString, [string] $matchString) {
    if ($targetString.StartsWith($matchString)) {
        return $targetString.Substring($matchString.Length)
    }
    return $targetString
}

function RemoveEnd([string] $targetString, [string] $matchString) {
    if ($targetString.EndsWith($matchString)) {
        return $targetString.Substring(0, $targetString.Length - $matchString.Length)
    }
    return $targetString
}

function CheckExist([string] $path) {
    if (-not (Test-Path $path)) {
        Write-Error "Can't find path or file: $path"
        exit 1;
    }
}

<#
    scope: cache
#>
function SaveVariable([string] $key, $variable) {
    $variableXml = "$ScopeToolsRoot\Cache\variable_$key.xml"
    $variable | Export-Clixml $variableXml
}

function RestoreVariable([string] $key) {
    throw "not implemented"

    $variableXml = "$ScopeToolsRoot\Cache\variable_$key.xml"
    if (-not (Test-Path $variableXml)) {
        Write-Error "Can't find the cache xml for $key" -ErrorAction Stop
    }
    $variable = Import-Clixml $variableXml

    # Check if this is a internal class
    if ($key.Contains("SimpleStreamInfo")) {
        $variable = [SimpleStreamInfo]::reserialize($variable)
    }

    return $variable
}

<#
    scope:  cosmos process
#>
function LoadVcClient() {
    if ($script:VcClientLoaded) {
        return
    }
    
    Write-Host "Loading VcClient"
    [void][System.Reflection.Assembly]::LoadFile($VcClientDll);
    $script:VcClientLoaded = $true
}

class SimpleStreamInfo {
    [bool]     $IsDirectory
    [string]   $Url
    [datetime] $ExpireTime
    [bool]     $IsComplete
    [System.Collections.Generic.List[SimpleStreamInfo]] $SubStreamInfos

    SimpleStreamInfo () {
    }

    SimpleStreamInfo ([bool] $isDir, [string] $link, [datetime] $expire, [bool] $iscomp) {
        $this.IsDirectory = $isDir
        $this.Url = $link
        if ($this.IsDirectory) {
            $this.ExpireTime = [datetime]::MaxValue
        }else {
            $this.ExpireTime = $expire
        }
        $this.IsComplete = $iscomp
    }

    [void] AddSubStreamInfo([SimpleStreamInfo] $subStreamInfo) {
        if (-not $this.IsDirectory) {
            Write-Error "Trying to add subStreamInfo to non-directory $($this.Url) whose IsDirectory is $($this.IsDirectory)" -ErrorAction Stop
        }
        if (-not $subStreamInfo) {
            Write-Warning "Trying to add null subStreamInfo"
        }
        if ($this.SubStreamInfos -eq $null) {
            $this.SubStreamInfos = [System.Collections.Generic.List[SimpleStreamInfo]]::New()
        }
        $this.SubStreamInfos.Add($subStreamInfo)
    }

    [int] GetStreamsNumber() {
        if (-not $this.IsDirectory) {
            return 1
        }
        if (-not $this.SubStreamInfos) {
            return 0
        }

        [int] $num = 0
        foreach ($sub in $this.SubStreamInfos) {
            $num += $sub.GetStreamsNumber()
        }
        return $num
    }
}

function GetCosmosUrlType([string] $CosmosUrl) {
    if ([VcClient.VC]::DirectoryExists($CosmosUrl)) {
        return "Directory"
    }
    if ([VcClient.VC]::StreamExists($CosmosUrl)) {
        return "File"
    }
    return "Invalid"
}

function GetSimpleStreamInfo([string] $CosmosFile) {
    Write-Host "[minzhe][GetSimpleStreamInfo]: $CosmosFile"
    $streamInfo = [VcClient.VC]::GetStreamInfo($CosmosFile, $true)
    [SimpleStreamInfo] $simpleStreamInfo = [SimpleStreamInfo]::New($streamInfo.IsDirectory, $streamInfo.StreamName, $streamInfo.ExpireTime, $streamInfo.IsComplete)
    return $simpleStreamInfo
}

function GetSimpleStreamInfoByDirectory([string] $CosmosDirectory) {
    Write-Host "[minzhe][GetSimpleStreamInfoByDirectory]: $CosmosDirectory"
    [SimpleStreamInfo] $simpleStreamInfo = [SimpleStreamInfo]::New($true, $CosmosDirectory, [datetime]::MaxValue, $true)

    $streamInfos = [VcClient.VC]::GetDirectoryInfo($CosmosDirectory, $true)
    foreach ($streamInfo in $streamInfos) {
        if ($streamInfo.IsDirectory) {
            [SimpleStreamInfo] $subSimpleStreamInfo = GetSimpleStreamInfoByDirectory $streamInfo.StreamName
        } else {
            [SimpleStreamInfo] $subSimpleStreamInfo = [SimpleStreamInfo]::New($streamInfo.IsDirectory, $streamInfo.StreamName, $streamInfo.ExpireTime, $streamInfo.IsComplete)
        }
        $simpleStreamInfo.AddSubStreamInfo($subSimpleStreamInfo)
    }

    return $simpleStreamInfo
}

function GetSimpleStreamInfoByUrl([string] $CosmosUrl) {
    Write-Host "[minzhe][GetSimpleStreamInfoByUrl]: $CosmosUrl"
    $UrlType = GetCosmosUrlType $CosmosUrl
    
    if ($UrlType -eq "Invalid") {
        Write-Error "Invalid UrlType or the CosmosUrl $CosmosUrl does not exist" -ErrorAction Stop
    }

    if ($UrlType -eq "File") {
        $simpleStreamInfo = GetSimpleStreamInfo $CosmosUrl
    } else {
        $simpleStreamInfo = GetSimpleStreamInfoByDirectory $CosmosUrl
    }

    return $simpleStreamInfo
}

function DownloadCosmosFile([string] $cosmosfile, [string] $localPath, [bool] $isBinary = $false) {
    if ($isBinary)
    {
        $CommandStr = "$ScopeExe copy $cosmosFile $localPath -binary"
    }
    else
    {
        $CommandStr = "$ScopeExe copy $cosmosFile $localPath -text"
    }
    return ProcessCommand $CommandStr
}

<# function DownloadCosmosFileList([string] $listTableFile, [string] $localPath) {
	foreach ($line in Get-Content $listTableFile) {
        if ($line.IsNullOrEmpty()) 
        {
            continue;
        }
        
        $file = GetFileName($line);

	}
} #>

function SetCosmosFileExpiry([SimpleStreamInfo] $SimpleStreamInfo, [timespan]$TimeSpan) {
    if ($SimpleStreamInfo.IsDirectory) {
        Write-Error "Error in calling SetCosmosFileExpiry with directory url: $($SimpleStreamInfo.Url)" -ErrorAction Stop
    }

    if (-not $SimpleStreamInfo.IsComplete) {
        Write-Warning "The cosmos file $($SimpleStreamInfo.Url) is not completed" -ErrorAction return
    }

    if ($SimpleStreamInfo.ExpireTime -ge [datetime]::Now.Add($TimeSpan)) {
        return
    }

    Write-Host "Setting expiry for $($SimpleStreamInfo.Url) with $TimeSpan"
    [VcClient.VC]::SetStreamExpirationTime($SimpleStreamInfo.Url, $TimeSpan)
}

function SetCosmosStreamExpiry([SimpleStreamInfo] $SimpleStreamInfo, [timespan]$TimeSpan) {
    if (-not $SimpleStreamInfo.IsDirectory) {
        SetCosmosFileExpiry $SimpleStreamInfo $TimeSpan
    }

    foreach ($subSimpleStreamInfo in $SimpleStreamInfo.SubStreamInfos) {
        SetCosmosStreamExpiry $subSimpleStreamInfo $TimeSpan
    }
}

function ExtractVC([string] $cosmosFile) {
    foreach ($VCName in $VCMap.Values) {
        if ($cosmosFile.StartsWith($VCName)) {
            return $VCName
        }
    }
    return ""
}

$ExportFunctions = (
    "ProcessCommand",
    "PrintInfo",
    "SparsePrintInfo",
    "Assert-Statement",
    "MatchParams",
    "GetFileName",
    "GetFileNameWithoutExt",
    "GetPath",
    "PathJoin",
    "RemoveHead",
    "RemoveEnd",
    "CheckExist",
    "SaveVariable",
    "RestoreVariable",
    "LoadVcClient",
    "GetSimpleStreamInfo",
    "GetSimpleStreamInfoByDirectory",
    "GetSimpleStreamInfoByUrl",
    "DownloadCosmosFile",
    "SetCosmosStreamExpiry",
    "ExtractVC"
)

Export-ModuleMember -Function $ExportFunctions