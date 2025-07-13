#include <iostream>
#include <ranges>

#include "gtest/gtest.h"

#include "../src/ast/program_node.hpp"
#include "../src/bblocks/bb_ssa_generator.hpp"
#include "../src/machine_code/machine_code_generator.hpp"
#include "emulator_connector.hpp"

using namespace bblocks;
using namespace machine_code;

void translateBasicBlockToBinaryCode(const std::vector<std::string>& readVariables,
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
  binaryCode.erase(binaryCode.end() - writeVariableStepsNumber * writeVariables.size() - 1, binaryCode.end());
}

void prepareEmulatorForTest(EmulatorConnector& emulator, const std::vector<uint8_t>& binaryCode,
                            const std::map<uint16_t, uint8_t>& nonZeroMemory = {}, uint8_t registerA = 0, uint8_t registerB = 0,
                            uint16_t instructionCounter = 0x0000, uint16_t stackPointer = 0xFFFF) {
  emulator.clearMemory();
  for (const auto& [address, value] : nonZeroMemory) {
    emulator.setMemory(address, value);
  }

  emulator.loadRom(binaryCode);

  emulator.setRegA(registerA);
  emulator.setRegB(registerB);

  emulator.setPc(instructionCounter);
  emulator.setStc(stackPointer);

  emulator.setClockCyclesCounter(0);
  emulator.setInstructionCounter(0);
}

/* Register allocation result for movesVV programs (short/long address):
 *
 * src1 -> regB, src2 -> regA, src3 -> [34/1026], src4 -> [35/1027]
 * dst1 -> [32/1024], dst2 -> regB, dst3 -> regA, dst4 -> [33/1025]
*/

TEST(instructionToBinaryCodeConversion, movesVV_RegisterToRegister) {
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
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1),
                                  1 << 5, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 9);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{34, 17}, {35, 21}}, 42, 37);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(1);  // dst1 := src1  ->  [32] := regB
  memorySnapshot1[32] = 37;
  ASSERT_EQ(emulator1.getRegA(), 42);
  ASSERT_EQ(emulator1.getRegB(), 37);
  ASSERT_EQ(emulator1.getMemory(32), 37);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // dst2 := src2  ->  regB := regA
  ASSERT_EQ(emulator1.getRegA(), 42);
  ASSERT_EQ(emulator1.getRegB(), 42);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // dst3 := src3  ->  regA := [34]
  ASSERT_EQ(emulator1.getRegA(), 17);
  ASSERT_EQ(emulator1.getRegB(), 42);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // dst4 := src4  ->  [33] := [35]
  memorySnapshot1[33] = memorySnapshot1[35];
  ASSERT_EQ(emulator1.getRegA(), 17);
  ASSERT_EQ(emulator1.getRegB(), 42);
  ASSERT_EQ(emulator1.getMemory(33), 21);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

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
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2),
                                  1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 13);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{1026, 17}, {1027, 21}}, 42, 37);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(1);  // dst1 := src1  ->  [1024] := regB
  memorySnapshot2[1024] = 37;
  ASSERT_EQ(emulator2.getRegA(), 42);
  ASSERT_EQ(emulator2.getRegB(), 37);
  ASSERT_EQ(emulator2.getMemory(1024), 37);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // dst2 := src2  ->  regB := regA
  ASSERT_EQ(emulator2.getRegA(), 42);
  ASSERT_EQ(emulator2.getRegB(), 42);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // dst3 := src3  ->  regA := [1026]
  ASSERT_EQ(emulator2.getRegA(), 17);
  ASSERT_EQ(emulator2.getRegB(), 42);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // dst4 := src4  ->  [1025] := [1027]
  memorySnapshot2[1025] = memorySnapshot2[1027];
  ASSERT_EQ(emulator2.getRegA(), 17);
  ASSERT_EQ(emulator2.getRegB(), 42);
  ASSERT_EQ(emulator2.getMemory(1025), 21);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(instructionToBinaryCodeConversion, movesVV_RegisterToMemory) {
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
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1),
                                  1 << 5, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 16);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{32, 67}, {33, 71}, {34, 77}, {35, 81}}, 92, 97);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(3);  // [dst1] := src1  ->  [[32]] := regB
  memorySnapshot1[memorySnapshot1[32]] = 97;
  ASSERT_EQ(emulator1.getRegA(), 92);
  ASSERT_EQ(emulator1.getRegB(), 97);
  ASSERT_EQ(emulator1.getMemory(67), 97);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // [dst2] := src2  ->  [regB] := regA
  memorySnapshot1[97] = 92;
  ASSERT_EQ(emulator1.getRegA(), 92);
  ASSERT_EQ(emulator1.getRegB(), 97);
  ASSERT_EQ(emulator1.getMemory(97), 92);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3);  // [dst3] := src3  ->  [regA] := [34]
  memorySnapshot1[92] = memorySnapshot1[34];
  ASSERT_EQ(emulator1.getRegA(), 92);
  ASSERT_EQ(emulator1.getRegB(), 97);
  ASSERT_EQ(emulator1.getMemory(92), 77);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(5);  // [dst4] := src4  ->  [[33]] := [35]
  memorySnapshot1[memorySnapshot1[33]] = memorySnapshot1[35];
  ASSERT_EQ(emulator1.getRegA(), 92);
  ASSERT_EQ(emulator1.getRegB(), 97);
  ASSERT_EQ(emulator1.getMemory(71), 81);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

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
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2),
                                  1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 20);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{1024, 67}, {1025, 71}, {1026, 77}, {1027, 81}}, 92, 97);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(3);  // [dst1] := src1  ->  [[1024]] := regB
  memorySnapshot2[memorySnapshot2[1024]] = 97;
  ASSERT_EQ(emulator2.getRegA(), 92);
  ASSERT_EQ(emulator2.getRegB(), 97);
  ASSERT_EQ(emulator2.getMemory(67), 97);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // [dst2] := src2  ->  [regB] := regA
  memorySnapshot2[97] = 92;
  ASSERT_EQ(emulator2.getRegA(), 92);
  ASSERT_EQ(emulator2.getRegB(), 97);
  ASSERT_EQ(emulator2.getMemory(97), 92);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3);  // [dst3] := src3  ->  [regA] := [1026]
  memorySnapshot2[92] = memorySnapshot2[1026];
  ASSERT_EQ(emulator2.getRegA(), 92);
  ASSERT_EQ(emulator2.getRegB(), 97);
  ASSERT_EQ(emulator2.getMemory(92), 77);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(5);  // [dst4] := src4  ->  [[1025]] := [1027]
  memorySnapshot2[memorySnapshot2[1025]] = memorySnapshot2[1027];
  ASSERT_EQ(emulator2.getRegA(), 92);
  ASSERT_EQ(emulator2.getRegB(), 97);
  ASSERT_EQ(emulator2.getMemory(71), 81);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(instructionToBinaryCodeConversion, movesVV_MemoryToRegister) {
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
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1),
                                  1 << 5, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 18);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(
      emulator1, binaryCode1,
      {{32, 67}, {33, 71}, {34, 77}, {35, 81}, {67, 87}, {71, 101}, {77, 107}, {81, 111}, {92, 112}, {97, 117}}, 92, 97);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(4);  // dst1 := [src1]  ->  [32] := [regB]
  memorySnapshot1[32] = 117;
  ASSERT_EQ(emulator1.getRegA(), 92);
  ASSERT_EQ(emulator1.getRegB(), 97);
  ASSERT_EQ(emulator1.getMemory(32), 117);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // dst2 := [src2]  ->  regB := [regA]
  ASSERT_EQ(emulator1.getRegA(), 92);
  ASSERT_EQ(emulator1.getRegB(), 112);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3);  // dst3 := [src3]  ->  regA := [[34]]
  ASSERT_EQ(emulator1.getRegA(), 107);
  ASSERT_EQ(emulator1.getRegB(), 112);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(6);  // dst4 := [src4]  ->  [33] := [[35]]
  memorySnapshot1[33] = memorySnapshot1[memorySnapshot1[35]];
  ASSERT_EQ(emulator1.getRegA(), 107);
  ASSERT_EQ(emulator1.getRegB(), 112);
  ASSERT_EQ(emulator1.getMemory(33), 111);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

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
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2),
                                  1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 22);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(
      emulator2, binaryCode2,
      {{1024, 67}, {1025, 71}, {1026, 77}, {1027, 81}, {67, 87}, {71, 101}, {77, 107}, {81, 111}, {92, 112}, {97, 117}}, 92, 97);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(4);  // dst1 := [src1]  ->  [1024] := [regB]
  memorySnapshot2[1024] = 117;
  ASSERT_EQ(emulator2.getRegA(), 92);
  ASSERT_EQ(emulator2.getRegB(), 97);
  ASSERT_EQ(emulator2.getMemory(1024), 117);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // dst2 := [src2]  ->  regB := [regA]
  ASSERT_EQ(emulator2.getRegA(), 92);
  ASSERT_EQ(emulator2.getRegB(), 112);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3);  // dst3 := [src3]  ->  regA := [[1026]]
  ASSERT_EQ(emulator2.getRegA(), 107);
  ASSERT_EQ(emulator2.getRegB(), 112);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(6);  // dst4 := [src4]  ->  [1025] := [[1027]]
  memorySnapshot2[1025] = memorySnapshot2[memorySnapshot2[1027]];
  ASSERT_EQ(emulator2.getRegA(), 107);
  ASSERT_EQ(emulator2.getRegB(), 112);
  ASSERT_EQ(emulator2.getMemory(1025), 111);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(instructionToBinaryCodeConversion, movesVV_MemoryToMemory) {
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
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1),
                                  1 << 5, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 24);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(
      emulator1, binaryCode1,
      {{32, 67}, {33, 71}, {34, 77}, {35, 81}, {67, 87}, {71, 101}, {77, 107}, {81, 111}, {92, 112}, {97, 117}}, 92, 97);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(5);  // [dst1] := [src1]  ->  [[32]] := [regB]
  memorySnapshot1[memorySnapshot1[32]] = memorySnapshot1[97];
  ASSERT_EQ(emulator1.getRegA(), 92);
  ASSERT_EQ(emulator1.getRegB(), 97);
  ASSERT_EQ(emulator1.getMemory(67), 117);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // [dst2] := [src2]  ->  [regB] := [regA]
  memorySnapshot1[97] = memorySnapshot1[92];
  ASSERT_EQ(emulator1.getRegA(), 92);
  ASSERT_EQ(emulator1.getRegB(), 97);
  ASSERT_EQ(emulator1.getMemory(97), 112);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(5);  // [dst3] := [src3]  ->  [regA] := [[34]]
  memorySnapshot1[92] = memorySnapshot1[memorySnapshot1[34]];
  ASSERT_EQ(emulator1.getRegA(), 92);
  ASSERT_EQ(emulator1.getRegB(), 97);
  ASSERT_EQ(emulator1.getMemory(92), 107);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(8);  // [dst4] := [src4]  ->  [[33]] := [[35]]
  memorySnapshot1[memorySnapshot1[33]] = memorySnapshot1[memorySnapshot1[35]];
  ASSERT_EQ(emulator1.getRegA(), 92);
  ASSERT_EQ(emulator1.getRegB(), 97);
  ASSERT_EQ(emulator1.getMemory(71), 111);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

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
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2),
                                  1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 28);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(
      emulator2, binaryCode2,
      {{1024, 67}, {1025, 71}, {1026, 77}, {1027, 81}, {67, 87}, {71, 101}, {77, 107}, {81, 111}, {92, 112}, {97, 117}}, 92, 97);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(5);  // [dst1] := [src1]  ->  [[1024]] := [regB]
  memorySnapshot2[memorySnapshot2[1024]] = memorySnapshot2[97];
  ASSERT_EQ(emulator2.getRegA(), 92);
  ASSERT_EQ(emulator2.getRegB(), 97);
  ASSERT_EQ(emulator2.getMemory(67), 117);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // [dst2] := [src2]  ->  [regB] := [regA]
  memorySnapshot2[97] = memorySnapshot2[92];
  ASSERT_EQ(emulator2.getRegA(), 92);
  ASSERT_EQ(emulator2.getRegB(), 97);
  ASSERT_EQ(emulator2.getMemory(97), 112);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(5);  // [dst3] := [src3]  ->  [regA] := [[1026]]
  memorySnapshot2[92] = memorySnapshot2[memorySnapshot2[1026]];
  ASSERT_EQ(emulator2.getRegA(), 92);
  ASSERT_EQ(emulator2.getRegB(), 97);
  ASSERT_EQ(emulator2.getMemory(92), 107);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(8);  // [dst4] := [src4]  ->  [[1025]] := [[1027]]
  memorySnapshot2[memorySnapshot2[1025]] = memorySnapshot2[memorySnapshot2[1027]];
  ASSERT_EQ(emulator2.getRegA(), 92);
  ASSERT_EQ(emulator2.getRegB(), 97);
  ASSERT_EQ(emulator2.getMemory(71), 111);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

/* Register allocation result for movesVN programs (short/long address):
 *
 * src1 -> regB, src2 -> regA, src3 -> [32/1024], src4 -> [33/1025]
*/

TEST(instructionToBinaryCodeConversion, movesVN_RegisterToMemory) {
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
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 5, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 14);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{32, 57}, {33, 61}}, 41, 37);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(1);  // [42] := src1  ->  [42] := regB
  memorySnapshot1[42] = 37;
  ASSERT_EQ(emulator1.getRegA(), 41);
  ASSERT_EQ(emulator1.getRegB(), 37);
  ASSERT_EQ(emulator1.getMemory(42), 37);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // [1410] := src2  ->  [1410] := regA
  memorySnapshot1[1410] = 41;
  ASSERT_EQ(emulator1.getRegA(), 41);
  ASSERT_EQ(emulator1.getRegB(), 37);
  ASSERT_EQ(emulator1.getMemory(1410), 41);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // [42] := src3  ->  [42] := [32]
  memorySnapshot1[42] = memorySnapshot1[32];
  ASSERT_EQ(emulator1.getRegA(), 41);
  ASSERT_EQ(emulator1.getRegB(), 37);
  ASSERT_EQ(emulator1.getMemory(42), 57);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // [1410] := src4  ->  [1410] := [33]
  memorySnapshot1[1410] = memorySnapshot1[33];
  ASSERT_EQ(emulator1.getRegA(), 41);
  ASSERT_EQ(emulator1.getRegB(), 37);
  ASSERT_EQ(emulator1.getMemory(1410), 61);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

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
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 16);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{1024, 57}, {1025, 61}}, 41, 37);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(1);  // [42] := src1  ->  [42] := regB
  memorySnapshot2[42] = 37;
  ASSERT_EQ(emulator2.getRegA(), 41);
  ASSERT_EQ(emulator2.getRegB(), 37);
  ASSERT_EQ(emulator2.getMemory(42), 37);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // [1410] := src2  ->  [1410] := regA
  memorySnapshot2[1410] = 41;
  ASSERT_EQ(emulator2.getRegA(), 41);
  ASSERT_EQ(emulator2.getRegB(), 37);
  ASSERT_EQ(emulator2.getMemory(1410), 41);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // [42] := src3  ->  [42] := [1024]
  memorySnapshot2[42] = memorySnapshot2[1024];
  ASSERT_EQ(emulator2.getRegA(), 41);
  ASSERT_EQ(emulator2.getRegB(), 37);
  ASSERT_EQ(emulator2.getMemory(42), 57);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // [1410] := src4  ->  [1410] := [1025]
  memorySnapshot2[1410] = memorySnapshot2[1025];
  ASSERT_EQ(emulator2.getRegA(), 41);
  ASSERT_EQ(emulator2.getRegB(), 37);
  ASSERT_EQ(emulator2.getMemory(1410), 61);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(instructionToBinaryCodeConversion, movesVN_MemoryToMemory) {
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
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 5, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 28);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{32, 57}, {33, 61}, {37, 137}, {41, 141}, {57, 157}, {61, 161}}, 41, 37);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(4);  // [42] := [src1]  ->  [42] := [regB]
  memorySnapshot1[42] = memorySnapshot1[37];
  ASSERT_EQ(emulator1.getRegA(), 41);
  ASSERT_EQ(emulator1.getRegB(), 37);
  ASSERT_EQ(emulator1.getMemory(42), 137);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(4);  // [1410] := [src2]  ->  [1410] := [regA]
  memorySnapshot1[1410] = memorySnapshot1[41];
  ASSERT_EQ(emulator1.getRegA(), 41);
  ASSERT_EQ(emulator1.getRegB(), 37);
  ASSERT_EQ(emulator1.getMemory(1410), 141);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(6);  // [42] := [src3]  ->  [42] := [[32]]
  memorySnapshot1[42] = memorySnapshot1[memorySnapshot1[32]];
  ASSERT_EQ(emulator1.getRegA(), 41);
  ASSERT_EQ(emulator1.getRegB(), 37);
  ASSERT_EQ(emulator1.getMemory(42), 157);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(6);  // [1410] := [src4]  ->  [1410] := [[33]]
  memorySnapshot1[1410] = memorySnapshot1[memorySnapshot1[33]];
  ASSERT_EQ(emulator1.getRegA(), 41);
  ASSERT_EQ(emulator1.getRegB(), 37);
  ASSERT_EQ(emulator1.getMemory(1410), 161);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

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
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 30);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{1024, 57}, {1025, 61}, {37, 137}, {41, 141}, {57, 157}, {61, 161}}, 41, 37);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(4);  // [42] := [src1]  ->  [42] := [regB]
  memorySnapshot2[42] = memorySnapshot2[37];
  ASSERT_EQ(emulator2.getRegA(), 41);
  ASSERT_EQ(emulator2.getRegB(), 37);
  ASSERT_EQ(emulator2.getMemory(42), 137);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(4);  // [1410] := [src2]  ->  [1410] := [regA]
  memorySnapshot2[1410] = memorySnapshot2[41];
  ASSERT_EQ(emulator2.getRegA(), 41);
  ASSERT_EQ(emulator2.getRegB(), 37);
  ASSERT_EQ(emulator2.getMemory(1410), 141);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(6);  // [42] := [src3]  ->  [42] := [[1024]]
  memorySnapshot2[42] = memorySnapshot2[memorySnapshot2[1024]];
  ASSERT_EQ(emulator2.getRegA(), 41);
  ASSERT_EQ(emulator2.getRegB(), 37);
  ASSERT_EQ(emulator2.getMemory(42), 157);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(6);  // [1410] := [src4]  ->  [1410] := [[1025]]
  memorySnapshot2[1410] = memorySnapshot2[memorySnapshot2[1025]];
  ASSERT_EQ(emulator2.getRegA(), 41);
  ASSERT_EQ(emulator2.getRegB(), 37);
  ASSERT_EQ(emulator2.getMemory(1410), 161);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

/* Register allocation result for movesNV programs (short/long address):
 *
 * dst1 -> regB, dst2 -> regA, dst3 -> [32/1024]
*/

TEST(instructionToBinaryCodeConversion, movesNV_ConstantToRegister) {
  // move constant to register - register does not need memory cell (short address)   - case dst2 := 42
  // move constant to register - register need memory cell (short address)            - case dst3 := 42
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst2", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst3", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock1), 1 << 5, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 5);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {}, 110, 120);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(1);  // dst2 := 42  ->  regA := 42
  ASSERT_EQ(emulator1.getRegA(), 42);
  ASSERT_EQ(emulator1.getRegB(), 120);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // dst3 := 42  ->  [32] = 42
  memorySnapshot1[32] = 42;
  ASSERT_EQ(emulator1.getRegA(), 42);
  ASSERT_EQ(emulator1.getRegB(), 120);
  ASSERT_EQ(emulator1.getMemory(32), 42);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move constant to register - register does not need memory cell (long address)   - case dst2 := 42
  // move constant to register - register need memory cell (long address)            - case dst3 := 42
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst2", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst3", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 6);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {}, 110, 120);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(1);  // dst2 := 42  ->  regA := 42
  ASSERT_EQ(emulator2.getRegA(), 42);
  ASSERT_EQ(emulator2.getRegB(), 120);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // dst3 := 42  ->  [1024] = 42
  memorySnapshot2[1024] = 42;
  ASSERT_EQ(emulator2.getRegA(), 42);
  ASSERT_EQ(emulator2.getRegB(), 120);
  ASSERT_EQ(emulator2.getMemory(1024), 42);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(instructionToBinaryCodeConversion, movesNV_ConstantToMemory) {
  // move constant to memory - register does not need memory cell (short address)   - case [dst2] := 42
  // move constant to memory - register need memory cell (short address)            - case [dst3] := 42
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst2", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst3", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock1), 1 << 5, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 7);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{32, 99}}, 110, 120);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(1);  // [dst2] := 42  ->  [regA] := 42
  memorySnapshot1[110] = 42;
  ASSERT_EQ(emulator1.getRegA(), 110);
  ASSERT_EQ(emulator1.getRegB(), 120);
  ASSERT_EQ(emulator1.getMemory(110), 42);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3);  // [dst3] := 42  ->  [[32]] := 42
  memorySnapshot1[memorySnapshot1[32]] = 42;
  ASSERT_EQ(emulator1.getRegA(), 110);
  ASSERT_EQ(emulator1.getRegB(), 120);
  ASSERT_EQ(emulator1.getMemory(99), 42);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move constant to memory - register does not need memory cell (long address)   - case [dst2] := 42
  // move constant to memory - register need memory cell (long address)            - case [dst3] := 42
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst2", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::MEMORY));
  basicBlock2.addInstruction(
      std::make_unique<BBMoveNV>(42, "dst3", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 8);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{1024, 99}}, 110, 120);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(1);  // [dst2] := 42  ->  [regA] := 42
  memorySnapshot2[110] = 42;
  ASSERT_EQ(emulator2.getRegA(), 110);
  ASSERT_EQ(emulator2.getRegB(), 120);
  ASSERT_EQ(emulator2.getMemory(110), 42);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3);  // [dst3] := 42  ->  [[32]] := 42
  memorySnapshot2[memorySnapshot2[1024]] = 42;
  ASSERT_EQ(emulator2.getRegA(), 110);
  ASSERT_EQ(emulator2.getRegB(), 120);
  ASSERT_EQ(emulator2.getMemory(99), 42);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

/* Register allocation result for movesNV programs (short/long address):
 *
 * dst1 -> regB, dst2 -> regA, dst3 -> [32/1024], dst4 -> [33, 1025]
*/

TEST(instructionToBinaryCodeConversion, movesNV_MemoryToRegister) {
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
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 5, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 14);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{32, 92}, {33, 93}, {42, 100}, {1410, 101}}, 110, 120);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(1);  // dst1 := [42]  ->  regB := [42]
  ASSERT_EQ(emulator1.getRegA(), 110);
  ASSERT_EQ(emulator1.getRegB(), 100);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // dst2 := [1410]  ->  regA := [1410]
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 100);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // dst3 := [42]  ->  [32] = [42]
  memorySnapshot1[32] = memorySnapshot1[42];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 100);
  ASSERT_EQ(emulator1.getMemory(32), 100);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // dst4 := [1410]  ->  [33] = [1410]
  memorySnapshot1[33] = memorySnapshot1[1410];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 100);
  ASSERT_EQ(emulator1.getMemory(33), 101);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

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
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 16);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{1024, 92}, {1025, 93}, {42, 100}, {1410, 101}}, 110, 120);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(1);  // dst1 := [42]  ->  regB := [42]
  ASSERT_EQ(emulator2.getRegA(), 110);
  ASSERT_EQ(emulator2.getRegB(), 100);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // dst2 := [1410]  ->  regA := [1410]
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 100);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // dst3 := [42]  ->  [1024] = [42]
  memorySnapshot2[1024] = memorySnapshot2[42];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 100);
  ASSERT_EQ(emulator2.getMemory(1024), 100);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // dst4 := [1410]  ->  [1025] = [1410]
  memorySnapshot2[1025] = memorySnapshot2[1410];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 100);
  ASSERT_EQ(emulator2.getMemory(1025), 101);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(instructionToBinaryCodeConversion, movesNV_MemoryToMemory) {
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
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 5, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 24);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{32, 92}, {33, 93}, {42, 100}, {1410, 101}}, 110, 120);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(3);  // [dst1] := [42]  ->  [regB] := [42]
  memorySnapshot1[120] = memorySnapshot1[42];
  ASSERT_EQ(emulator1.getRegA(), 110);
  ASSERT_EQ(emulator1.getRegB(), 120);
  ASSERT_EQ(emulator1.getMemory(120), 100);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3);  // [dst2] := [1410]  ->  [regA] := [1410]
  memorySnapshot1[110] = memorySnapshot1[1410];
  ASSERT_EQ(emulator1.getRegA(), 110);
  ASSERT_EQ(emulator1.getRegB(), 120);
  ASSERT_EQ(emulator1.getMemory(110), 101);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(5);  // [dst3] := [42]  ->  [[32]] := [42]
  memorySnapshot1[memorySnapshot1[32]] = memorySnapshot1[42];
  ASSERT_EQ(emulator1.getRegA(), 110);
  ASSERT_EQ(emulator1.getRegB(), 120);
  ASSERT_EQ(emulator1.getMemory(92), 100);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(5);  // [dst4] := [1410]  ->  [[33]] := [1410]
  memorySnapshot1[memorySnapshot1[33]] = memorySnapshot1[1410];
  ASSERT_EQ(emulator1.getRegA(), 110);
  ASSERT_EQ(emulator1.getRegB(), 120);
  ASSERT_EQ(emulator1.getMemory(93), 101);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

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
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 26);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{1024, 92}, {1025, 93}, {42, 100}, {1410, 101}}, 110, 120);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(3);  // [dst1] := [42]  ->  [regB] := [42]
  memorySnapshot2[120] = memorySnapshot2[42];
  ASSERT_EQ(emulator2.getRegA(), 110);
  ASSERT_EQ(emulator2.getRegB(), 120);
  ASSERT_EQ(emulator2.getMemory(120), 100);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3);  // [dst2] := [1410]  ->  [regA] := [1410]
  memorySnapshot2[110] = memorySnapshot2[1410];
  ASSERT_EQ(emulator2.getRegA(), 110);
  ASSERT_EQ(emulator2.getRegB(), 120);
  ASSERT_EQ(emulator2.getMemory(110), 101);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(5);  // [dst3] := [42]  ->  [[1024]] := [42]
  memorySnapshot2[memorySnapshot2[1024]] = memorySnapshot2[42];
  ASSERT_EQ(emulator2.getRegA(), 110);
  ASSERT_EQ(emulator2.getRegB(), 120);
  ASSERT_EQ(emulator2.getMemory(92), 100);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(5);  // [dst4] := [1410]  ->  [[1025]] := [1410]
  memorySnapshot2[memorySnapshot2[1025]] = memorySnapshot2[1410];
  ASSERT_EQ(emulator2.getRegA(), 110);
  ASSERT_EQ(emulator2.getRegB(), 120);
  ASSERT_EQ(emulator2.getMemory(93), 101);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(instructionToBinaryCodeConversion, movesNN_ConstantToMemory) {
  // move constant to memory - int8     - case [42] := 37
  // move constant to memory - int16    - case [1410] := 37
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(37, 42, BBMoveNN::SourceType::CONSTANT, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(37, 1410, BBMoveNN::SourceType::CONSTANT, BBMoveNN::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock1), 1 << 5, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 7);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {}, 77, 88);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(1);  // [42] := 37
  memorySnapshot1[42] = 37;
  ASSERT_EQ(emulator1.getRegA(), 77);
  ASSERT_EQ(emulator1.getRegB(), 88);
  ASSERT_EQ(emulator1.getMemory(42), 37);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // [1410] := 37
  memorySnapshot1[1410] = 37;
  ASSERT_EQ(emulator1.getRegA(), 77);
  ASSERT_EQ(emulator1.getRegB(), 88);
  ASSERT_EQ(emulator1.getMemory(1410), 37);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);
}

TEST(instructionToBinaryCodeConversion, movesNN_MemoryToMemory) {
  // move memory to memory - int8, int8     - case [37] := [42]
  // move memory to memory - int8, int16    - case [1410] := [42]
  // move memory to memory - int16, int8    - case [37] := [1920]
  // move memory to memory - int16, int16   - case [1410] := [1920]
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveNN>(42, 37, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(42, 1410, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(1920, 37, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(
      std::make_unique<BBMoveNN>(1920, 1410, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock1), 1 << 5, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 20);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{42, 142}, {1920, 120}}, 77, 88);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(2);  // [37] := [42]
  memorySnapshot1[37] = memorySnapshot1[42];
  ASSERT_EQ(emulator1.getRegA(), 77);
  ASSERT_EQ(emulator1.getRegB(), 88);
  ASSERT_EQ(emulator1.getMemory(37), 142);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // [1410] := [42]
  memorySnapshot1[1410] = memorySnapshot1[42];
  ASSERT_EQ(emulator1.getRegA(), 77);
  ASSERT_EQ(emulator1.getRegB(), 88);
  ASSERT_EQ(emulator1.getMemory(1410), 142);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // [37] := [1920]
  memorySnapshot1[37] = memorySnapshot1[1920];
  ASSERT_EQ(emulator1.getRegA(), 77);
  ASSERT_EQ(emulator1.getRegB(), 88);
  ASSERT_EQ(emulator1.getMemory(37), 120);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // [1410] := [1920]
  memorySnapshot1[1410] = memorySnapshot1[1920];
  ASSERT_EQ(emulator1.getRegA(), 77);
  ASSERT_EQ(emulator1.getRegB(), 88);
  ASSERT_EQ(emulator1.getMemory(1410), 120);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);
}