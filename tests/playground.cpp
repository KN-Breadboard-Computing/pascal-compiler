#include <fstream>
#include <iostream>
#include <sstream>

#include "../src/ast/program_node.hpp"
#include "../src/bblocks/bb_ssa_generator.hpp"
#include "../src/machine_code/machine_code_generator.hpp"

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program);

void translateBasicBlockToMachineCode(bblocks::BasicBlock&& basicBlock,
                                      std::vector<machine_code::MachineInstruction>& machineInstructions) {
  std::vector<bblocks::BBCall::Argument> readArguments;
  readArguments.emplace_back(bblocks::BBCall::Argument::Type::VARIABLE_DEF, "src", 0);

  std::vector<bblocks::BBCall::Argument> writeArguments;
  writeArguments.emplace_back(bblocks::BBCall::Argument::Type::VARIABLE_USE, "dst", 0);

  basicBlock.addInstructionToStart(std::make_unique<bblocks::BBCall>("read", std::move(readArguments), false));
  basicBlock.addInstruction(std::make_unique<bblocks::BBCall>("write", std::move(writeArguments), false));
  basicBlock.addInstruction(std::make_unique<bblocks::BBHalt>());

  std::cout << basicBlock << std::endl;

  bblocks::BBControlFlowGraph cfg{"main", basicBlock};

  bblocks::BbSsaGenerator ssaGenerator;
  ssaGenerator.toSsa("program", cfg);
  ssaGenerator.fromSsa();

  machine_code::MachineCodeGenerator machineCodeGenerator;
  machineCodeGenerator.generate(ssaGenerator.getControlFlowGraphs(),
                                machine_code::MachineCodeGenerator::RegisterAllocator::LINEAR_SCAN);
  machineInstructions = machineCodeGenerator.getMachineCode().at("program");

  machineCodeGenerator.saveLiveRanges(std::cout);
}

int main() {
  bblocks::BasicBlock basicBlock;

  basicBlock.addInstruction(std::make_unique<bblocks::BBUnaryOperationVV>(
      "src", "dst", bblocks::BBUnaryOperationVV::SourceType::REGISTER, bblocks::BBUnaryOperationVV::DestinationType::REGISTER,
      bblocks::BBUnaryOperationEnum::NEG));

  std::vector<machine_code::MachineInstruction> machineInstructions;
  translateBasicBlockToMachineCode(std::move(basicBlock), machineInstructions);

  for (const auto& machineInstruction : machineInstructions) {
    std::cout << machineInstruction.toString() << std::endl;
  }
  std::cout << std::endl;

  return 0;
}