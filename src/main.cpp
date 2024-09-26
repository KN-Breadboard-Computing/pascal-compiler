#include <fstream>
#include <iostream>

#include "ast/program_node.hpp"
#include "bblocks/bb_cfg_generator.hpp"
#include "bblocks/bb_ssa_generator.hpp"
#include "machine_code/machine_code_generator.hpp"

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program);

int main(int argc, char* argv[]) {
  constexpr int expectedArgumentsNumber{7};
  if (argc != expectedArgumentsNumber) {
    std::cerr << "Usage: " << argv[0]
              << " <input-file> <output-ast-file> <output-bblocks-file> <output-ssa-file> <output-machine-code-file> "
                 "<output-asm-file>"
              << std::endl;
    return 1;
  }

  const std::string inputFileName{argv[1]};
  const std::string outputAstFileName{argv[2]};
  const std::string outputBblocksFileName{argv[3]};
  const std::string outputSsaFileName{argv[4]};
  const std::string outputMachineCodeFileName{argv[5]};
  const std::string outputAsmFileName{argv[6]};

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
  cfgGenerator.generate(program);

  std::ofstream outputBbFile(outputBblocksFileName);
  for (const auto& [name, cfg] : cfgGenerator.getControlFlowGraphs()) {
    outputBbFile << name << ":\n" << cfg << std::endl;
  }

  cfgGenerator.removeEmptyBasicBlocks();
  cfgGenerator.removeTemporaryVariables();

  std::ofstream outputOptimizedBbFile("optimized-" + outputBblocksFileName);
  for (const auto& [name, cfg] : cfgGenerator.getControlFlowGraphs()) {
    outputOptimizedBbFile << name << ":\n" << cfg << std::endl;
  }

  bblocks::BbSsaGenerator ssaGenerator;
  for (const auto& [name, cfg] : cfgGenerator.getControlFlowGraphs()) {
    ssaGenerator.toSsa(name, cfg);
  }

  std::ofstream outputSsaFile(outputSsaFileName);
  for (const auto& [name, cfg] : ssaGenerator.getControlFlowGraphs()) {
    outputSsaFile << name << ":\n" << cfg << std::endl;
  }

  ssaGenerator.optimize();

  std::ofstream outputOptimizedSsaFile("optimized-" + outputSsaFileName);
  for (const auto& [name, cfg] : ssaGenerator.getControlFlowGraphs()) {
    outputOptimizedSsaFile << name << ":\n" << cfg << std::endl;
  }

  ssaGenerator.fromSsa();

  machine_code::MachineCodeGenerator machineCodeGenerator;
  machineCodeGenerator.generate(ssaGenerator.getControlFlowGraphs());

  machineCodeGenerator.saveMachineCode(outputMachineCodeFileName);
  machineCodeGenerator.saveAssembly(outputAsmFileName);
  machineCodeGenerator.saveBinary("binary-" + outputAsmFileName);

  return 0;
}