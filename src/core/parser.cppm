module;

#include <vector>
#include <optional>
#include <initializer_list>
#include <span>
#include "../../vendor/wereType.hpp"

export module parser;
import lexer;

export class Parser {
	public:
	Parser(std::span<const lexer::lexeme> toks) : tokens(toks){}

	private:
	std::span<const lexer::lexeme> tokens;
	size_t current = 0;

	struct ASTNode {
		lexer::lexClass type;
		std::optional<int> number;
		std::vector<ASTNode*> children;
	};

	// utility
	bool fileEnd() const { 
		return current >= tokens.size(); 
	}
	bool check(lexer::lexClass expected) const {
		if (fileEnd()) return false;
		return tokens[current].type == expected;
	}
	auto peek() const -> const lexer::lexeme& {
		return tokens[current];
	}
	auto advance() -> const lexer::lexeme& {
		return tokens[current++];
	}
	auto previous() const -> const lexer::lexeme& {
		return tokens[current - 1];
	}
	bool match(std::initializer_list<lexer::lexClass> kinds) {
		for (auto k : kinds) {
			if (check(k)) {
				advance();
				return true;
			}
		}
		return false;
	}

};