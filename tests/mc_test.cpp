#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>

#include "gtest/gtest.h"

#include "../src/ast/program_node.hpp"
#include "../src/bblocks/bb_ssa_generator.hpp"
#include "../src/machine_code/machine_code_generator.hpp"

using namespace bblocks;
using namespace machine_code;

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
}

TEST(instructionToMachineInstructionConversion, movesVV_ConstantToRegister) {
  // move constant to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src", "dst", BBMoveVV::SourceType::CONSTANT, BBMoveVV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src", "dst"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1),
               std::invalid_argument);
}

TEST(instructionToMachineInstructionConversion, movesVV_ConstantToMemory) {
  // move constant to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src", "dst", BBMoveVV::SourceType::CONSTANT, BBMoveVV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src", "dst"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1),
               std::invalid_argument);
}

TEST(instructionToMachineInstructionConversion, movesVV_RegisterToRegister) {
  // move register to register - any register need memory cell (short address)    - case dst2 := src2
  // move register to register - first register need memory cell (short address)  - case dst3 := src3
  // move register to register - second register need memory cell (short address) - case dst1 := src1
  // move register to register - each register need memory cell (short address)   - case dst4 := src4
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1),
                                   1 << 5, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 5);

  ASSERT_EQ(machineInstructions1.at(0).getType(), MachineInstruction::MOV_AT_ABS_B_ZP);
  ASSERT_EQ(machineInstructions1.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(0).getOperands(), std::vector<std::string>{"0b00100000"});

  ASSERT_EQ(machineInstructions1.at(1).getType(), MachineInstruction::MOV_B_A);
  ASSERT_EQ(machineInstructions1.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(2).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(2).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(2).getOperands(), std::vector<std::string>{"0b00100010"});

  ASSERT_EQ(machineInstructions1.at(3).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(3).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(3).getOperands(), std::vector<std::string>{"0b00100011"});

  ASSERT_EQ(machineInstructions1.at(4).getType(), MachineInstruction::POP_MEM_ZP);
  ASSERT_EQ(machineInstructions1.at(4).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(4).getOperands(), std::vector<std::string>{"0b00100001"});

  // move register to register - any register need memory cell (long address)    - case dst2 := src2
  // move register to register - first register need memory cell (long address)  - case dst3 := src3
  // move register to register - second register need memory cell (long address) - case dst1 := src1
  // move register to register - each register need memory cell (long address)   - case dst4 := src4
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2),
                                   1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 5);

  ASSERT_EQ(machineInstructions2.at(0).getType(), MachineInstruction::MOV_AT_ABS_B);
  ASSERT_EQ(machineInstructions2.at(0).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(0).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));

  ASSERT_EQ(machineInstructions2.at(1).getType(), MachineInstruction::MOV_B_A);
  ASSERT_EQ(machineInstructions2.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(2).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(2).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(2).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000010"}));

  ASSERT_EQ(machineInstructions2.at(3).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(3).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(3).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000011"}));

  ASSERT_EQ(machineInstructions2.at(4).getType(), MachineInstruction::POP_MEM);
  ASSERT_EQ(machineInstructions2.at(4).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(4).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));
}

TEST(instructionToMachineInstructionConversion, movesVV_RegisterToMemory) {
  // move register to memory - any register need memory cell (short address)    - case [dst2] := src2
  // move register to memory - first register need memory cell (short address)  - case [dst3] := src3
  // move register to memory - second register need memory cell (short address) - case [dst1] := src1
  // move register to memory - each register need memory cell (short address)   - case [dst4] := src4
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1),
                                   1 << 5, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 12);

  ASSERT_EQ(machineInstructions1.at(0).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(0).getOperands(), std::vector<std::string>{"0b00100000"});

  ASSERT_EQ(machineInstructions1.at(1).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions1.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(2).getType(), MachineInstruction::MOV_AT_TL_B);
  ASSERT_EQ(machineInstructions1.at(2).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(3).getType(), MachineInstruction::MOV_AT_B_A);
  ASSERT_EQ(machineInstructions1.at(3).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(4).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(4).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(4).getOperands(), std::vector<std::string>{"0b00100010"});

  ASSERT_EQ(machineInstructions1.at(5).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions1.at(5).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(6).getType(), MachineInstruction::MOV_AT_A_TL);
  ASSERT_EQ(machineInstructions1.at(6).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(7).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(7).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(7).getOperands(), std::vector<std::string>{"0b00100011"});

  ASSERT_EQ(machineInstructions1.at(8).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(8).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(8).getOperands(), std::vector<std::string>{"0b00100001"});

  ASSERT_EQ(machineInstructions1.at(9).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions1.at(9).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(10).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions1.at(10).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(11).getType(), MachineInstruction::MOV_AT_TL_TH);
  ASSERT_EQ(machineInstructions1.at(11).getOperands().size(), 0);

  // move register to memory - any register need memory cell (long address)     - case [dst2] := src2
  // move register to memory - first register need memory cell (long address)   - case [dst3] := src3
  // move register to memory - second register need memory cell (long address)  - case [dst1] := src1
  // move register to memory - each register need memory cell (long address)    - case [dst4] := src4
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2),
                                   1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 12);

  ASSERT_EQ(machineInstructions2.at(0).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(0).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(0).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));

  ASSERT_EQ(machineInstructions2.at(1).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions2.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(2).getType(), MachineInstruction::MOV_AT_TL_B);
  ASSERT_EQ(machineInstructions2.at(2).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(3).getType(), MachineInstruction::MOV_AT_B_A);
  ASSERT_EQ(machineInstructions2.at(3).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(4).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(4).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(4).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000010"}));

  ASSERT_EQ(machineInstructions2.at(5).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions2.at(5).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(6).getType(), MachineInstruction::MOV_AT_A_TL);
  ASSERT_EQ(machineInstructions2.at(6).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(7).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(7).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(7).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000011"}));

  ASSERT_EQ(machineInstructions2.at(8).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(8).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(8).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));

  ASSERT_EQ(machineInstructions2.at(9).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions2.at(9).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(10).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions2.at(10).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(11).getType(), MachineInstruction::MOV_AT_TL_TH);
  ASSERT_EQ(machineInstructions2.at(11).getOperands().size(), 0);
}

TEST(instructionToMachineInstructionConversion, movesVV_MemoryToRegister) {
  // move memory to register - any register need memory cell (short address)    - case dst2 := [src2]
  // move memory to register - first register need memory cell (short address)  - case dst3 := [src3]
  // move memory to register - second register need memory cell (short address) - case dst1 := [src1]
  // move memory to register - each register need memory cell (short address)   - case dst4 := [src4]
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1),
                                   1 << 5, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 14);

  ASSERT_EQ(machineInstructions1.at(0).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(0).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(1).getType(), MachineInstruction::MOV_A_AT_B);
  ASSERT_EQ(machineInstructions1.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(2).getType(), MachineInstruction::MOV_AT_ABS_A_ZP);
  ASSERT_EQ(machineInstructions1.at(2).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(2).getOperands(), std::vector<std::string>{"0b00100000"});

  ASSERT_EQ(machineInstructions1.at(3).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(3).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(4).getType(), MachineInstruction::MOV_B_AT_A);
  ASSERT_EQ(machineInstructions1.at(4).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(5).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(5).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(5).getOperands(), std::vector<std::string>{"0b00100010"});

  ASSERT_EQ(machineInstructions1.at(6).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions1.at(6).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(7).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions1.at(7).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(8).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(8).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(9).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(9).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(9).getOperands(), std::vector<std::string>{"0b00100011"});

  ASSERT_EQ(machineInstructions1.at(10).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions1.at(10).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(11).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions1.at(11).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(12).getType(), MachineInstruction::MOV_AT_ABS_A_ZP);
  ASSERT_EQ(machineInstructions1.at(12).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(12).getOperands(), std::vector<std::string>{"0b00100001"});

  ASSERT_EQ(machineInstructions1.at(13).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(13).getOperands().size(), 0);

  // move memory to register - any register need memory cell (long address)    - case dst2 := [src2]
  // move memory to register - first register need memory cell (long address)  - case dst3 := [src3]
  // move memory to register - second register need memory cell (long address) - case dst1 := [src1]
  // move memory to register - each register need memory cell (long address)   - case dst4 := [src4]
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2),
                                   1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 14);

  ASSERT_EQ(machineInstructions2.at(0).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(0).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(1).getType(), MachineInstruction::MOV_A_AT_B);
  ASSERT_EQ(machineInstructions2.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(2).getType(), MachineInstruction::MOV_AT_ABS_A);
  ASSERT_EQ(machineInstructions2.at(2).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(2).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));

  ASSERT_EQ(machineInstructions2.at(3).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(3).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(4).getType(), MachineInstruction::MOV_B_AT_A);
  ASSERT_EQ(machineInstructions2.at(4).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(5).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(5).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(5).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000010"}));

  ASSERT_EQ(machineInstructions2.at(6).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions2.at(6).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(7).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions2.at(7).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(8).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(8).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(9).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(9).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(9).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000011"}));

  ASSERT_EQ(machineInstructions2.at(10).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions2.at(10).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(11).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions2.at(11).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(12).getType(), MachineInstruction::MOV_AT_ABS_A);
  ASSERT_EQ(machineInstructions2.at(12).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(12).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));

  ASSERT_EQ(machineInstructions2.at(13).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(13).getOperands().size(), 0);
}

TEST(instructionToMachineInstructionConversion, movesVV_MemoryToMemory) {
  // move memory to memory - any register need memory cell (short address)    - case [dst2] := [src2]
  // move memory to memory - first register need memory cell (short address)  - case [dst3] := [src3]
  // move memory to memory - second register need memory cell (short address) - case [dst1] := [src1]
  // move memory to memory - each register need memory cell (short address)   - case [dst4] := [src4]
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1),
                                   1 << 5, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 20);

  ASSERT_EQ(machineInstructions1.at(0).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(0).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(1).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(1).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(1).getOperands(), std::vector<std::string>{"0b00100000"});

  ASSERT_EQ(machineInstructions1.at(2).getType(), MachineInstruction::MOV_TH_AT_B);
  ASSERT_EQ(machineInstructions1.at(2).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(3).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions1.at(3).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(4).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(4).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(5).getType(), MachineInstruction::MOV_TL_AT_A);
  ASSERT_EQ(machineInstructions1.at(5).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(6).getType(), MachineInstruction::MOV_AT_B_TL);
  ASSERT_EQ(machineInstructions1.at(6).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(7).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions1.at(7).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(8).getType(), MachineInstruction::MOV_B_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(8).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(8).getOperands(), std::vector<std::string>{"0b00100010"});

  ASSERT_EQ(machineInstructions1.at(9).getType(), MachineInstruction::MOV_TH_AT_B);
  ASSERT_EQ(machineInstructions1.at(9).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(10).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions1.at(10).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(11).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions1.at(11).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(12).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(12).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(13).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions1.at(13).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(14).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(14).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(14).getOperands(), std::vector<std::string>{"0b00100011"});

  ASSERT_EQ(machineInstructions1.at(15).getType(), MachineInstruction::MOV_B_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(15).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(15).getOperands(), std::vector<std::string>{"0b00100001"});

  ASSERT_EQ(machineInstructions1.at(16).getType(), MachineInstruction::MOV_TH_AT_A);
  ASSERT_EQ(machineInstructions1.at(16).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(17).getType(), MachineInstruction::MOV_AT_B_TH);
  ASSERT_EQ(machineInstructions1.at(17).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(18).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions1.at(18).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(19).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(19).getOperands().size(), 0);

  // move memory to memory - any register need memory cell (long address)    - case [dst2] := [src2]
  // move memory to memory - first register need memory cell (long address)  - case [dst3] := [src3]
  // move memory to memory - second register need memory cell (long address) - case [dst1] := [src1]
  // move memory to memory - each register need memory cell (long address)   - case [dst4] := [src4]
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2),
                                   1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 20);

  ASSERT_EQ(machineInstructions2.at(0).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(0).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(1).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(1).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(1).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));

  ASSERT_EQ(machineInstructions2.at(2).getType(), MachineInstruction::MOV_TH_AT_B);
  ASSERT_EQ(machineInstructions2.at(2).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(3).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions2.at(3).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(4).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(4).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(5).getType(), MachineInstruction::MOV_TL_AT_A);
  ASSERT_EQ(machineInstructions2.at(5).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(6).getType(), MachineInstruction::MOV_AT_B_TL);
  ASSERT_EQ(machineInstructions2.at(6).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(7).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions2.at(7).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(8).getType(), MachineInstruction::MOV_B_ABS);
  ASSERT_EQ(machineInstructions2.at(8).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(8).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000010"}));

  ASSERT_EQ(machineInstructions2.at(9).getType(), MachineInstruction::MOV_TH_AT_B);
  ASSERT_EQ(machineInstructions2.at(9).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(10).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions2.at(10).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(11).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions2.at(11).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(12).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(12).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(13).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions2.at(13).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(14).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(14).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(14).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000011"}));

  ASSERT_EQ(machineInstructions2.at(15).getType(), MachineInstruction::MOV_B_ABS);
  ASSERT_EQ(machineInstructions2.at(15).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(15).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));

  ASSERT_EQ(machineInstructions2.at(16).getType(), MachineInstruction::MOV_TH_AT_A);
  ASSERT_EQ(machineInstructions2.at(16).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(17).getType(), MachineInstruction::MOV_AT_B_TH);
  ASSERT_EQ(machineInstructions2.at(17).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(18).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions2.at(18).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(19).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(19).getOperands().size(), 0);
}

TEST(instructionToMachineInstructionConversion, movesVN_ConstantToRegister) {
  // move constant to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVN>("src", 42, BBMoveVN::SourceType::CONSTANT, BBMoveVN::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src"}, {}, std::move(basicBlock1), 0, machineInstructions1),
               std::invalid_argument);
}

TEST(instructionToMachineInstructionConversion, movesVN_ConstantToMemory) {
  // move constant to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVN>("src", 42, BBMoveVN::SourceType::CONSTANT, BBMoveVN::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src"}, {}, std::move(basicBlock1), 0, machineInstructions1),
               std::invalid_argument);
}

TEST(instructionToMachineInstructionConversion, movesVN_RegisterToRegister) {
  // move register to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVN>("src", 42, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src"}, {}, std::move(basicBlock1), 0, machineInstructions1),
               std::invalid_argument);
}

TEST(instructionToMachineInstructionConversion, movesVN_RegisterToMemory) {
  // move register to memory - register does not need memory cell (uint8, short address)      - case [42] := src1
  // move register to memory - register does not need memory cell (uint16, short address)     - case [1410] := src2
  // move register to memory - register need memory cell (uint8, short address)               - case [42] := src3
  // move register to memory - register need memory cell (uint16, short address)              - case [1410] := src4
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVN>("src1", 42, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVN>("src2", 1410, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVN>("src3", 42, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVN>("src4", 1410, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 5, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 6);

  ASSERT_EQ(machineInstructions1.at(0).getType(), MachineInstruction::MOV_AT_ABS_B_ZP);
  ASSERT_EQ(machineInstructions1.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(0).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions1.at(1).getType(), MachineInstruction::MOV_AT_ABS_A);
  ASSERT_EQ(machineInstructions1.at(1).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(1).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions1.at(2).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(2).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(2).getOperands(), std::vector<std::string>{"0b00100000"});

  ASSERT_EQ(machineInstructions1.at(3).getType(), MachineInstruction::POP_MEM_ZP);
  ASSERT_EQ(machineInstructions1.at(3).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(3).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions1.at(4).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(4).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(4).getOperands(), std::vector<std::string>{"0b00100001"});

  ASSERT_EQ(machineInstructions1.at(5).getType(), MachineInstruction::POP_MEM);
  ASSERT_EQ(machineInstructions1.at(5).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(5).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  // move register to memory - register does not need memory cell (uint8, long address)      - case [42] := src1
  // move register to memory - register does not need memory cell (uint16, long address)     - case [1410] := src2
  // move register to memory - register need memory cell (uint8, long address)               - case [42] := src3
  // move register to memory - register need memory cell (uint16, long address)              - case [1410] := src4
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVN>("src1", 42, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVN>("src2", 1410, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVN>("src3", 42, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVN>("src4", 1410, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 6);

  ASSERT_EQ(machineInstructions2.at(0).getType(), MachineInstruction::MOV_AT_ABS_B_ZP);
  ASSERT_EQ(machineInstructions2.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(0).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions2.at(1).getType(), MachineInstruction::MOV_AT_ABS_A);
  ASSERT_EQ(machineInstructions2.at(1).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(1).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions2.at(2).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(2).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(2).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));

  ASSERT_EQ(machineInstructions2.at(3).getType(), MachineInstruction::POP_MEM_ZP);
  ASSERT_EQ(machineInstructions2.at(3).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(3).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions2.at(4).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(4).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(4).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));

  ASSERT_EQ(machineInstructions2.at(5).getType(), MachineInstruction::POP_MEM);
  ASSERT_EQ(machineInstructions2.at(5).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(5).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
}

TEST(instructionToMachineInstructionConversion, movesVN_MemoryToRegister) {
  // move memory to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVN>("src", 42, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src"}, {}, std::move(basicBlock1), 0, machineInstructions1),
               std::invalid_argument);
}

TEST(instructionToMachineInstructionConversion, movesVN_MemoryToMemory) {
  // move memory to memory - register does not need memory cell (uint8, short address)    - case [42] := [src1]
  // move memory to memory - register does not need memory cell (uint16, short address)   - case [1410] := [src2]
  // move memory to memory - register need memory cell (uint8, short address)             - case [42] := [src3]
  // move memory to memory - register need memory cell (uint16, short address)            - case [1410] := [src4]
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVN>("src1", 42, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVN>("src2", 1410, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVN>("src3", 42, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVN>("src4", 1410, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 5, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 20);

  ASSERT_EQ(machineInstructions1.at(0).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(0).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(1).getType(), MachineInstruction::MOV_A_AT_B);
  ASSERT_EQ(machineInstructions1.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(2).getType(), MachineInstruction::MOV_AT_ABS_A_ZP);
  ASSERT_EQ(machineInstructions1.at(2).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(2).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions1.at(3).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(3).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(4).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions1.at(4).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(5).getType(), MachineInstruction::MOV_B_AT_A);
  ASSERT_EQ(machineInstructions1.at(5).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(6).getType(), MachineInstruction::MOV_AT_ABS_B);
  ASSERT_EQ(machineInstructions1.at(6).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(6).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions1.at(7).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions1.at(7).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(8).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(8).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(9).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(9).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(9).getOperands(), (std::vector<std::string>{"0b00100000"}));

  ASSERT_EQ(machineInstructions1.at(10).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions1.at(10).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(11).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions1.at(11).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(12).getType(), MachineInstruction::MOV_AT_ABS_A_ZP);
  ASSERT_EQ(machineInstructions1.at(12).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(12).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions1.at(13).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(13).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(14).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(14).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(15).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(15).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(15).getOperands(), (std::vector<std::string>{"0b00100001"}));

  ASSERT_EQ(machineInstructions1.at(16).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions1.at(16).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(17).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions1.at(17).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(18).getType(), MachineInstruction::MOV_AT_ABS_A);
  ASSERT_EQ(machineInstructions1.at(18).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(18).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions1.at(19).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(19).getOperands().size(), 0);

  // move memory to memory - register does not need memory cell (uint8, long address)     - case [42] := [src1]
  // move memory to memory - register does not need memory cell (uint16, long address)    - case [1410] := [src2]
  // move memory to memory - register need memory cell (uint8, long address)              - case [42] := [src3]
  // move memory to memory - register need memory cell (uint16, long address)             - case [1410] := [src4]
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVN>("src1", 42, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVN>("src2", 1410, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVN>("src3", 42, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveVN>("src4", 1410, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 20);

  ASSERT_EQ(machineInstructions2.at(0).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(0).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(1).getType(), MachineInstruction::MOV_A_AT_B);
  ASSERT_EQ(machineInstructions2.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(2).getType(), MachineInstruction::MOV_AT_ABS_A_ZP);
  ASSERT_EQ(machineInstructions2.at(2).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(2).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions2.at(3).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(3).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(4).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions2.at(4).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(5).getType(), MachineInstruction::MOV_B_AT_A);
  ASSERT_EQ(machineInstructions2.at(5).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(6).getType(), MachineInstruction::MOV_AT_ABS_B);
  ASSERT_EQ(machineInstructions2.at(6).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(6).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions2.at(7).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions2.at(7).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(8).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(8).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(9).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(9).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(9).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));

  ASSERT_EQ(machineInstructions2.at(10).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions2.at(10).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(11).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions2.at(11).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(12).getType(), MachineInstruction::MOV_AT_ABS_A_ZP);
  ASSERT_EQ(machineInstructions2.at(12).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(12).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions2.at(13).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(13).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(14).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(14).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(15).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(15).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(15).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));

  ASSERT_EQ(machineInstructions2.at(16).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions2.at(16).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(17).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions2.at(17).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(18).getType(), MachineInstruction::MOV_AT_ABS_A);
  ASSERT_EQ(machineInstructions2.at(18).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(18).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions2.at(19).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(19).getOperands().size(), 0);
}

TEST(instructionToMachineInstructionConversion, movesNV_ConstantToRegister) {
  // move constant to register - register does not need memory cell (short address)   - case src2 := 42
  // move constant to register - register need memory cell (short address)            - case src3 := 42
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst2", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst3", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock1), 1 << 5, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 2);

  ASSERT_EQ(machineInstructions1.at(0).getType(), MachineInstruction::MOV_A_IMM);
  ASSERT_EQ(machineInstructions1.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(0).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions1.at(1).getType(), MachineInstruction::MOV_AT_ABS_IMM_ZP);
  ASSERT_EQ(machineInstructions1.at(1).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(1).getOperands(), (std::vector<std::string>{"0b00100000", "0b00101010"}));

  // move constant to register - register does not need memory cell (long address)   - case src2 := 42
  // move constant to register - register need memory cell (long address)            - case src3 := 42
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst2", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst3", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 2);

  ASSERT_EQ(machineInstructions2.at(0).getType(), MachineInstruction::MOV_A_IMM);
  ASSERT_EQ(machineInstructions2.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(0).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions2.at(1).getType(), MachineInstruction::MOV_AT_ABS_IMM);
  ASSERT_EQ(machineInstructions2.at(1).getOperands().size(), 3);
  ASSERT_EQ(machineInstructions2.at(1).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000", "0b00101010"}));
}

TEST(instructionToMachineInstructionConversion, movesNV_ConstantToMemory) {
  // move constant to memory - register does not need memory cell (short address)   - case [src2] := 42
  // move constant to memory - register need memory cell (short address)            - case [src3] := 42
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst2", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst3", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock1), 1 << 5, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 4);

  ASSERT_EQ(machineInstructions1.at(0).getType(), MachineInstruction::MOV_AT_A_IMM);
  ASSERT_EQ(machineInstructions1.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(0).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions1.at(1).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(1).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(1).getOperands(), std::vector<std::string>{"0b00100000"});

  ASSERT_EQ(machineInstructions1.at(2).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions1.at(2).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(3).getType(), MachineInstruction::MOV_AT_TL_IMM);
  ASSERT_EQ(machineInstructions1.at(3).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(3).getOperands(), std::vector<std::string>{"0b00101010"});

  // move constant to memory - register does not need memory cell (long address)   - case [src2] := 42
  // move constant to memory - register need memory cell (long address)            - case [src3] := 42
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst2", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst3", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 4);

  ASSERT_EQ(machineInstructions2.at(0).getType(), MachineInstruction::MOV_AT_A_IMM);
  ASSERT_EQ(machineInstructions2.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(0).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions2.at(1).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(1).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(1).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));

  ASSERT_EQ(machineInstructions2.at(2).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions2.at(2).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(3).getType(), MachineInstruction::MOV_AT_TL_IMM);
  ASSERT_EQ(machineInstructions2.at(3).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(3).getOperands(), std::vector<std::string>{"0b00101010"});
}

TEST(instructionToMachineInstructionConversion, movesNV_RegisterToRegister) {
  // move register to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst", BBMoveNV::SourceType::REGISTER, BBMoveNV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1),
               std::invalid_argument);
}

TEST(instructionToMachineInstructionConversion, movesNV_RegisterToMemory) {
  // move register to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst", BBMoveNV::SourceType::REGISTER, BBMoveNV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"dst"}, {}, std::move(basicBlock1), 0, machineInstructions1),
               std::invalid_argument);
}

TEST(instructionToMachineInstructionConversion, movesNV_MemoryToRegister) {
  // move memory to register - register does not need memory cell (uint8, short address)      - case dst1 := [42]
  // move memory to register - register does not need memory cell (uint16, short address)     - case dst2 := [1410]
  // move memory to register - register need memory cell (uint8, short address)               - case dst3 := [42]
  // move memory to register - register need memory cell (uint16, short address)              - case dst4 := [1410]
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst1", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(1410, "dst2", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst3", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(1410, "dst4", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 5, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 6);

  ASSERT_EQ(machineInstructions1.at(0).getType(), MachineInstruction::MOV_B_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(0).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions1.at(1).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions1.at(1).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(1).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions1.at(2).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(2).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(2).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions1.at(3).getType(), MachineInstruction::POP_MEM_ZP);
  ASSERT_EQ(machineInstructions1.at(3).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(3).getOperands(), std::vector<std::string>{"0b00100000"});

  ASSERT_EQ(machineInstructions1.at(4).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions1.at(4).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(4).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions1.at(5).getType(), MachineInstruction::POP_MEM_ZP);
  ASSERT_EQ(machineInstructions1.at(5).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(5).getOperands(), std::vector<std::string>{"0b00100001"});

  // move memory to register - register does not need memory cell (uint8, long address)       - case dst1 := [42]
  // move memory to register - register does not need memory cell (uint16, long address)      - case dst2 := [1410]
  // move memory to register - register need memory cell (uint8, long address)                - case dst3 := [42]
  // move memory to register - register need memory cell (uint16, long address)               - case dst4 := [1410]
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst1", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(1410, "dst2", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst3", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(1410, "dst4", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 6);

  ASSERT_EQ(machineInstructions2.at(0).getType(), MachineInstruction::MOV_B_ABS_ZP);
  ASSERT_EQ(machineInstructions2.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(0).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions2.at(1).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(1).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(1).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions2.at(2).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions2.at(2).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(2).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions2.at(3).getType(), MachineInstruction::POP_MEM);
  ASSERT_EQ(machineInstructions2.at(3).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(3).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));

  ASSERT_EQ(machineInstructions2.at(4).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(4).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(4).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions2.at(5).getType(), MachineInstruction::POP_MEM);
  ASSERT_EQ(machineInstructions2.at(5).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(5).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));
}

TEST(instructionToMachineInstructionConversion, movesNV_MemoryToMemory) {
  // move memory to memory - register does not need memory cell (uint8, short address)        - case [dst1] := [42]
  // move memory to memory - register does not need memory cell (uint16, short address)       - case [dst2] := [1410]
  // move memory to memory - register need memory cell (uint8, short address)                 - case [dst3] := [42]
  // move memory to memory - register need memory cell (uint16, short address)                - case [dst4] := [1410]
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst1", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(1410, "dst2", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst3", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(1410, "dst4", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 5, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 16);

  ASSERT_EQ(machineInstructions1.at(0).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(0).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions1.at(1).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions1.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(2).getType(), MachineInstruction::MOV_AT_B_TL);
  ASSERT_EQ(machineInstructions1.at(2).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(3).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions1.at(3).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(3).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions1.at(4).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions1.at(4).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(5).getType(), MachineInstruction::MOV_AT_A_TL);
  ASSERT_EQ(machineInstructions1.at(5).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(6).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(6).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(6).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions1.at(7).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(7).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(7).getOperands(), std::vector<std::string>{"0b00100000"});

  ASSERT_EQ(machineInstructions1.at(8).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions1.at(8).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(9).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions1.at(9).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(10).getType(), MachineInstruction::MOV_AT_TL_TH);
  ASSERT_EQ(machineInstructions1.at(10).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(11).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions1.at(11).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(11).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions1.at(12).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(12).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(12).getOperands(), std::vector<std::string>{"0b00100001"});

  ASSERT_EQ(machineInstructions1.at(13).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions1.at(13).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(14).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions1.at(14).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions1.at(15).getType(), MachineInstruction::MOV_AT_TL_TH);
  ASSERT_EQ(machineInstructions1.at(15).getOperands().size(), 0);

  // move memory to memory - register does not need memory cell (uint8, long address)         - case [dst1] := [42]
  // move memory to memory - register does not need memory cell (uint16, long address)        - case [dst2] := [1410]
  // move memory to memory - register need memory cell (uint8, long address)                  - case [dst3] := [42]
  // move memory to memory - register need memory cell (uint16, long address)                 - case [dst4] := [1410]
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst1", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(1410, "dst2", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst3", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(1410, "dst4", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 16);

  ASSERT_EQ(machineInstructions2.at(0).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions2.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(0).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions2.at(1).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions2.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(2).getType(), MachineInstruction::MOV_AT_B_TL);
  ASSERT_EQ(machineInstructions2.at(2).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(3).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(3).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(3).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions2.at(4).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions2.at(4).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(5).getType(), MachineInstruction::MOV_AT_A_TL);
  ASSERT_EQ(machineInstructions2.at(5).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(6).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions2.at(6).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(6).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions2.at(7).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(7).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(7).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));

  ASSERT_EQ(machineInstructions2.at(8).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions2.at(8).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(9).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions2.at(9).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(10).getType(), MachineInstruction::MOV_AT_TL_TH);
  ASSERT_EQ(machineInstructions2.at(10).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(11).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(11).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(11).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions2.at(12).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(12).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(12).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));

  ASSERT_EQ(machineInstructions2.at(13).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions2.at(13).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(14).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions2.at(14).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(15).getType(), MachineInstruction::MOV_AT_TL_TH);
  ASSERT_EQ(machineInstructions2.at(15).getOperands().size(), 0);
}

TEST(instructionToMachineInstructionConversion, movesNN_ConstantToRegister) {
  // move constant to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(37, 42, BBMoveNN::SourceType::CONSTANT, BBMoveNN::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST(instructionToMachineInstructionConversion, movesNN_ConstantToMemory) {
  // move constant to memory - int8     - case [42] := 37
  // move constant to memory - int16    - case [1410] := 37
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(37, 42, BBMoveNN::SourceType::CONSTANT, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(37, 1410, BBMoveNN::SourceType::CONSTANT, BBMoveNN::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 1 << 5, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 2);

  ASSERT_EQ(machineInstructions1.at(0).getType(), MachineInstruction::MOV_AT_ABS_IMM_ZP);
  ASSERT_EQ(machineInstructions1.at(0).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(0).getOperands(), (std::vector<std::string>{"0b00101010", "0b00100101"}));

  ASSERT_EQ(machineInstructions1.at(1).getType(), MachineInstruction::MOV_AT_ABS_IMM);
  ASSERT_EQ(machineInstructions1.at(1).getOperands().size(), 3);
  ASSERT_EQ(machineInstructions1.at(1).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010", "0b00100101"}));
}

TEST(instructionToMachineInstructionConversion, movesNN_RegisterToRegister) {
  // move register to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(37, 42, BBMoveNN::SourceType::REGISTER, BBMoveNN::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST(instructionToMachineInstructionConversion, movesNN_RegisterToMemory) {
  // move register to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(37, 42, BBMoveNN::SourceType::REGISTER, BBMoveNN::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST(instructionToMachineInstructionConversion, movesNN_MemoryToRegister) {
  // move memory to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(37, 42, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST(instructionToMachineInstructionConversion, movesNN_MemoryToMemory) {
  // move memory to memory - int8, int8     - case [37] := [42]
  // move memory to memory - int8, int16    - case [1410] := [42]
  // move memory to memory - int16, int8    - case [37] := [1410]
  // move memory to memory - int16, int16   - case [1410] := [1920]
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveNN>(42, 37, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(42, 1410, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(1920, 37, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(1920, 1410, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 1 << 5, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 8);

  ASSERT_EQ(machineInstructions1.at(0).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(0).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions1.at(1).getType(), MachineInstruction::POP_MEM_ZP);
  ASSERT_EQ(machineInstructions1.at(1).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(1).getOperands(), std::vector<std::string>{"0b00100101"});

  ASSERT_EQ(machineInstructions1.at(2).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(2).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(2).getOperands(), std::vector<std::string>{"0b00101010"});

  ASSERT_EQ(machineInstructions1.at(3).getType(), MachineInstruction::POP_MEM);
  ASSERT_EQ(machineInstructions1.at(3).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(3).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));

  ASSERT_EQ(machineInstructions1.at(4).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions1.at(4).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(4).getOperands(), (std::vector<std::string>{"0b00000111", "0b10000000"}));

  ASSERT_EQ(machineInstructions1.at(5).getType(), MachineInstruction::POP_MEM_ZP);
  ASSERT_EQ(machineInstructions1.at(5).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(5).getOperands(), std::vector<std::string>{"0b00100101"});

  ASSERT_EQ(machineInstructions1.at(6).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions1.at(6).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(6).getOperands(), (std::vector<std::string>{"0b00000111", "0b10000000"}));

  ASSERT_EQ(machineInstructions1.at(7).getType(), MachineInstruction::POP_MEM);
  ASSERT_EQ(machineInstructions1.at(7).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(7).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
}

//TEST(instructionToMachineInstructionConversion, unaryOperations) {
//  const std::vector<std::pair<BBUnaryOperationEnum, MachineInstruction::Type::NEG_A_A>> operations = {
//      BBUnaryOperationEnum::NEG, BBUnaryOperationEnum::NOT, BBUnaryOperationEnum::INC,
//      BBUnaryOperationEnum::DEC, BBUnaryOperationEnum::SHL, BBUnaryOperationEnum::SHL,
//      BBUnaryOperationEnum::SAR};
//
//  for (const auto operation : operations) {
//    BasicBlock basicBlock;
//    basicBlock2.addInstruction(std::make_unique<BBMoveNV>(0, "src", BBMoveVV::SourceType::CONSTANT,
//                                                                  BBMoveVV::DestinationType::REGISTER));
//    basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>(
//        "src", "dst", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER,
//        BBUnaryOperationEnum::NEG));
//
//    std::vector<MachineInstruction> machineInstructions;
//    std::stringstream tmp;
//    translateBasicBlockToMachineCode(std::move(basicBlock), machineInstructions, tmp);
//
//    std::cout << "Machine instructions: " << std::endl;
//    for (const auto& machineInstruction : machineInstructions) {
//      std::cout << machineInstruction.toString() << std::endl;
//    }
//
//    ASSERT_EQ(machineInstructions.size(), 3);
//    ASSERT_EQ(machineInstructions[0].getType(), MachineInstruction::Type::LABEL);
//    ASSERT_EQ(machineInstructions[0].getOperands().size(), 1);
//    ASSERT_EQ(machineInstructions[0].getOperands()[0], "main");
//    ASSERT_EQ(machineInstructions[1].getType(), operation.second);
//    ASSERT_EQ(machineInstructions[1].getOperands().size(), 1);
//    ASSERT_EQ(machineInstructions[1].getOperands()[0], "0b00000000");
//    ASSERT_EQ(machineInstructions[2].getType(), MachineInstruction::Type::NEG_A_A);
//    ASSERT_EQ(machineInstructions[2].getOperands().size(), 0);
//  }
//}

//TEST(instructionToMachineInstructionConversion, binaryOperations) {}

//TEST(instructionToMachineInstructionConversion, branches) {}

//TEST(instructionToMachineInstructionConversion, calls) {}

//TEST(instructionToMachineInstructionConversion, returns) {}

//TEST(instructionToMachineInstructionConversion, phis) {}

//TEST(instructionToMachineInstructionConversion, halts) {}

//TEST(instructionToMachineInstructionConversion, builtinFunctions) {}

//TEST(toMcConversion, liveRanges) {}

//TEST(toMcConversion, linearScanAllocation) {}

//TEST(toMcConversion, graphColoringAllocation) {}

//TEST(toMcConversion, ifs) {}

//TEST(toMcConversion, cases) {}

//TEST(toMcConversion, forLoops) {}

//TEST(toMcConversion, whileLoops) {}

//TEST(toMcConversion, repeatLoops) {}

//TEST(toMcConversion, functions) {}

//TEST(toMcConversion, recursion) {}

//TEST(toMcConversion, enumerations) {}

//TEST(toMcConversion, arrays) {}

//TEST(toMcConversion, records) {}