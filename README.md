# impx
Imperial CLI calculator

## VSCode users
- Microsoft C/C++ extention appears to not be able to locate modules
- Clangd extention might work (75% chance) `llvm-vs-code-extensions.vscode-clangd`
- clangd module error (built from a different branch) fix potentially `never allow use compile_commands.json`.

## Modules
- Compile std.ixx to precompiled module with clang (Not used in project)
`clang++ -std=c++23 -x c++-module ./std.ixx --precompile -o ./std.pcm`