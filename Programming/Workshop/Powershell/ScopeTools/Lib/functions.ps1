. "$PSScriptRoot\variables.ps1"

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
    if ($Global:SparsePrintInfo_count % $interval -eq 0) {
        Write-Output $Global:SparsePrintInfo_count
        PrintInfo $logStr
    }
    $Global:SparsePrintInfo_count += 1
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
    scope:  cosmos file process
#>
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

function ExtractVC([string] $cosmosFile) {
    foreach ($VCName in $VCMap.Values) {
        if ($cosmosFile.StartsWith($VCName)) {
            return $VCName
        }
    }
    return ""
}
