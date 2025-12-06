# Working on MacOS

## Working in VSCode
Create user editor files
- Create folder for VSCode `./vscode`
- Create file `settings.json`
```
{
	"clangd.path": "/opt/homebrew/opt/llvm/bin/clangd",

	"clangd.arguments": [
			"--header-insertion=never",
			"--background-index",
			"--all-scopes-completion",
			"--pch-storage=memory",
			"--query-driver=/opt/homebrew/opt/llvm/bin/clang++",
			"--compile-commands-dir=build",
			"--enable-diagnostics=false"
	],

	"cmake.configureSettings": {
		"CMAKE_C_COMPILER": "/opt/homebrew/opt/llvm/bin/clang",
		"CMAKE_CXX_COMPILER": "/opt/homebrew/opt/llvm/bin/clang++"
	},

	"C_Cpp.default.includePath": [
		"${workspaceFolder}/**",
		"/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include",
		"/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks"
	]
}
```