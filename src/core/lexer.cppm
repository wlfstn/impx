module;

#include <optional>
#include <ranges>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <cwctype>
#include <stdexcept>
#include <iostream>
#include "../../vendor/wereType.hpp"

export module lexer;

export namespace lexer {

	namespace GBL {
		u8 toggles{};
	}

	// Data Types
	enum class flag : u8 {
		only_inches = 1 << 0,
		version = 1 << 1,
		debug = 1 << 2
	};

	enum class lexClass : u8 {
		ImpValue,
		Number,
		Op_add,
		Op_subtract,
		Op_multiply,
		Op_divide,
		flag
	};

	struct lexeme {
		lexClass type;
		std::wstring text;
		std::optional<i64> num;
		size_t tokenPos;
	};
	
	// ==================================================
	// Functions

	bool isNumeric(const std::wstring& str) {
		return !str.empty() && std::all_of(str.begin(), str.end(), ::iswdigit);
	}

	auto isImpValue(const std::wstring& str) -> std::optional<i64> {
		auto pos = str.find(L'f');
		if (pos == std::wstring::npos) return false;

		std::wstring before = str.substr(0,pos);
		std::wstring after = str.substr(pos + 1);

		if (before.empty()) return std::nullopt;
		if (after.empty()) after = L"0";

		if (isNumeric(before) && isNumeric(after)) {
			int imp_ft = std::stoi(before);
			int imp_in = std::stoi(after);

			return imp_ft * 12 + imp_in;
		}

		return std::nullopt;
	}

	auto classify(const std::wstring& str) -> std::pair<lexClass, std::optional<i64>> {
		if (str.size() == 1 && std::wcschr(L"+-*/", str[0])) {
			if (str == L"+") return {lexClass::Op_add, std::nullopt};
			if (str == L"-") return {lexClass::Op_subtract, std::nullopt};
			if (str == L"*") return {lexClass::Op_multiply, std::nullopt};
			if (str == L"/") return {lexClass::Op_divide, std::nullopt};
		}

		if (str.size() > 1 && str.starts_with(L"-")) {
			if (str == L"-in") {
				GBL::toggles |= as<u8>(flag::only_inches);
				std::cout << "inches flag enabled\n";
			} else if (str == L"-v") {
				GBL::toggles |= as<u8>(flag::version);
				std::cout << "version flag enabled\n";
			} else  if (str == L"-d") {
				GBL::toggles |= as<u8>(flag::debug);
				std::cout << "debug flag enabled\n";
			}
			return {lexClass::flag, std::nullopt};
		}
		
		if (isNumeric(str)) {
			return {lexClass::Number, std::stoi(str)};
		}

		if (auto val = isImpValue(str)) {
			return {lexClass::ImpValue, *val};
		}


		throw std::runtime_error("Unexpected token: " + std::string(str.begin(), str.end()) );
	}

	auto tokenize(const std::wstring& input) -> std::vector<std::wstring> {
		std::vector<std::wstring> tokens;
		std::wstring current;

		for (wchar_t ch : input) {
			if (iswspace(ch)) {
				if (!current.empty()) {
					tokens.push_back(current); // append token
					current.clear(); // start next token
				}
			} else {
				current.push_back(ch); // token expands
			}
		}

		if (!current.empty()) {
			tokens.push_back(current);
		}
		return tokens;
	}

	auto lex(const std::wstring& input) -> std::vector<lexeme> {
		std::vector<lexeme> result;

		for (auto&& [i, word] : tokenize(input) | std::views::enumerate) {
			auto [t, val] = classify(word);

			size_t pos = as<size_t>(i);
			result.push_back({t, word, val, pos});
		}
		return result;
	}
}