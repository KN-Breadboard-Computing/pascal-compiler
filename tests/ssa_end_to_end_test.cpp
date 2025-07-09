#include <iostream>
#include <ranges>

#include "gtest/gtest.h"

#include "../src/ast/program_node.hpp"
#include "../src/bblocks/bb_ssa_generator.hpp"
#include "../src/machine_code/machine_code_generator.hpp"
#include "emulator_connector.hpp"

using namespace bblocks;
using namespace machine_code;

void translateBasicBlockToMachineCode(const std::vector<std::string>& readVariables,
                                      const std::vector<std::string>& writeVariables, BasicBlock&& basicBlock,
                                      uint16_t variablesOffset, std::vector<uint8_t>& binaryCode) {
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

  binaryCode = machineCodeGenerator.getBinaryCode();
  binaryCode.erase(binaryCode.begin(), binaryCode.begin() + readVariableStepsNumber * readVariables.size());
  binaryCode.erase(binaryCode.end() - writeVariableStepsNumber * writeVariables.size() - 1, binaryCode.end() - 1);
}

TEST(test, test) {
  BasicBlock basicBlock;
  basicBlock.addInstruction(
      std::make_unique<BBMoveNV>(23, "a", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  basicBlock.addInstruction(
      std::make_unique<BBMoveNV>(32, "b", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));

  std::vector<uint8_t> binaryCode;
  translateBasicBlockToMachineCode({"a", "b"}, {"a", "b"}, std::move(basicBlock), 1 << 5, binaryCode);

  EmulatorConnector emulatorConnector;
  emulatorConnector.run(binaryCode);

  ASSERT_TRUE(emulatorConnector.assertRegA(32));
  ASSERT_TRUE(emulatorConnector.assertRegB(23));
}