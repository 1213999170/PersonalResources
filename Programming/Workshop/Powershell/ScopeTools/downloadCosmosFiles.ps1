param(
    [string] $listTableFile = "downloadCosmosFileList.csv"
)

. "$PSScriptRoot\Lib\variables.ps1"
. "$PSScriptRoot\Lib\functions.ps1"

foreach ($line in Get-Content $listTableFile) {
    if (!$line) 
    {
        continue;
    }
    
    $cosmosFile, $localFile = $line.Split(',');
    $ret_print = DownloadCosmosFile($cosmosFile, $localFile);
    Write-Output $ret_print
}

