<#
    Module: ShortPath
    Usage :
#>
Import-Module "$PSScriptRoot\init.psm1"

# Functions
function Enter-PowershellWorkshop {
    Enter-Location "F:\PersonalResources\Programming\Workshop\Powershell"
}

function Enter-Repos {
    Enter-Location "D:\Repos"
}

function Enter-CompareRepos {
    Enter-Location "D:\03_Project\Compare_repos"
}

function Enter-RepoTools {
    Enter-Location "D:\Repos\Ads.BI.SubjectAreas\private\Tools"
}

function Enter-RepoCFR {
    Enter-Location "D:\Repos\Ads.BI.CFR"
}

# Alias
Set-UserAlias "cdp" "Enter-PowershellWorkshop"
Set-UserAlias "cdr" "Enter-Repos"
Set-UserAlias "cdc" "Enter-CompareRepos"
Set-UserAlias "cdt" "Enter-RepoTools"
Set-UserAlias "cdcfr" "Enter-RepoCFR"

# Export
$ExportFunctions = (
    "Enter-PowershellWorkshop",
    "Enter-Repos",
    "Enter-CompareRepos"
)

$ExportAlias = (
    "cdp",
    "cdr",
    "cdc"
)

Export-ModuleMember -Alias $ExportAlias -Function $ExportFunctions
