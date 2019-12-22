param(
    [string] $directory = ".\Data\input.txt",
    [string] $targetFile = ".\Data\output.txt", 
    [string] $searchPattern = "DeviceOSId2 625"
)

Clear-Content $targetFile

$files = Get-ChildItem -Path $directory
foreach ($file in $files) {
    $content = Get-Content -LiteralPath $file.FullName | Where-Object{$_.Contains($searchPattern)}
    Add-Content $targetFile $content
}