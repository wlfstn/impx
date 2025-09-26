$exeDownload = "https://github.com/wlfstn/impx/releases/download/v1.0.3/impx.exe"
$destinationDir = "$env:USERPROFILE\wlfstn\impx"
$destinationFile = Join-Path $destinationDir "impx.exe"

if (-not (Test-Path $destinationDir)) {
	New-Item -ItemType Directory -Path $destinationDir -Force | Out-Null
}

Invoke-WebRequest -Uri $exeDownload -OutFile $destinationFile

$userPath = [Environment]::GetEnvironmentVariable("Path", "User")
if (-not $userPath) {
	$userPath = ""
}

if ($userPath -split ";" -contains $destinationDir) {
	Write-Host "impx directory is already in PATH."
} else {
	$addToPath = Read-Host "Would you like to add impx to your PATH? (y/n)"
	if ($addToPath -match '^[Yy]$') {
		$newPath = if ($userPath -eq "") {
			$destinationDir
		} else {
			"$userPath;$destinationDir"
		}
		[Environment]::SetEnvironmentVariable("Path", $newPath, "User")
		Write-Host "Added $destinationDir to user PATH."
	} else {
		Write-Host "Installed, but skipped adding to PATH."
	}
}