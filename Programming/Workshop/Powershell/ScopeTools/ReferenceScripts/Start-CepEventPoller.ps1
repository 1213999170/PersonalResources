param(
    [Parameter(Mandatory)]
    [string]$VC,

    [Parameter(Mandatory)]
    [string]$JobId,

    [Parameter(Mandatory)]
    [string]$EventName,

    [Parameter(Mandatory)]
    [timespan]$DeltaInterval,

    [Parameter(Mandatory)]
    [string]$ConnectionString,

    [switch]$Interactive = $False,

    [string]$EventValueTemplateFile = "Templates/$EventName.json",

    [int]$SleepInterval = 10
)

$DeltaFormat = "yyyyMMdd HHmm";
$UtcFormat = "yyyy-MM-ddTHH:mm:ssZ";
$JobUrl = "$VC/_Jobs/$JobId";
[System.Data.SqlClient.SqlConnection]$Connection = $null;

$VcClientDll = "$PSScriptRoot\VcClient.dll";
if (-not (Test-Path $VcClientDll)) {
    Write-Error "Please put VcClient.dll alongside with this script. Typically you can find it under scope sdk folder (C:\Program Files (x86)\Microsoft Visual Studio\<your version>\<your sku>\Common7\IDE\Extensions\Microsoft\ScopeStudio\2.5.0000.3\CosmosRuntimeSDK), you can also search it using Everything."
    exit 1;
}

[void][System.Reflection.Assembly]::LoadFile($VcClientDll);

function Download([string]$Url) {
    $tempFile = (New-Guid).Guid;
    try {
        [void][VcClient.VC]::Download($Url, $tempFile, $false, $false);
        return [System.IO.File]::ReadAllLines($tempFile);
    }
    catch {
        throw;
    }
    finally {
        if (Test-Path $tempFile) {
            Remove-Item $tempFile;
        }
    }
}

function ParseCti([string]$line) {
    if ($line -match ".*CurrentCTI=(.*?),.*") {
        return ([datetime]$Matches[1]).ToUniversalTime();
    }
    else {
        return $null;
    }
}

function GetMinCti {
    $latestStatusFile = "$JobUrl/system/CepStatus.latest.txt";
    [string[]]$lines = Download $latestStatusFile;
    for ($i = $lines.Count - 1; $i -ge 0; $i--) {
        if ($lines[$i].StartsWith("========")) {
            $lastBlockStart = $i;
            break;
        }
    }
    $minCti = [datetime]::MaxValue;
    for ($i = $lastBlockStart + 1; $i -lt $lines.Count; $i++) {
        $cti = ParseCti($lines[$i]);
        if ($null -eq $cti) {
            Write-Warning "Failed to parse min CTI for CEP status line $($lines[$i])";
            continue;
        }
        if ($cti -lt $minCti) {
            $minCti = $cti;
        }
    }
    return $minCti;
}

function GetConnection() {
    if ($null -eq $Connection -or $Connection.State -ne [System.Data.ConnectionState]::Open) {
        $Connection = New-Object System.Data.SqlClient.SqlConnection;
        $Connection.ConnectionString = $ConnectionString;
        try {
            $Connection.Open();
        }
        catch {
            throw "Failed to open connection to DWC DB using connection string $ConnectionString";
        }
    }
    return $Connection;
}

function CreateSqlCommand() {
    $conn = GetConnection;
    $command = New-Object System.Data.SqlClient.SqlCommand;
    $command.Connection = $conn;
    return $command;
}

function CreateSPCommand([string]$StoredProcedureName) {
    $command = CreateSqlCommand;
    $command.CommandType = [System.Data.CommandType]::StoredProcedure;
    $command.CommandText = $StoredProcedureName;
    return $command;
}

function GetDwcEventLatestDelta() {
    $command = CreateSqlCommand;
    try {
        $queryString =
        "SELECT TOP 1 PS.ParameterName `
            FROM ProcessState PS, EventType ET `
            WHERE PS.EventTypeId = ET.EventTypeId `
            AND ET.EventName = @EventName `
            ORDER BY PS.ParameterName DESC"
        $command.CommandText = $queryString;
        [void]$command.Parameters.AddWithValue("@EventName", $EventName);
        $reader = $command.ExecuteReader();
        if ($reader.Read()) {
            return $reader.GetValue(0);
        }
        else {
            throw "Failed to get latest event delta from DWC DB. Error: $_";
        }
    }
    finally {
        $command.Dispose();
    }
}

function PostEvent([string]$Delta, [string]$EventValue) {
    Write-Output "Posting event $EventName with delta $DeltaString, delta interval $DeltaInterval and event value $escapedEventValue";
    $command = CreateSPCommand "[dbo].[prc_ProcessStatePostByEventName]";
    try {
        [void]$command.Parameters.AddWithValue("@EventName", $EventName);
        [void]$command.Parameters.AddWithValue("@ParameterName", $Delta);
        [void]$command.Parameters.AddWithValue("@EventValue", $EventValue);
        [void]$command.Parameters.AddWithValue("@DeltaInterval", $DeltaInterval.ToString());
        [void]$command.ExecuteNonQuery();
    }
    catch {
        throw "Failed to post event. Error: $_";
    }
    finally {
        $command.Dispose();
    }
}

function ParseDwcDelta([string]$DwcDelta) {
    return [datetime]::SpecifyKind([datetime]::ParseExact($DwcDelta, $DeltaFormat, $null), [System.DateTimeKind]::Utc);
}

function JsonEscapeAndCompact([string]$Origin) {
    return $Origin.Replace(" ", "").Replace("`r", "").Replace("`n", "");
}

if (-not (Test-Path $EventValueTemplateFile)) {
    Write-Error "Event value template file not found under $EventValueTemplateFile.";
    exit 1;
}

$eventValueTemplate = Get-Content -Raw $EventValueTemplateFile;
Write-Output "Got event value template $eventValueTemplate";

$StartDelta = ParseDwcDelta (GetDwcEventLatestDelta);
Write-Output "Got latest delta of event $EventName`: $StartDelta"

if ($StartDelta.Minute % $DeltaInterval.Minutes -ne 0) {
    Write-Error "Looks like event $EventName have an incorrect delta: $StartDelta";
    exit 1;
}

$Current = $StartDelta;
while ($true) {
    try {
        $minCti = GetMinCti;
        if ($minCti -eq [datetime]::MaxValue) {
            Write-Warning "Failed to get min CTI.";
        }
        elseif ($Current -ge $minCti) {
            Write-Output "Reached latest Cti $minCti"
        }
        else {
            $eventValue = $eventValueTemplate;
            $DeltaString = $Current.ToString($DeltaFormat);
            $UtcDeltaString = $Current.ToString($UtcFormat);
            $CreateedTime = [datetime]::UtcNow.ToString("o");

            Write-Output "Current min CTI: $minCti";
            Write-Output "Current event delta: $Current";
            Write-Output "Posting event $DeltaString";

            Write-Output "Replacing `$JobId`$ with $JobId";
            $eventValue = $eventValue.Replace("`$JobId`$", $JobId);
            Write-Output "Replacing `$Delta`$ with $UtcDeltaString";
            $eventValue = $eventValue.Replace("`$Delta`$", $UtcDeltaString);
            Write-Output "Replacing `$CreatedTime`$ with $CreateedTime";
            $eventValue = $eventValue.Replace("`$CreatedTime`$", $CreateedTime);

            if ($Interactive) {
                Write-Output "Resolved event value:";
                Write-Output $eventValue;
                $confirm = Read-Host -Prompt "Comfirm? [Y(es)/N(o)/A(ll)]";
                if ($confirm -eq "A" -or $confirm -eq "a") {
                    $Interactive = $False;
                }
                elseif (-not($confirm -eq "y" -or $confirm -eq "Y")) {
                    Write-Warning "Posting cancelled.";
                    break;
                }
            }

            $escapedEventValue = JsonEscapeAndCompact $eventValue;
            PostEvent $DeltaString $escapedEventValue
            Write-Output "Done.";
            $Current += $DeltaInterval;
        }

        Start-Sleep $SleepInterval;
    }
    catch {
        Write-Error "Error occurred: $_";
    }
}
