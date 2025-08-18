#include <iostream>
#include <string>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../vendor/wereType.hpp"
import lexer;

int main() {
	
	LPCWSTR userInput = GetCommandLineW();
	std::wcout << L"Raw Command Line: " << userInput << std::endl;

	std::vector<std::wstring> tokens;

}
