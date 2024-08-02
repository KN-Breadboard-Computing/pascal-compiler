#include <iostream>
#include <fstream>

#include "ast/program_node.hpp"

std::unique_ptr<ast::ProgramNode> parse(const std::string& inputFileName, std::vector<std::string>& errors);

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <input-file> <output-ast-file> <output-asm-file>" << std::endl;
    return 1;
  }

  std::string inputFileName{argv[1]};
  std::string outputAstFileName{argv[2]};
  std::string outputAsmFileName{argv[3]};

  std::vector<std::string> errors;
  auto program = parse(inputFileName, errors);

  if(errors.size() > 0) {
    for(auto& error : errors) {
      std::cerr << error << std::endl;
    }
    return 1;
  }

  std::ofstream outputAsmFile(outputAsmFileName);
  program->print(outputAsmFile, 0);

  return 0;
}