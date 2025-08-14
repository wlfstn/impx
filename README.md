# impx
Imperial CLI calculator

## VSCode users
- Microsoft C/C++ extention appears to not be able to locate modules
- Clangd extention appears to work fine `llvm-vs-code-extensions.vscode-clangd`

## Modules
- Compile std.ixx to precompiled module with clang (Not used in project)
`clang++ -std=c++23 -x c++-module ./std.ixx --precompile -o ./std.pcm`