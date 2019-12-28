param(
    [string] $CosmosUrl = "https://cosmos08.osdinfra.net/cosmos/adCenter.BICore.prod2/local/prod/FastBIAdl/output/CFR/2019/12/04/",

    [timespan] $TimeSpan = "60.00:00:00"
)

Import-Module "$PSScriptRoot\Lib\variables.psm1"
Import-Module "$PSScriptRoot\Lib\functions.psm1"

LoadVcClient

$simpleStreamInfo = GetSimpleStreamInfoByUrl $CosmosUrl

if (-not $simpleStreamInfo) {
    Write-Error "Failed to get stream info of given CosmosUrl $CosmosUrl" -ErrorAction Stop
}

SetCosmosStreamExpiry $simpleStreamInfo $TimeSpan