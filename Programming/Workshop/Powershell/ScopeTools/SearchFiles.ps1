param(
    [string] $directory = ".\Data\input.txt",
    [string] $targetFile = ".\Data\output.txt", 
    [string] $searchPattern = "2254"
)

Clear-Content $targetFile

$files = Get-ChildItem -Path $directory
foreach ($file in $files) {
    Write-Output "Reading $file"
    $content = Get-Content -LiteralPath $file.FullName | Where-Object{$_.Contains($searchPattern)}
    Add-Content $targetFile $content
}