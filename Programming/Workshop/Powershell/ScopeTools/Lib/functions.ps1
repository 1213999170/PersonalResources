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

<#
    scope:  path / file name handling
#>
function GetFileNameWithoutExt([string] $fullFilePath) {
    if ($fullFilePath.Contains("\")) {
        if ($fullFilePath.Contains(".")) {
            return $fullFilePath.split("\")[-1].split(".")[0];
        }else {
            return $fullFilePath.split("\")[-1];
        }
    }else {
        if ($fullFilePath.Contains(".")) {
            return $fullFilePath.split(".")[0];
        }else {
            return $fullFilePath;
        }
    }
}

function GetFileName([string] $fullFilePath) {
    if ($fullFilePath.Contains("\")) {
        return $fullFilePath.split("\")[-1];
    }else {
        return $fullFilePath;
    }
}

<#
    scope:  cosmos file upload / download
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
    return ProcessCommand($CommandStr)
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
