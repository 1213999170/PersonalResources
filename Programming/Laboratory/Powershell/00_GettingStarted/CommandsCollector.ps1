$data = get-service | Where-Object status -eq 'Stopped' | Select-Object name, status

$data | out-file .\services.csv
notepad .\services.csv

$data | export-csv .\services.csv
get-content .\services.csv

$PSVersionTable
(get-command).count

Get-Verb -Group Security | Format-List