$data = get-service | Where-Object status -eq 'Stopped' | Select-Object name, status

$data | out-file .\services.csv
notepad .\services.csv

$data | export-csv .\services.csv
get-content .\services.csv

$PSVersionTable
(get-command).count

Get-Verb -Group Security | Format-List
Get-Service -Name M* -ComputerName Client01,DC01

* 3 Important Commands
	Get-Commands
	Get-Help
	Get-Member
-

get-command -verb get -noun *dns*
get-command -name *fire* -commandtype function

get-help -name get-command -detailed
man -name get-command -detailed
get-help -name *dns*

update-help

help get-service
help get-service -full

help *about*

get-command -commandtype function | measure-object
	-- 得到统计量，计数，平均，求和，最大值，最小值等

get-command -name *ip* -module nettcpip

get-history
invoke-history -id 24
	-- 重复历史命令记录
clear-history 


start-transcript
	-- 将你之后的操作记录保存到脚本文件里
stop-transcript 




