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

$ScopeRoot = "D:\Repos\Ads.BI.SubjectAreas\target\distrib\debug\amd64\Autopilot\ScopeSDK";
$ScopeExe = "$ScopeRoot\Scope.exe";

$CommandHistoryFile = "F:\PersonalResources\Programming\Workshop\Powershell\ScopeTools\History\Commands.txt";
$CommandPrintHistoryFile = "F:\PersonalResources\Programming\Workshop\Powershell\ScopeTools\History\CommandPrints.txt";
$PrintHistoryFile = "F:\PersonalResources\Programming\Workshop\Powershell\ScopeTools\History\Prints.txt";

$CookiesFile = "F:\PersonalResources\Programming\Workshop\Powershell\ScopeTools\Cookies\cookies.json";
