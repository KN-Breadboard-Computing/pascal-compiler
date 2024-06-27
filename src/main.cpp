#include <iostream>
#include <string>

#include "ast/program_node.hpp"

std::unique_ptr<ast::ProgramNode> parse(const std::string& inputFileName, std::vector<std::string>& errors);

int main(int argc, char *argv[]) {
  if (argc != 3) {
	std::cerr << "Usage: " << argv[0] << " <input-file> <output-file>" << std::endl;
	return 1;
  }

  std::string inputFileName{argv[1]};
  std::string outputFileName{argv[2]};

  std::vector<std::string> errors;
  auto program = parse(inputFileName, errors);

  return 0;
}