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

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program);

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

TEST(instructionToMachineInstructionConversion, movesVV) {
  // move constant to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveVV>("src", "dst", BBMoveVV::SourceType::CONSTANT, BBMoveVV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src", "dst"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1),
               std::invalid_argument);

  // move register to register - any register need memory cell (short address)    - case dst2 := src2
  // move register to register - first register need memory cell (short address)  - case dst3 := dst3
  // move register to register - second register need memory cell (short address) - case dst1 := src1
  // move register to register - each register need memory cell (short address)   - case dst4 := src4
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
                                   1 << 5, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 5);

  ASSERT_EQ(machineInstructions2.at(0).getType(), MachineInstruction::MOV_AT_ABS_B_ZP);
  ASSERT_EQ(machineInstructions2.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(0).getOperands(), std::vector<std::string>{"0b00100000"});

  ASSERT_EQ(machineInstructions2.at(1).getType(), MachineInstruction::MOV_B_A);
  ASSERT_EQ(machineInstructions2.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions2.at(2).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions2.at(2).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(2).getOperands(), std::vector<std::string>{"0b00100010"});

  ASSERT_EQ(machineInstructions2.at(3).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions2.at(3).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(3).getOperands(), std::vector<std::string>{"0b00100011"});

  ASSERT_EQ(machineInstructions2.at(4).getType(), MachineInstruction::POP_MEM_ZP);
  ASSERT_EQ(machineInstructions2.at(4).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(4).getOperands(), std::vector<std::string>{"0b00100001"});

  // move register to register - any register need memory cell (long address)    - case dst2 := src2
  // move register to register - first register need memory cell (long address)  - case dst3 := dst3
  // move register to register - second register need memory cell (long address) - case dst1 := src1
  // move register to register - each register need memory cell (long address)   - case dst4 := src4
  BasicBlock basicBlock3;
  basicBlock3.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock3.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock3.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock3.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions3;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock3),
                                   1 << 10, machineInstructions3);

  ASSERT_EQ(machineInstructions3.size(), 5);

  ASSERT_EQ(machineInstructions3.at(0).getType(), MachineInstruction::MOV_AT_ABS_B);
  ASSERT_EQ(machineInstructions3.at(0).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions3.at(0).getOperands(), (std::vector<std::string>{"0b00000000", "0b00000100"}));

  ASSERT_EQ(machineInstructions3.at(1).getType(), MachineInstruction::MOV_B_A);
  ASSERT_EQ(machineInstructions3.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions3.at(2).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions3.at(2).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions3.at(2).getOperands(), (std::vector<std::string>{"0b00000010", "0b00000100"}));

  ASSERT_EQ(machineInstructions3.at(3).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions3.at(3).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions3.at(3).getOperands(), (std::vector<std::string>{"0b00000011", "0b00000100"}));

  ASSERT_EQ(machineInstructions3.at(4).getType(), MachineInstruction::POP_MEM);
  ASSERT_EQ(machineInstructions3.at(4).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions3.at(4).getOperands(), (std::vector<std::string>{"0b00000001", "0b00000100"}));

  // move register to memory - any register need memory cell (short address)    - case [dst2] := src2
  // move register to memory - first register need memory cell (short address)  - case [dst3] := dst3
  // move register to memory - second register need memory cell (short address) - case [dst1] := src1
  // move register to memory - each register need memory cell (short address)   - case [dst4] := src4
  BasicBlock basicBlock4;
  basicBlock4.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock4.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock4.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock4.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions4;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock4),
                                   1 << 5, machineInstructions4);

  ASSERT_EQ(machineInstructions4.size(), 13);

  ASSERT_EQ(machineInstructions4.at(0).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions4.at(0).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions4.at(0).getOperands(), std::vector<std::string>{"0b00100000"});

  ASSERT_EQ(machineInstructions4.at(1).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions4.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions4.at(2).getType(), MachineInstruction::MOV_AT_TL_B);
  ASSERT_EQ(machineInstructions4.at(2).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions4.at(3).getType(), MachineInstruction::MOV_TL_B);
  ASSERT_EQ(machineInstructions4.at(3).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions4.at(4).getType(), MachineInstruction::MOV_AT_B_A);
  ASSERT_EQ(machineInstructions4.at(4).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions4.at(5).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions4.at(5).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions4.at(5).getOperands(), std::vector<std::string>{"0b00100010"});

  ASSERT_EQ(machineInstructions4.at(6).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions4.at(6).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions4.at(7).getType(), MachineInstruction::MOV_AT_A_TL);
  ASSERT_EQ(machineInstructions4.at(7).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions4.at(8).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions4.at(8).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions4.at(8).getOperands(), std::vector<std::string>{"0b00100011"});

  ASSERT_EQ(machineInstructions4.at(9).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions4.at(9).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions4.at(10).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions4.at(10).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions4.at(10).getOperands(), std::vector<std::string>{"0b00100001"});

  ASSERT_EQ(machineInstructions4.at(11).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions4.at(11).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions4.at(12).getType(), MachineInstruction::MOV_AT_TL_TH);
  ASSERT_EQ(machineInstructions4.at(12).getOperands().size(), 0);

  // move register to memory - any register need memory cell (long address)     - case [dst2] := src2
  // move register to memory - first register need memory cell (long address)   - case [dst3] := dst3
  // move register to memory - second register need memory cell (long address)  - case [dst1] := src1
  // move register to memory - each register need memory cell (long address)    - case [dst4] := src4
  BasicBlock basicBlock5;
  basicBlock5.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock5.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock5.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock5.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions5;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock5),
                                   1 << 10, machineInstructions5);

  ASSERT_EQ(machineInstructions5.size(), 13);

  ASSERT_EQ(machineInstructions5.at(0).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions5.at(0).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions5.at(0).getOperands(), (std::vector<std::string>{"0b00000000", "0b00000100"}));

  ASSERT_EQ(machineInstructions5.at(1).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions5.at(1).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions5.at(2).getType(), MachineInstruction::MOV_AT_TL_B);
  ASSERT_EQ(machineInstructions5.at(2).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions5.at(3).getType(), MachineInstruction::MOV_TL_B);
  ASSERT_EQ(machineInstructions5.at(3).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions5.at(4).getType(), MachineInstruction::MOV_AT_B_A);
  ASSERT_EQ(machineInstructions5.at(4).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions5.at(5).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions5.at(5).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions5.at(5).getOperands(), (std::vector<std::string>{"0b00000010", "0b00000100"}));

  ASSERT_EQ(machineInstructions5.at(6).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions5.at(6).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions5.at(7).getType(), MachineInstruction::MOV_AT_A_TL);
  ASSERT_EQ(machineInstructions5.at(7).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions5.at(8).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions5.at(8).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions5.at(8).getOperands(), (std::vector<std::string>{"0b00000011", "0b00000100"}));

  ASSERT_EQ(machineInstructions5.at(9).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions5.at(9).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions5.at(10).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions5.at(10).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions5.at(10).getOperands(), (std::vector<std::string>{"0b00000001", "0b00000100"}));

  ASSERT_EQ(machineInstructions5.at(11).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions5.at(11).getOperands().size(), 0);

  ASSERT_EQ(machineInstructions5.at(12).getType(), MachineInstruction::MOV_AT_TL_TH);
  ASSERT_EQ(machineInstructions5.at(12).getOperands().size(), 0);

  // move constant to memory - not allowed for this template specialization
  BasicBlock basicBlock6;
  basicBlock6.addInstruction(
      std::make_unique<BBMoveVV>("src", "dst", BBMoveVV::SourceType::CONSTANT, BBMoveVV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions6;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src", "dst"}, {"dst"}, std::move(basicBlock6), 0, machineInstructions6),
               std::invalid_argument);

  // move memory to register - any register need memory cell (short address)    - case dst2 := [src2]
  // move memory to register - first register need memory cell (short address)  - case dst3 := [dst3]
  // move memory to register - second register need memory cell (short address) - case dst1 := [src1]
  // move memory to register - each register need memory cell (short address)   - case dst4 := [src4]
  BasicBlock basicBlock7;
  basicBlock7.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock7.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock7.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock7.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions7;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock7),
                                   1 << 5, machineInstructions7);

  // move memory to register - any register need memory cell (long address)    - case dst2 := [src2]
  // move memory to register - first register need memory cell (long address)  - case dst3 := [dst3]
  // move memory to register - second register need memory cell (long address) - case dst1 := [src1]
  // move memory to register - each register need memory cell (long address)   - case dst4 := [src4]
  BasicBlock basicBlock8;
  basicBlock8.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock8.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock8.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock8.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  std::vector<MachineInstruction> machineInstructions8;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock8),
                                   1 << 10, machineInstructions8);

  // move memory to memory - any register need memory cell (short address)    - case [dst2] := [src2]
  // move memory to memory - first register need memory cell (short address)  - case [dst3] := [dst3]
  // move memory to memory - second register need memory cell (short address) - case [dst1] := [src1]
  // move memory to memory - each register need memory cell (short address)   - case [dst4] := [src4]
  BasicBlock basicBlock9;
  basicBlock9.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock9.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock9.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock9.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions9;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock9),
                                   1 << 5, machineInstructions9);

  // move memory to memory - any register need memory cell (long address)    - case [dst2] := [src2]
  // move memory to memory - first register need memory cell (long address)  - case [dst3] := [dst3]
  // move memory to memory - second register need memory cell (long address) - case [dst1] := [src1]
  // move memory to memory - each register need memory cell (long address)   - case [dst4] := [src4]
  BasicBlock basicBlock10;
  basicBlock10.addInstruction(
      std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock10.addInstruction(
      std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock10.addInstruction(
      std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock10.addInstruction(
      std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  std::vector<MachineInstruction> machineInstructions10;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock10),
                                   1 << 10, machineInstructions10);
}

TEST(instructionToMachineInstructionConversion, movesVN) {
  // move constant to register
  // move register to register
  // move memory to register

  // move constant to memory
  // move register to memory
  // move memory to memory
}

TEST(instructionToMachineInstructionConversion, movesNV) {
  // move constant to register
  // move register to register
  // move memory to register

  // move constant to memory
  // move register to memory
  // move memory to memory
}

TEST(instructionToMachineInstructionConversion, movesNN) {
  // move constant to register
  // move register to register
  // move memory to register

  // move constant to memory
  // move register to memory
  // move memory to memory
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