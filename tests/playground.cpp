#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>

#include "../src/ast/program_node.hpp"
#include "../src/bblocks/bb_ssa_generator.hpp"
#include "../src/machine_code/machine_code_generator.hpp"

using namespace bblocks;
using namespace machine_code;

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program);

void readVariables(BasicBlock& basicBlock, const std::vector<std::string>& variables) {
  for (const auto& variable : variables) {
    std::vector<BBCall::Argument> readArguments;
    readArguments.emplace_back(BBCall::Argument::Type::VARIABLE_DEF, variable, 0);
    basicBlock.addInstructionToStart(std::make_unique<BBCall>("read", std::move(readArguments), false));
  }
}

void writeVariables(BasicBlock& basicBlock, const std::vector<std::string>& variables) {
  for (const auto& variable : variables) {
    std::vector<BBCall::Argument> writeArguments;
    writeArguments.emplace_back(BBCall::Argument::Type::VARIABLE_USE, variable, 0);
    basicBlock.addInstruction(std::make_unique<BBCall>("write", std::move(writeArguments), false));
  }
}

void halt(BasicBlock& basicBlock) {
  basicBlock.addInstruction(std::make_unique<BBHalt>());
}

void translateBasicBlockToMachineCode(const std::vector<std::string>& readVariables,
                                      const std::vector<std::string>& writeVariables, BasicBlock&& basicBlock,
                                      uint16_t variablesOffset, std::vector<MachineInstruction>& machineInstructions) {
  constexpr std::size_t readVariableStepsNumber = 1;
  constexpr std::size_t writeVariableStepsNumber = 1;

  for (const auto& variable : std::ranges::views::reverse(readVariables)) {
    std::vector<BBCall::Argument> readArguments;
    readArguments.emplace_back(BBCall::Argument::Type::VARIABLE_DEF, variable, 0);
    basicBlock.addInstructionToStart(std::make_unique<BBCall>("read", std::move(readArguments), false));
  }

  for (const auto& variable : writeVariables) {
    std::vector<BBCall::Argument> writeArguments;
    writeArguments.emplace_back(BBCall::Argument::Type::VARIABLE_USE, variable, 0);
    basicBlock.addInstruction(std::make_unique<BBCall>("write", std::move(writeArguments), false));
  }

  basicBlock.addInstruction(std::make_unique<BBHalt>());

  BBControlFlowGraph functionCfg{"main", basicBlock};
  std::map<std::string, BBControlFlowGraph> programCfg = {{"program", functionCfg}};

  MachineCodeGenerator machineCodeGenerator;
  machineCodeGenerator.generate(programCfg, MachineCodeGenerator::RegisterAllocator::LINEAR_SCAN, variablesOffset);
  machineInstructions.insert(
      machineInstructions.end(),
      machineCodeGenerator.getMachineCode().at("program").begin() + readVariableStepsNumber * readVariables.size() + 1,
      machineCodeGenerator.getMachineCode().at("program").end() - writeVariableStepsNumber * writeVariables.size() - 1);

  std::cout << "Basic Block:" << std::endl << basicBlock << std::endl;

  std::cout << "Live Ranges:" << std::endl;
  machineCodeGenerator.saveLiveRanges(std::cout);
  std::cout << std::endl;

  std::cout << "Machine Instructions:" << std::endl;
  for (const auto& instruction : machineInstructions) {
    std::cout << instruction.toString() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Binary Code:" << std::endl;
  std::vector<uint8_t> binaryCode = machineCodeGenerator.getBinaryCode();
  for (const auto& byte : binaryCode) {
    std::cout << std::hex << static_cast<int>(byte) << " ";
  }
  std::cout << std::dec << std::endl;
}

int main() {
  //  BasicBlock basicBlock1;
  //  basicBlock1.addInstruction(
  //      std::make_unique<BBMoveNV>(42, "src2", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  //  basicBlock1.addInstruction(
  //      std::make_unique<BBMoveNV>(42, "src3", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  //  std::vector<MachineInstruction> machineInstructions1;
  //  translateBasicBlockToMachineCode({"src1",}, {"src1", "src2", "src3"}, std::move(basicBlock1), 1 << 5, machineInstructions1);

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveNN>(42, 37, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(42, 1410, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(1410, 37, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(1920, 1410, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 1 << 5, machineInstructions1);



  return 0;
}