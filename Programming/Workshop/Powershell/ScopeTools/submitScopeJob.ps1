param(
    [string] $Param1 = "",

    [string] $Param2 = "",

    [int] $Tokens = 400
)

. "$PSScriptRoot\Lib\functions.ps1"
. "$PSScriptRoot\Lib\variables.ps1"

$Cookies = ConvertFrom-Json -InputObject (Get-Content $CookiesFile -Raw)
$VCDescr    = ""
$ScriptPath = ""

if ($Param1 -eq "")
{
    $VCDescr    = $Cookies.VCDescr
    $ScriptPath = $Cookies.ScriptPath
    if ($VCDescr == "" -or $ScriptPath == "")
    {
        return
    }
}
elseif ($Param2 -ne "")
{
    if ($Param1.Contains("script"))
    {
        $ScriptPath = $Param1
        $VCDescr    = $Param2
    }
    else 
    {
        $VCDescr    = $Param1
        $ScriptPath = $Param2
    }
}
else
{
    if ($Param1.Contains("script"))
    {
        $ScriptPath = $Param1
        $VCDescr    = $Cookies.VCDescr
    }
    else 
    {
        $VCDescr    = $Param1
        $ScriptPath = $Cookies.ScriptPath
    }
}

[string] $JobName = GetFileNameWithoutExt($ScriptPath)
[string] $VCName  = GetVC($VCDescr)

$JobName = "minzhe_" + $JobName

$CommandStr = "$ScopeRoot\Scope.exe submit -i $ScriptPath -vc $VCName -f $JobName -tokens $Tokens" `
            + " -maxUnavailability 0" `
            + " -tempdir D:\Tmp\ScopeTmp" `
            + " -RESOURCE_PATH `$(CLUSTER_ROOT)" `
            + " -INPUT_PATH `$(CLUSTER_ROOT)" `
            + " -OUTPUT_PATH `$(CLUSTER_ROOT)"

Write-Output $CommandStr;
$ret = ProcessCommand($CommandStr)

PrintInfo($ret)

$EndLine = $ret[-1]
if ($EndLine.Length -gt 36)
{
    $JobId = $EndLine.Substring($EndLine.Length - 36)
    $JobLink = $VCName + "_jobs/" + $JobId
    PrintInfo($JobLink)    
}

$Cookies.VCDescr    = $VCDescr
$Cookies.ScriptPath = $ScriptPath
$Cookies | ConvertTo-Json | Out-File $CookiesFile

