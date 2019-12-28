<#
    Module: init
    Usage :
#>
# Functions
function Set-UserAlias ([string] $AliasName, [string] $CommandFunction) {
    $AliasInfo = Get-Alias $AliasName -ErrorAction SilentlyContinue
    if ($null -ne $AliasInfo) {
        if ($CommandFunction -eq $AliasInfo.Definition) {
            return
        }
        Write-Warning "Resetting alias ""$AliasInfo"" from ""$($AliasInfo.Definition)"" to ""$CommandFunction"""
        Remove-Alias $AliasName
    }
    Set-Alias $AliasName $CommandFunction -Option AllScope -Scope Global
}

function Enter-Location ([string] $Path) {
    Push-Location $Path
}

# Alias
Set-UserAlias "cd" "Enter-Location"

# Export
$ExportFunctions = (
    "Set-UserAlias",
    "Enter-Location"
)

$ExportAlias = (
    "cd"
)

Export-ModuleMember -Alias $ExportAlias -Function $ExportFunctions
