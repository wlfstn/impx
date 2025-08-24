import lexer;

#include <iostream>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../vendor/wereType.hpp"

int main() {
	
	std::wstring raw_console = GetCommandLineW();
	std::wcout << L"Raw Command Line: " << raw_console << std::endl;

	size_t sPos = raw_console.find(L' ', 1);
	if (sPos == std::wstring::npos) {
		std::wcout << "No input was given!\n";
		return{};
	} 
	if (sPos + 1 < raw_console.size()) {
		
		std::wstring userInput = raw_console.substr(sPos + 1);
		std::wcout << L"Starting Pos:" << sPos << L" | User Input:" << userInput << "\n";
		auto lexVals = lexer::lex(userInput);
		for (auto val : lexVals) {
			std::wcout << L"[" << val.text << L" | " << as<u8>(val.type)  << L"] ";
		}

	} else {
		std::wcout << L"No input provided" << std::endl;
	}

}
