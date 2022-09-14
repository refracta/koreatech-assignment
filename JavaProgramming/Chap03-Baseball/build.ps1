$folder = (Split-Path -Path (Get-Location) -Leaf)
$source = '.\'
$dest =  $env:temp + '\' + $folder
$eclipse_project = $source + 'eclipse_project/'
$zip = $source + $folder + '.zip'
$exclude = @('build.ps1', '*.iml')

Remove-Item -Path $zip -Recurse -ErrorAction SilentlyContinue
Remove-Item -Path $dest -Recurse -ErrorAction SilentlyContinue
Remove-Item -Path $eclipse_project -Recurse -ErrorAction SilentlyContinue
Copy-Item $source $dest -Recurse -Exclude $exclude

Copy-Item $dest ($eclipse_project + $folder) -Recurse -Exclude $exclude

# Compress-Archive -Path ($eclipse_project + '*') -DestinationPath $zip -Force -CompressionLevel Fastest
# not compatible with eclipse project archive

bz c $zip ($eclipse_project + $folder)
# winget install -e --id Bandisoft.Bandizip

Remove-Item -Path $eclipse_project -Recurse -ErrorAction SilentlyContinue
Remove-Item -Path $dest -Recurse -ErrorAction SilentlyContinue