## Build
`clang++ -std=c++23 ./main.cpp`
`./build -b` powershell script

## Release versions
- Update version string in main.cpp
- `git tag -a v1.0.0 -m "Release v1.0.0"`
- `git push origin --tags`