param(
    [string] $listTableFile = "downloadCosmosFileList.csv", 
    [string] $localPath = "D:\01_Downloads\Temp\realtimebudgetingreport"
)

. "$PSScriptRoot\Lib\variables.ps1"
. "$PSScriptRoot\Lib\functions.ps1"

foreach ($line in Get-Content $listTableFile) {
    if (!$line) 
    {
        continue;
    }

    $filename = $line.Split("/")[-1];
    $localFile = "$localPath\$filename";
    
    $ret_print = DownloadCosmosFile($line, $localFile);
    Write-Output $ret_print
}

