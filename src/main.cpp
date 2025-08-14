#include <iostream>
#include <string>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "./core/lexer.hpp"
#include "../vendor/wereType.hpp"

int main(int argc, char* argv[]) {
	LPCWSTR raw = GetCommandLineW();
	std::wcout << L"Raw Command Line: " << raw << std::endl;
	
	std::vector<std::string> args(argv, argv + argc);

	for (const auto& arg : args) {
		if (auto totalInches = parseFeetInches(arg)) {
			std::cout << arg << " = " << *totalInches << " inches\n";
		}
	}

	u64 inches = 0;
}
