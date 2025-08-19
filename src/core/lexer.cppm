module;

#include <ranges>
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <cwctype>
#include <array>
#include <stdexcept>
#include "../../vendor/wereType.hpp"

export module lexer;

export namespace lexer {

	// ==================================================
	// Data Types

	enum class token_t : u8 {
		ImpValue,
		Number,
		Operator,
		flag
	};

	struct token {
		token_t type;
		std::wstring lexeme;
		size_t tokenPos;
	};

	
	// ==================================================
	// Functions

	bool isNumeric(const std::wstring& str) {
		return !str.empty() && std::all_of(str.begin(), str.end(), ::iswdigit);
	}

	bool isImpValue(const std::wstring& str) {
		auto pos = str.find(L'f');
		if (pos == std::wstring::npos) return false;
		if (pos == 0 || pos == str.size() - 1) return false;

		std::array<std::wstring, 2> impVal {
			str.substr(0,pos),
			str.substr(pos + 1)
		};

		return isNumeric(impVal[0]) && isNumeric(impVal[1]);
	}

	token_t classify(const std::wstring& str) {
		if (str.size() == 1 && std::wcschr(L"+-*/", str[0])) {
			return token_t::Operator;
		}

		if (str.size() > 1 && str.starts_with(L"-")) {
			return token_t::flag;
		}

		if (isImpValue(str)) {
			return token_t::ImpValue;
		}

		if (isNumeric(str)) {
			return token_t::Number;
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

	auto lex(const std::wstring& input) -> std::vector<token> {
		std::vector<token> result;

		for (auto&& [vPos, word] : tokenize(input) | std::views::enumerate) {
			token_t t = classify(word);

			size_t pos = static_cast<size_t>(vPos);
			result.push_back({t, word, static_cast<size_t>(pos)});
		}
		return result;
	}

}