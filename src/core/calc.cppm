module;

#include <expected>
#include <string>

export module calc;
import parser;
import lexer;

export namespace calc {

	using EvalResult = std::expected<int, std::wstring>;

	EvalResult EvalAST(const ASTNode* node) {
		if (!node) return std::unexpected(L"Null AST node");
		
		switch (node->type) {
			case lexer::lexClass::Number:
			case lexer::lexClass::ImpValue:
				return node->number.value_or(0);

			case lexer::lexClass::Op_add: {
				auto left  = EvalAST(node->children[0]);
				auto right = EvalAST(node->children[1]);
				if (!left)  return left;   // propagate error
				if (!right) return right;
				return *left + *right;
			}

			case lexer::lexClass::Op_subtract: {
				auto left  = EvalAST(node->children[0]);
				auto right = EvalAST(node->children[1]);
				if (!left)  return left;
				if (!right) return right;
				return *left - *right;
			}

			case lexer::lexClass::Op_multiply: {
				auto left  = EvalAST(node->children[0]);
				auto right = EvalAST(node->children[1]);
				if (!left)  return left;
				if (!right) return right;
				return *left * *right;
			}

			case lexer::lexClass::Op_divide: {
				auto left  = EvalAST(node->children[0]);
				auto right = EvalAST(node->children[1]);
				if (!left)  return left;
				if (!right) return right;
				if (*right == 0) return std::unexpected(L"Division by zero");
				return *left / *right;
			}

			default:
				return std::unexpected(L"Unknown AST node type");
    }
	}
	std::wstring ftFormat(int value) {
		int ft = value / 12;
		int in = value % 12;

		return std::to_wstring(ft) + L"\'" + std::to_wstring(in) + L"\"";
	}

}
