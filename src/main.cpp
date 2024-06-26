#include <iostream>
#include <string>

#include "ast/program_node.hpp"

void parse(const std::string& inputFileName, ast::ProgramNode& ast, std::vector<std::string>& errors);

int main(int argc, char *argv[]) {
  if (argc != 3) {
	std::cerr << "Usage: " << argv[0] << " <input-file> <output-file>" << std::endl;
	return 1;
  }

  std::string inputFileName{argv[1]};
  std::string outputFileName{argv[2]};

  ast::ProgramNode ast;
  std::vector<std::string> errors;

  parse(inputFileName, ast, errors);

  return 0;
}