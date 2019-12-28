param(
    [string]   $commandTemplateFile = ".\Data\input_template.txt",
    [datetime] $startDelta = [datetime]::parse("2019-12-14 00:00"),
    [datetime] $endDelta   = [datetime]::parse("2019-12-14 19:00"), 
    [timespan] $interval   = [timespan]::parse("0.01:00:00")
)

Import-Module "$PSScriptRoot\Lib\variables.psm1"
Import-Module "$PSScriptRoot\Lib\functions.psm1"

if (-not (Test-Path $commandTemplateFile)) {
    Write-Error "Can't find template file: $commandTemplateFile"
    exit 1;
}
$commandStrRaw = Get-Content -Raw $commandTemplateFile
PrintInfo $commandStrRaw

[datetime] $delta = $startDelta
while ($delta -le $endDelta) {
    $deltaStr = $delta.ToString("yyyy-MM-ddTHH:mm:ss")
    $deltaStrInJobName = $delta.ToString("yyyyMMddHH")

    $commandStr = $commandStrRaw
    $commandStr = $commandStr.Replace("`$deltaStrInJobName`$", $deltaStrInJobName);
    $commandStr = $commandStr.Replace("`$deltaStr`$", $deltaStr);

    $ret = ProcessCommand $commandStr
    PrintInfo $ret

    $delta += $interval
}

