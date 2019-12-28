param(
    [string] $listTableFile = ".\Data\downloadCosmosFileList.csv"
)

Import-Module "$PSScriptRoot\Lib\variables.psm1"
Import-Module "$PSScriptRoot\Lib\functions.psm1"

foreach ($line in Get-Content $listTableFile) {
    if (!$line) 
    {
        continue;
    }
    
    $cosmosFile, $localFile = $line.Split(',');
    $ret_print = DownloadCosmosFile $cosmosFile $localFile
    Write-Output $ret_print
}

