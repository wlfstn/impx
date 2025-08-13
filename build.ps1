function cppRun {
	param (
		[string]$ProcType
	)
	Write-Host "Build script!"
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
		ninja -C build
	}
	if ($ProcType -match 'r') {
		Write-Host "Launching!"
		./build/impx.exe
	}
	if ($ProcType -notmatch '[gbr]') {
		ninja -C build
		./build/impx.exe
	}
}

cppRun $args[0]