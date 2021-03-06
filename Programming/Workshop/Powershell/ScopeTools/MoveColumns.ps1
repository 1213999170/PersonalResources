param(
    [string] $DataFile = "",
    [string] $Delimiter = "`t"
)

Import-Module "$PSScriptRoot\Lib\variables.psm1"
Import-Module "$PSScriptRoot\Lib\functions.psm1"

# Preprocess $Columns
$Columns = Get-Content ".\Data\chooseColumn.txt"

if ($Columns.Length -le 0) {
    return
}

if ($Columns.GetType().Name -eq "String") {
    $Columns = @($Columns)
}

# Read DataFile
CheckExist($DataFile)

$Content = Get-Content $DataFile -Encoding UTF8
if ($Content.GetType().BaseType.Name -ne "Array" `
    -or $Content[0].GetType().Name -ne "String" `
    -or $Content.Length -lt 1) 
{
    return
}

# Get Indices
$Head = $Content[0]
$HeadColumns = $Head.Split($Delimiter)
$Indices = $Columns.ForEach({$HeadColumns.IndexOf($_)}).Where({$_ -ne -1})

# Output
Clear-Content ".\Data\output.txt"
foreach ($line in $Content) {
    $linecontent = $line.Split($Delimiter)
    $newline = $linecontent[$Indices] -join $Delimiter
    $newline = $newline + $Delimiter + $line
    Add-Content ".\Data\output.txt" $newline

    SparsePrintInfo $newline.SubString(0, 80)
}

