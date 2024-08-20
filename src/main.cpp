#include <fstream>
#include <iostream>

#include "ast/program_node.hpp"
#include "bblocks/bb_cfg_generator.hpp"

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program);

int main(int argc, char* argv[]) {
  constexpr int expectedArgumentsNumber{5};
  if (argc != expectedArgumentsNumber) {
    std::cerr << "Usage: " << argv[0] << " <input-file> <output-ast-file> <output-bblocks-file> <output-asm-file>" << std::endl;
    return 1;
  }

  const std::string inputFileName{argv[1]};
  const std::string outputAstFileName{argv[2]};
  const std::string outputAsmFileName{argv[4]};

  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  auto parsed = parse(inputFileName, errors, program);

  if (!errors.empty()) {
    for (auto& error : errors) {
      std::cerr << error << std::endl;
    }
  }

  if (!parsed) {
    std::cerr << "Failed to parse!" << std::endl;
    return 1;
  }

  std::cout << "Parsed successfully!" << std::endl;
  std::ofstream outputAstFile(outputAstFileName);
  outputAstFile << *program;

  bblocks::BbCfgGenerator cfgGenerator;
  const std::map<std::string, bblocks::BBControlFlowGraph> cfg{cfgGenerator.generate(program)};

  std::ofstream outputBbFile(argv[3]);
  outputBbFile << cfg;

  return 0;
}