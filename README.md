# impx
Imperial CLI calculator

## VSCode users
- Microsoft C/C++ extention appears to not be able to locate modules
- Clangd extention might work (75% chance) `llvm-vs-code-extensions.vscode-clangd`
- clangd module error (built from a different branch) fix potentially `never allow use compile_commands.json`.

## MacOS users
- AppleClang is not fully supported by CMake and causes issues with modules.
- Install LLVM clang with home brew `brew install llvm`
- Specify the path to LLVM clang 
	`-DCMAKE_CXX_COMPILER=/opt/homebrew/opt/llvm/bin/clang++` 
	`-DCMAKE_C_COMPILER=/opt/homebrew/opt/llvm/bin/clang`
- Mac Terminal Command `export SDKROOT="$(xcrun --show-sdk-path)"`

## Modules
- Compile std.ixx to precompiled module with clang (Not used in project)
`clang++ -std=c++23 -x c++-module ./std.ixx --precompile -o ./std.pcm`