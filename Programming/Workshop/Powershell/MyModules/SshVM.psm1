
<#
    Module: SshVM.psm1
    Usage : Store commands of ssh connection to VMs
#>

# Functions
function Enter-VMJP {
    ssh minzlu@vmjp-minzhe.japaneast.cloudapp.azure.com
}

function Enter-VMUS {
    ssh minzlu@vmus-minzhe.westus2.cloudapp.azure.com
}

# Export
$ExportFunctions = (
    "Enter-VMJP",
    "Enter-VMUS"
)

Export-ModuleMember -Function $ExportFunctions
