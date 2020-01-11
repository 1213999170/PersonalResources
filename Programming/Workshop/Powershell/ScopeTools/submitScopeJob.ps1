param(
    [string] $Param1 = "",

    [string] $Param2 = "",

    [int] $Tokens = 400
)

Import-Module "$PSScriptRoot\Lib\variables.psm1"
Import-Module "$PSScriptRoot\Lib\functions.psm1"

$Cookies = ConvertFrom-Json -InputObject (Get-Content $CookiesFile -Raw)

$VCDescr    = $Cookies.VCDescr
$ScriptPath = $Cookies.ScriptPath
MatchParams $Param1 $Param2 ([ref]$ScriptPath) ([ref]$VCDescr) "script"

[string] $JobName = GetFileNameWithoutExt $ScriptPath
[string] $VCName  = GetVC $VCDescr

$JobName = "minzhe_" + $JobName

$CommandStr = "$ScopeRoot\Scope.exe submit -i $ScriptPath -vc $VCName -f $JobName -tokens $Tokens" `
            + " -maxUnavailability 0" `
            + " -tempdir D:\Tmp\ScopeTmp" `
            + " -RESOURCE_PATH `$(CLUSTER_ROOT)" `
            + " -INPUT_PATH `$(CLUSTER_ROOT)" `
            + " -OUTPUT_PATH `$(CLUSTER_ROOT)"

Write-Output $CommandStr;
$ret = ProcessCommand $CommandStr

PrintInfo $ret

$EndLine = $ret[-1]
if ($EndLine.Length -gt 36)
{
    $JobId = $EndLine.Substring($EndLine.Length - 36)
    $JobLink = $VCName + "_jobs/" + $JobId
    PrintInfo $JobLink
}

# Save Cookies
$Cookies.VCDescr    = $VCDescr
$Cookies.ScriptPath = $ScriptPath
$Cookies | ConvertTo-Json | Out-File $CookiesFile

