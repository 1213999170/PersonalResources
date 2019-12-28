param(
    [datetime] $startDelta = [datetime]::parseexact("2019-12-05 01:00", 'yyyy-MM-dd HH:mm', $null),
    #[datetime] $endDelta   = [datetime]::parseexact("2019-12-08 23:00", 'yyyy-MM-dd HH:mm', $null)
    [datetime] $endDelta   = [datetime]::parseexact("2019-12-05 23:00", 'yyyy-MM-dd HH:mm', $null)
)

Import-Module "$PSScriptRoot\Lib\variables.psm1"
Import-Module "$PSScriptRoot\Lib\functions.psm1"

[datetime] $delta = $startDelta
while ($delta -le $endDelta) {
    $jobname = "HourlyMAIReport_" + $delta.ToString("yyyyMMddHHmm")
    $deltaParam = $delta.ToString("yyyy-MM-ddTHH:mm:ss")

    $commandStr = "$ScopeRoot\ScopePreprocessor.exe submit" `
                + " -i D:\Repos\Ads.BI.Mediation\target\distrib\debug\amd64\Autopilot\MFRLoader\Binaries\HourlyMAIReport.script" `
                + " -vc https://cosmos11.osdinfra.net/cosmos/sharedData.Ads.Dev/" `
                + " -f $jobname" `
                + " -params Delta=\""$deltaParam\""" `
                + " -params OutputPathRoot=\""local/users/minzlu/HourlyMAIReport/\""" `
                + " -params DSVPathRoot=\""/local/prod/pipelines/Mediation/Contracts/\""" `
                + " -params SAPathRoot=\""/local/prod/pipelines/Mediation/Facts/\""" `
                + " -params ResourcePath=\""/local/prod/pipelines/Mediation/Views/\""" `
                + " -params MonetizationViewPath=\""/shares/adCenter.BICore.SubjectArea/SubjectArea/Monetization/views/e2ephys\""" `
                + " -params DataSet=\""Mobile\""" `
                + " -params StagingArea=\""/local/twp\""" `
                + " -maxUnavailability 0" `
                + " -p 1500"
    
    $ret = ProcessCommand $commandStr
    PrintInfo $ret

    $delta = $delta.AddHours(1)
}

