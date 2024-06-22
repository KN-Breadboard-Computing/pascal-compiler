#include <iostream>

#include "ast/ast_node.hpp"

int main(int argc, char *argv[]) {
  if (argc != 3) {
	std::cerr << "Usage: " << argv[0] << " <input-file> <output-file>" << std::endl;
	return 1;
  }

  ast::AstNode ast;
  std::vector<std::string> errors;

  return 0;
}