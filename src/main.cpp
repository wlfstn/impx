#include <cstddef>
#include <iostream>
#include <string>
#include <algorithm>
#include <cwctype>
#include <expected>

import lexer;
import parser;
import calc;
import weretype;

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif


std::wstring getCommandLineMacOS(int argc, char** argv)
{
	std::string utf8;

	for (int i = 0; i < argc; ++i) {
		utf8 += argv[i];
		if (i + 1 < argc) utf8 += " ";
	}

	// Convert UTF-8 → UTF-16
	std::wstring w;
	w.reserve(utf8.size());

	for (u8 c : utf8)
		w.push_back(as<wchar_t>(c));

	return w;
}

int main(int argc, char** argv) {
	std::wstring_view version = L"v1.0.4";
	
	#if defined(_WIN32)
	std::wstring raw_console = GetCommandLineW();
	#elif defined(__MACH__)
	std::wstring raw_console = getCommandLineMacOS(argc, argv);
	#endif
	std::transform(
		raw_console.begin(),
		raw_console.end(),
		raw_console.begin(),
		[](wchar_t c) { return std::towlower(c); }
	);
	
	u64 sPos = raw_console.find(L' ', 1);
	if (sPos == std::wstring::npos) {
		std::wcout << "No input was given!\n";
		return{};
	} 
	if (sPos + 1 < raw_console.size()) {
		
		std::wstring userInput = raw_console.substr(sPos + 1);
		auto lexVals = lexer::lex(userInput);
		
		Parser myParser(lexVals);
		ASTNode* root = nullptr;
		try {
			root = myParser.parse();
		} catch (const std::runtime_error& e) {
			std::cerr << "Parser error: " << e.what() << "\n";
			return 1;
		}
		
		if (lexer::GBL::toggles & as<u8>(lexer::flag::version)) {
			std::wcout << version << "\n";
		}
		if (lexer::GBL::toggles & as<u8>(lexer::flag::debug)) {
			std::wcout << L"Raw Command Line: " << raw_console << L"\n";
			std::wcout << L"Starting Pos: " << sPos << L" | User Input: " << userInput << "\n";
			std::wcout << L"AST:\n";
			PrintAST(root);
		}

		auto result = calc::EvalAST(root);
		if (result) {
			if (lexer::GBL::toggles & as<u8>(lexer::flag::only_inches)) {
				std::wcout << L"Result = " << *result << L"\n";
			} else {
				std::wcout << L"Result = " << calc::ftFormat(*result) << L"\n";
			}
		} else {
			std::wcerr << L"Error: " << result.error() << L"\n";
		}

	} else {
		std::wcout << L"No input provided" << std::endl;
	}
}
