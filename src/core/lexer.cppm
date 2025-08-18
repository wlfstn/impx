module;

#include <string>
#include <vector>
#include <cwctype>
#include "../../vendor/wereType.hpp"

export module lexer;

namespace lexer {

	auto tokenize(const std::wstring& input) -> std::vector<std::wstring> {
		std::vector<std::wstring> tokens;
		std::wstring current;

		for (wchar_t c : input) {
			if (iswspace(c)) {
				if (!current.empty()) {
					tokens.push_back(current);
					current.clear();
				}
			} else {
				current.push_back(c);
			}
		}

		if (!current.empty()) {
			tokens.push_back(current);
		}
		return tokens;
	}

	enum class token_t : u8 {
		Number,
		Operator,
		flag
	};

	struct token {
		std::string value;
		token_t type;
	};

}