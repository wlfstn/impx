module;

#include <vector>
#include <iostream>
#include <optional>
#include <initializer_list>
#include <span>
#include <stdexcept>
#include "../../vendor/wereType.hpp"

export module parser;
import lexer;

export struct ASTNode {
	lexer::lexClass type;
	std::optional<int> number;
	std::vector<ASTNode*> children;
};

export class Parser {
	public:
	Parser(std::span<const lexer::lexeme> toks) : tokens(toks){}
	ASTNode* parse() {
		return parseExpression();
	}

	private:
	std::span<const lexer::lexeme> tokens;
	size_t current = 0;

	// utility
	bool fileEnd() const { return current >= tokens.size(); }
	auto peek() const -> const lexer::lexeme& { return tokens[current]; }
	auto advance() -> const lexer::lexeme& { return tokens[current++]; }
	auto previous() const -> const lexer::lexeme& { return tokens[current - 1]; }

	bool check(lexer::lexClass expected) const {
		return !fileEnd() &&  tokens[current].type == expected;
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

	ASTNode* parseExpression() {
		ASTNode* left = parseTerm();
		while (match({lexer::lexClass::Op_add, lexer::lexClass::Op_subtract})) {
			auto op = previous().type;
			auto* node = new ASTNode{op, std::nullopt, {}};
			node->children.push_back(left);
			node->children.push_back(parseTerm());
			left = node;
		}
		return left;
	}

	ASTNode* parseTerm() {
		ASTNode* left = parseFactor();

		while (match({lexer::lexClass::Op_multiply, lexer::lexClass::Op_divide})) {
			auto op = previous().type;
			auto* node = new ASTNode{op, std::nullopt, {}};
			node->children.push_back(left);
			node->children.push_back(parseTerm());
			left = node;
		}
		return left;
	}

	ASTNode* parseFactor() {
		if (match({lexer::lexClass::Number, lexer::lexClass::ImpValue})) {
			const auto& tok = previous();
			return new ASTNode{tok.type, tok.num, {}};
		}
		throw std::runtime_error("Unexpected Token in parseFactor");
	}

};

export void PrintAST(const ASTNode* node, int depth = 0) {
	if (!node) return;

	for (int i = 0; i < depth; i++) std::wcout << L"  ";

	switch (node->type) {
		case lexer::lexClass::Number:
		case lexer::lexClass::ImpValue:
			std::wcout << L"Number(" << node->number.value_or(0) << L")\n";
			break;
		case lexer::lexClass::Op_add:      std::wcout << L"Op(+)\n"; break;
		case lexer::lexClass::Op_subtract: std::wcout << L"Op(-)\n"; break;
		case lexer::lexClass::Op_multiply: std::wcout << L"Op(*)\n"; break;
		case lexer::lexClass::Op_divide:   std::wcout << L"Op(/)\n"; break;
		default: std::wcout << L"Other\n"; break;
	}

	for (auto* child: node->children) {
		PrintAST(child, depth + 1);
	}
}