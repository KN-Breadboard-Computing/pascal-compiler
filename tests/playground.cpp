#include <fstream>
#include <iostream>
#include <sstream>

#include "../src/ast/program_node.hpp"
#include "../src/bblocks/bb_ssa_generator.hpp"
#include "../src/machine_code/machine_code_generator.hpp"

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program);

void translateBasicBlockToMachineCode(bblocks::BasicBlock&& basicBlock,
                                      std::vector<machine_code::MachineInstruction>& machineInstructions) {
  bblocks::BBControlFlowGraph cfg{"main", basicBlock};

  bblocks::BbSsaGenerator ssaGenerator;
  ssaGenerator.toSsa("program", cfg);
  //  ssaGenerator.propagateConstants();
  //  ssaGenerator.removeRedundantAssignments();
  ssaGenerator.fromSsa();

  std::cout << "Control flow graphs: " << std::endl;
  for (const auto& [name, cfg] : ssaGenerator.getControlFlowGraphs()) {
    std::cout << "  " << name << std::endl;
    for (const auto& [label, basicBlock] : cfg.getBasicBlocks()) {
      std::cout << "    " << label << std::endl;
      for (const auto& instruction : basicBlock.getInstructions()) {
        std::cout << "      " << *instruction << std::endl;
      }
    }
  }

  machine_code::MachineCodeGenerator machineCodeGenerator;
  machineCodeGenerator.generate(ssaGenerator.getControlFlowGraphs(),
                                machine_code::MachineCodeGenerator::RegisterAllocator::LINEAR_SCAN);
  machineInstructions = machineCodeGenerator.getMachineCode().at("program");
}

int main() {
  bblocks::BasicBlock basicBlock;
  basicBlock.addInstruction(std::make_unique<bblocks::BBMoveNV>(0, "src", bblocks::BBMoveVV::SourceType::CONSTANT,
                                                                bblocks::BBMoveVV::DestinationType::REGISTER));
  basicBlock.addInstruction(std::make_unique<bblocks::BBUnaryOperationVV>(
      "src", "dst", bblocks::BBUnaryOperationVV::SourceType::REGISTER, bblocks::BBUnaryOperationVV::DestinationType::REGISTER,
      bblocks::BBUnaryOperationEnum::NEG));

  std::cout << basicBlock << std::endl;

  std::vector<machine_code::MachineInstruction> machineInstructions;
  translateBasicBlockToMachineCode(std::move(basicBlock), machineInstructions);

  return 0;
}