### Shell settings ###
[console]::InputEncoding = [console]::OutputEncoding = [System.Text.Encoding]::UTF8 # Change code page

<#
  Set bash prompt
#>
function Prompt {
    Write-Host "$([DateTime]::Now.ToString("HH:mm:ss")) " -ForegroundColor Cyan -NoNewline
    Write-Host $pwd -ForegroundColor Green -nonewline
    Write-Host " >" -ForegroundColor Yellow -NoNewline
    return " "
}

<#
  Store and search all history commands
    [System.Net.ServicePointManager]::SecurityProtocol=[System.Net.SecurityProtocolType]::Tls12
    Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
    (new-object Net.WebClient).DownloadString("http://bit.ly/GetPsGet") | iex
    import-module PsGet
    install-module PsUrl
    install-module PSReadline
#>
$HistoryFilePath = Join-Path ([Environment]::GetFolderPath('UserProfile')) .ps_history
Register-EngineEvent PowerShell.Exiting -Action { Get-History | Export-Clixml $HistoryFilePath } | out-null
if (Test-path $HistoryFilePath) { Import-Clixml $HistoryFilePath | Add-History }
Set-PSReadlineKeyHandler -Key UpArrow -Function HistorySearchBackward   # Redefine UpArrow / DownArrow to search pattern-matched history commands
Set-PSReadlineKeyHandler -Key DownArrow -Function HistorySearchForward  # Redefine UpArrow / DownArrow to search pattern-matched history commands
Set-PSReadLineOption -HistorySearchCursorMovesToEnd                     # Move cursor to line end when searching history
Set-PSReadlineKeyHandler -Key Tab -Function Complete                    # Set bash-style completion
Set-PSReadlineOption -BellStyle None                                    # No bell

<#
  Import common Modules
    PowerShellGet\Install-Module posh-git -Scope CurrentUser -AllowClobber
    Update-Module posh-git
    PowerShellGet\Install-Module oh-my-posh -Scope CurrentUser -AllowClobber
    Set-ExecutionPolicy Bypass -Scope Process -Force; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))

#>
Import-Module posh-git
Import-Module oh-my-posh
Import-Module "$env:ChocolateyInstall\helpers\chocolateyProfile.psm1"
Import-Module "F:\PersonalResources\Programming\Workshop\Powershell\MyModules\init.psm1"
Import-Module "F:\PersonalResources\Programming\Workshop\Powershell\MyModules\ShortPath.psm1"
Import-Module "F:\PersonalResources\Programming\Workshop\Powershell\MyModules\SshVM.psm1"
Import-Module Cosmos

# Uncomment the sentence to get Paradox theme from oh-my-posh
# Set-Theme Paradox

<#
  Set my alias
#>
Set-Alias "which" "Get-Command"
Set-Alias "im" "Import-Module"

# Chocolatey profile
$ChocolateyProfile = "$env:ChocolateyInstall\helpers\chocolateyProfile.psm1"
if (Test-Path($ChocolateyProfile)) {
  Import-Module "$ChocolateyProfile"
}
