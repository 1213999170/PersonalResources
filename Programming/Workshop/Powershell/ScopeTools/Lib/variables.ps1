<#
    name:   variables.ps1
    usage:  store some useful constant variables.
#>
$TestMode = $false

$VCMap = @{
    "11prod" = "https://cosmos11.osdinfra.net/cosmos/adCenter.BICore.prod2/"; 
    "11twp"  = "https://cosmos11.osdinfra.net/cosmos/sharedData.Ads.Dev/"; 
    "08prod" = "https://cosmos08.osdinfra.net/cosmos/adCenter.BICore.prod2/"; 
    "08twp"  = "https://cosmos08.osdinfra.net/cosmos/sharedData.Ads.Dev/"
}

function GetVC([string]$VCDescr) {
    $VCDescr = $VCDescr.ToLower();
    if ($VCDescr.Contains("11")) {
        if ($VCDescr.Contains("pr")) {
            return $VCMap["11prod"];
        }
        else {
            return $VCMap["11twp"];
        }
    }
    else {
        if ($VCDescr.Contains("pr")) {
            return $VCMap["08prod"];
        }
        else {
            return $VCMap["08twp"];
        }
    }
}


<#
    Local paths
#>
$ScopeRoot = "D:\Repos\Ads.BI.SubjectAreas\target\distrib\debug\amd64\Autopilot\ScopeSDK"
$VSScopeRoot = """C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\IDE\Extensions\Microsoft\ScopeStudio\2.5.0000.4\CosmosRuntimeSDK"""
$ScopeExe = "$ScopeRoot\Scope.exe"

$CommandHistoryFile = "F:\PersonalResources\Programming\Workshop\Powershell\ScopeTools\History\Commands.txt"
$CommandPrintHistoryFile = "F:\PersonalResources\Programming\Workshop\Powershell\ScopeTools\History\CommandPrints.txt"
$PrintHistoryFile = "F:\PersonalResources\Programming\Workshop\Powershell\ScopeTools\History\Prints.txt"

$CookiesFile = "F:\PersonalResources\Programming\Workshop\Powershell\ScopeTools\Cookies\cookies.json"

<#
    System config
#>
$PathDelimiters = "/", "\"
$ExtDelimiter = "."

$UserName = $env:UserName
$UserDomain = $env:UserDomain
$ComputerName = $env:ComputerName

<#
    Cache
#>
$CacheScopeScript = ".\Cache\script.scope"