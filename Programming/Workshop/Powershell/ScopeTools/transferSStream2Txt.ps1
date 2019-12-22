param(
    [string] $SStreamFile = "",

    [int] $Tokens = 10
)

. "$PSScriptRoot\Lib\functions.ps1"
. "$PSScriptRoot\Lib\variables.ps1"

# String Process (SStreamFile)
$SStreamFile = RemoveEnd $SStreamFile "?property=info"

$VCName = ExtractVC $SStreamFile
$SStreamFile = RemoveHead $SStreamFile $VCName

if (!$SStreamFile.EndsWith(".ss")) {
    return
}

$FileName = GetFileNameWithoutExt $SStreamFile
$Path = GetPath $SStreamFile
$NewSStreamFile = PathJoin $Path,"$FileName.txt" "/"

# Write script
Clear-Content $CacheScopeScript
Add-Content $CacheScopeScript "data = SSTREAM ""$SStreamFile"";"
Add-Content $CacheScopeScript ""
Add-Content $CacheScopeScript "OUTPUT data TO ""$NewSStreamFile"""
Add-Content $CacheScopeScript "WITH STREAMEXPIRY ""15"""
Add-Content $CacheScopeScript "USING DefaultTextOutputter(""-outputHeader"");"

# Submit job
$JobName = "TransferSS2TXT_" + $FileName + "_" + $UserName
$CommandStr = "$ScopeRoot\Scope.exe submit -i $CacheScopeScript -vc $VCName -f $JobName -tokens $Tokens" `
            + " -maxUnavailability 0" `
            + " -tempdir D:\Tmp\ScopeTmp" `
            + " -RESOURCE_PATH `$(CLUSTER_ROOT)" `
            + " -INPUT_PATH `$(CLUSTER_ROOT)" `
            + " -OUTPUT_PATH `$(CLUSTER_ROOT)"

Write-Output $CommandStr
$ret = ProcessCommand $CommandStr

PrintInfo $ret

$EndLine = $ret[-1]
if ($EndLine.Length -gt 36)
{
    $JobId = $EndLine.Substring($EndLine.Length - 36)
    $JobLink = $VCName + "_jobs/" + $JobId
    PrintInfo $JobLink
}

