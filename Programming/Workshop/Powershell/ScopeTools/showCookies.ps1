. "$PSScriptRoot\Lib\variables.ps1"
ConvertFrom-Json -InputObject (Get-Content $CookiesFile -Raw)