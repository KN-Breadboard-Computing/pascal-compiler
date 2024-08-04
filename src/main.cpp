#include <fstream>
#include <iostream>

#include "ast/program_node.hpp"

std::unique_ptr<ast::ProgramNode> parse(const std::string& inputFileName, std::vector<std::string>& errors, bool& parsed);

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <input-file> <output-ast-file> <output-asm-file>" << std::endl;
    return 1;
  }

  std::string inputFileName{argv[1]};
  std::string outputAstFileName{argv[2]};
  std::string outputAsmFileName{argv[3]};

  std::vector<std::string> errors;
  bool parsed;
  auto program = parse(inputFileName, errors, parsed);

  if (errors.size() > 0) {
    for (auto& error : errors) {
      std::cerr << error << std::endl;
    }
  }

  if (parsed) {
    std::cout << "Parsed successfully!" << std::endl;
    std::ofstream outputAstFile(outputAstFileName);
    program->print(outputAstFile, 0);
  }
  else {
    std::cerr << "Failed to parse!" << std::endl;
    return 1;
  }

  return 0;
}