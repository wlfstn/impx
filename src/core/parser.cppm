module;

#include <vector>
#include "../../vendor/wereType.hpp"

export module parser;
import lexer;

export namespace parser {

	enum class NodeType : u8 {
		Number,
		Operator
	};

	struct ASTNode {
		NodeType type;
		std::vector<ASTNode*> children;
	};

}