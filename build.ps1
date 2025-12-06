function stopClangd {
	if (Get-Process clangd -ErrorAction SilentlyContinue) {
		Write-Host "Stopping clangd..."
		taskkill /IM clangd.exe /F 2>$null
		Start-Sleep -Milliseconds 500 # wait 0.5s for Windows to release mappings
	} else {
		Write-Host "clangd not running."
	}
}

function cppRun {
	param (
		[string]$ProcType
	)
	Write-Host "Build script!"

	if ($ProcType -eq "--release") {
		Write-Host "Generating Release Build!"
		cmake -G Ninja -B ./build -DCMAKE_BUILD_TYPE=Release
		ninja -C build
		return
	}
	
	if ($ProcType -match '1') {
		Write-Host "Generating debug Build with clang Setup!"
		cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -G Ninja -B ./build -DCMAKE_CXX_FLAGS_DEBUG="-DDEBUG"
	}
	if ($ProcType -match 'g') {
		Write-Host "Generating debug Build!"
		cmake -G Ninja -B ./build -DCMAKE_CXX_FLAGS_DEBUG="-DDEBUG" 
	}
	if ($ProcType -match 'b') {
		Write-Host "Building!"
		# stopClangd # Still doesn't completely stop the issue completely.
		ninja -C build
	}
	if ($ProcType -match 'r') {
		Write-Host "Launching!"
		./build/impx.exe
	}
	if ($ProcType -notmatch '[gbr1]') {
		ninja -C build
		./build/impx.exe
	}
}

cppRun $args[0]