#include <iostream>
#include <ranges>

#include "gtest/gtest.h"
#include "test_utils.hpp"

using namespace bblocks;
using namespace machine_code;

struct UnaryOpTestCaseConfig {
  BBUnaryOperationEnum operation;
  size_t pureOpOffset;
  std::function<uint8_t(uint8_t)> opFunc;
};

class unaryInstructionToBinaryCodeConversion : public ::testing::TestWithParam<UnaryOpTestCaseConfig> {};

/* Register allocation result for unaryOperationsVV programs (short/long address):
 *
 * src1 -> regB, src2 -> regA, src3 -> [66/1026], src4 -> [67/1027]
 * dst1 -> [64/1024], dst2 -> regB, dst3 -> regA, dst4 -> [65/1025]
*/

TEST_P(unaryInstructionToBinaryCodeConversion, unaryOperationsVV_RegisterToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(register) to register - any register need memory cell (short address)    - case dst2 := op(src2)
  // move op(register) to register - first register need memory cell (short address)  - case dst3 := op(src3)
  // move op(register) to register - second register need memory cell (short address) - case dst1 := op(src1)
  // move op(register) to register - each register need memory cell (short address)   - case dst4 := op(src4)
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src1", "dst1", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src2", "dst2", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src3", "dst3", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src4", "dst4", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 9 + 3 * config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(0 + config.pureOpOffset);  // dst1 := op(src1)  ->  [64] := op(regB)
  memorySnapshot1[64] = config.opFunc(102);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(64), config.opFunc(102));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(0 + config.pureOpOffset);  // dst2 := op(src2)  ->  regB := op(regA)
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), config.opFunc(101));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // dst3 := op(src3)  ->  regA := op([66])
  ASSERT_EQ(emulator1.getRegA(), config.opFunc(76));
  ASSERT_EQ(emulator1.getRegB(), config.opFunc(101));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3 + config.pureOpOffset);  // dst4 := op(src4)  ->  [65] := op([67])
  memorySnapshot1[65] = config.opFunc(memorySnapshot1[67]);
  ASSERT_EQ(emulator1.getRegA(), config.opFunc(76));
  ASSERT_EQ(emulator1.getRegB(), config.opFunc(101));
  ASSERT_EQ(emulator1.getMemory(65), config.opFunc(77));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move op(register) to register - any register need memory cell (long address)    - case dst2 := op(src2)
  // move op(register) to register - first register need memory cell (long address)  - case dst3 := op(src3)
  // move op(register) to register - second register need memory cell (long address) - case dst1 := op(src1)
  // move op(register) to register - each register need memory cell (long address)   - case dst4 := op(src4)
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src1", "dst1", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src2", "dst2", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src3", "dst3", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src4", "dst4", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 13 + 3 * config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(0 + config.pureOpOffset);  // dst1 := op(src1)  ->  [1024] := op(regB)
  memorySnapshot2[1024] = config.opFunc(102);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1024), config.opFunc(102));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(0 + config.pureOpOffset);  // dst2 := op(src2)  ->  regB := op(regA)
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), config.opFunc(101));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // dst3 := op(src3)  ->  regA := op([1026])
  ASSERT_EQ(emulator2.getRegA(), config.opFunc(76));
  ASSERT_EQ(emulator2.getRegB(), config.opFunc(101));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3 + config.pureOpOffset);  // dst4 := op(src4)  ->  [1025] := op([1027])
  memorySnapshot2[1025] = config.opFunc(memorySnapshot2[1027]);
  ASSERT_EQ(emulator2.getRegA(), config.opFunc(76));
  ASSERT_EQ(emulator2.getRegB(), config.opFunc(101));
  ASSERT_EQ(emulator2.getMemory(1025), config.opFunc(77));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST_P(unaryInstructionToBinaryCodeConversion, unaryOperationsVV_RegisterToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(register) to memory - any register need memory cell (short address)    - case [dst2] := op(src2)
  // move op(register) to memory - first register need memory cell (short address)  - case [dst3] := op(src3)
  // move op(register) to memory - second register need memory cell (short address) - case [dst1] := op(src1)
  // move op(register) to memory - each register need memory cell (short address)   - case [dst4] := op(src4)
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src1", "dst1", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src2", "dst2", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src3", "dst3", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src4", "dst4", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 21 + 3 * config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(4 + config.pureOpOffset);  // [dst1] := op(src1)  ->  [[64]] := op(regB)
  memorySnapshot1[memorySnapshot1[64]] = config.opFunc(102);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(74), config.opFunc(102));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2 + config.pureOpOffset);  // [dst2] := op(src2)  ->  [regB] := op(regA)
  memorySnapshot1[102] = config.opFunc(101);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(102), config.opFunc(101));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(5);  // [dst3] := op(src3)  ->  [regA] := op([66])
  memorySnapshot1[101] = config.opFunc(memorySnapshot1[66]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(101), config.opFunc(76));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(6 + config.pureOpOffset);  // [dst4] := op(src4)  ->  [[65]] := op([67])
  memorySnapshot1[memorySnapshot1[65]] = config.opFunc(memorySnapshot1[67]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(75), config.opFunc(77));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move op(register) to memory - any register need memory cell (long address)     - case [dst2] := op(src2)
  // move op(register) to memory - first register need memory cell (long address)   - case [dst3] := op(src3)
  // move op(register) to memory - second register need memory cell (long address)  - case [dst1] := op(src1)
  // move op(register) to memory - each register need memory cell (long address)    - case [dst4] := op(src4)
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src1", "dst1", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src2", "dst2", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src3", "dst3", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src4", "dst4", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 25 + 3 * config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(4 + config.pureOpOffset);  // [dst1] := op(src1)  ->  [[1024]] := op(regB)
  memorySnapshot2[memorySnapshot2[1024]] = config.opFunc(102);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(74), config.opFunc(102));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2 + config.pureOpOffset);  // [dst2] := op(src2)  ->  [regB] := op(regA)
  memorySnapshot2[102] = config.opFunc(101);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(102), config.opFunc(101));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(5);  // [dst3] := op(src3)  ->  [regA] := op([1026])
  memorySnapshot2[101] = config.opFunc(memorySnapshot2[1026]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(101), config.opFunc(76));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(6 + config.pureOpOffset);  // [dst4] := op(src4)  ->  [[1025]] := op([1027])
  memorySnapshot2[memorySnapshot2[1025]] = config.opFunc(memorySnapshot2[1027]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(75), config.opFunc(77));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST_P(unaryInstructionToBinaryCodeConversion, unaryOperationsVV_MemoryToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(memory) to register - any register need memory cell (short address)    - case dst2 := op([src2])
  // move op(memory) to register - first register need memory cell (short address)  - case dst3 := op([src3])
  // move op(memory) to register - second register need memory cell (short address) - case dst1 := op([src1])
  // move op(memory) to register - each register need memory cell (short address)   - case dst4 := op([src4])
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src1", "dst1", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src2", "dst2", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src3", "dst3", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src4", "dst4", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 18 + 2 * config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(3 + config.pureOpOffset);  // dst1 := op([src1])  ->  [64] := op([regB])
  memorySnapshot1[64] = config.opFunc(memorySnapshot1[102]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(64), config.opFunc(112));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // dst2 := op([src2])  ->  regB := op([regA])
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), config.opFunc(111));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(4);  // dst3 := op([src3])  ->  regA := op([[66]])
  ASSERT_EQ(emulator1.getRegA(), config.opFunc(86));
  ASSERT_EQ(emulator1.getRegB(), config.opFunc(111));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(5 + config.pureOpOffset);  // dst4 := op([src4])  ->  [65] := op([[67]])
  memorySnapshot1[65] = config.opFunc(memorySnapshot1[memorySnapshot1[67]]);
  ASSERT_EQ(emulator1.getRegA(), config.opFunc(86));
  ASSERT_EQ(emulator1.getRegB(), config.opFunc(111));
  ASSERT_EQ(emulator1.getMemory(65), config.opFunc(87));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move op(memory) to register - any register need memory cell (long address)    - case dst2 := op([src2])
  // move op(memory) to register - first register need memory cell (long address)  - case dst3 := op([src3])
  // move op(memory) to register - second register need memory cell (long address) - case dst1 := op([src1])
  // move op(memory) to register - each register need memory cell (long address)   - case dst4 := op([src4])
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src1", "dst1", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src2", "dst2", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src3", "dst3", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src4", "dst4", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 22 + 2 * config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(3 + config.pureOpOffset);  // dst1 := op([src1])  ->  [1024] := op([regB])
  memorySnapshot2[1024] = config.opFunc(memorySnapshot2[102]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1024), config.opFunc(112));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // dst2 := op([src2])  ->  regB := op([regA])
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), config.opFunc(111));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(4);  // dst3 := op([src3])  ->  regA := op([[1026]])
  ASSERT_EQ(emulator2.getRegA(), config.opFunc(86));
  ASSERT_EQ(emulator2.getRegB(), config.opFunc(111));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(5 + config.pureOpOffset);  // dst4 := op([src4])  ->  [1025] := op([[1027]])
  memorySnapshot2[1025] = config.opFunc(memorySnapshot2[memorySnapshot2[1027]]);
  ASSERT_EQ(emulator2.getRegA(), config.opFunc(86));
  ASSERT_EQ(emulator2.getRegB(), config.opFunc(111));
  ASSERT_EQ(emulator2.getMemory(1025), config.opFunc(87));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST_P(unaryInstructionToBinaryCodeConversion, unaryOperationsVV_MemoryToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(memory) to memory - any register need memory cell (short address)    - case [dst2] := op([src2])
  // move op(memory) to memory - first register need memory cell (short address)  - case [dst3] := op([src3])
  // move op(memory) to memory - second register need memory cell (short address) - case [dst1] := op([src1])
  // move op(memory) to memory - each register need memory cell (short address)   - case [dst4] := op([src4])
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src1", "dst1", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src2", "dst2", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src3", "dst3", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src4", "dst4", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 32 + 1 * config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(6 + config.pureOpOffset);  // [dst1] := op([src1])  ->  [[64]] := op([regB])
  memorySnapshot1[memorySnapshot1[64]] = config.opFunc(memorySnapshot1[102]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(74), config.opFunc(112));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(6);  // [dst2] := op([src2])  ->  [regB] := op([regA])
  memorySnapshot1[102] = config.opFunc(memorySnapshot1[101]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(102), config.opFunc(111));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(7);  // [dst3] := op([src3])  ->  [regA] := op([[66]])
  memorySnapshot1[101] = config.opFunc(memorySnapshot1[memorySnapshot1[66]]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(101), config.opFunc(86));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(9);  // [dst4] := op([src4])  ->  [[65]] := op([[67]])
  memorySnapshot1[memorySnapshot1[65]] = config.opFunc(memorySnapshot1[memorySnapshot1[67]]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(75), config.opFunc(87));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move op(memory) to memory - any register need memory cell (long address)    - case [dst2] := op([src2])
  // move op(memory) to memory - first register need memory cell (long address)  - case [dst3] := op([src3])
  // move op(memory) to memory - second register need memory cell (long address) - case [dst1] := op([src1])
  // move op(memory) to memory - each register need memory cell (long address)   - case [dst4] := op([src4])
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src1", "dst1", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src2", "dst2", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src3", "dst3", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src4", "dst4", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 36 + 1 * config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(6 + config.pureOpOffset);  // [dst1] := op([src1])  ->  [[1024]] := op([regB])
  memorySnapshot2[memorySnapshot2[1024]] = config.opFunc(memorySnapshot2[102]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(74), config.opFunc(112));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(6);  // [dst2] := op([src2])  ->  [regB] := op([regA])
  memorySnapshot2[102] = config.opFunc(memorySnapshot2[101]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(102), config.opFunc(111));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(7);  // [dst3] := op([src3])  ->  [regA] := op([[1026]])
  memorySnapshot2[101] = config.opFunc(memorySnapshot2[memorySnapshot2[1026]]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(101), config.opFunc(86));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(9);  // [dst4] := op([src4])  ->  [[1025]] := op([[1027]])
  memorySnapshot2[memorySnapshot2[1025]] = config.opFunc(memorySnapshot2[memorySnapshot2[1027]]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(75), config.opFunc(87));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

/* Register allocation result for unaryOperationsVN programs (short/long address):
 *
 * src1 -> regB, src2 -> regA, src3 -> [64/1024], src4 -> [65/1025]
*/

TEST_P(unaryInstructionToBinaryCodeConversion, unaryOperationsVN_RegisterToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(register) to memory - register does not need memory cell (uint8, short address)      - case [89] := op(src1)
  // move op(register) to memory - register does not need memory cell (uint16, short address)     - case [1410] := op(src2)
  // move op(register) to memory - register need memory cell (uint8, short address)               - case [89] := op(src3)
  // move op(register) to memory - register need memory cell (uint16, short address)              - case [1410] := op(src4)
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src1", 89, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src2", 1410, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src3", 89, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src4", 1410, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 14 + 4 * config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(0 + config.pureOpOffset);  // [89] := op(src1)  ->  [89] := op(regB)
  memorySnapshot1[89] = config.opFunc(102);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(89), config.opFunc(102));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(0 + config.pureOpOffset);  // [1410] := op(src2)  ->  [1410] := op(regA)
  memorySnapshot1[1410] = config.opFunc(101);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), config.opFunc(101));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3 + config.pureOpOffset);  // [89] := op(src3)  ->  [89] := op([64])
  memorySnapshot1[89] = config.opFunc(memorySnapshot1[64]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(89), config.opFunc(74));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3 + config.pureOpOffset);  // [1410] := op(src4)  ->  [1410] := op([65])
  memorySnapshot1[1410] = config.opFunc(memorySnapshot1[65]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), config.opFunc(75));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move op(register) to memory - register does not need memory cell (uint8, long address)      - case [89] := op(src1)
  // move op(register) to memory - register does not need memory cell (uint16, long address)     - case [1410] := op(src2)
  // move op(register) to memory - register need memory cell (uint8, long address)               - case [89] := op(src3)
  // move op(register) to memory - register need memory cell (uint16, long address)              - case [1410] := op(src4)
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src1", 89, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src2", 1410, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src3", 89, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src4", 1410, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 16 + 4 * config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(0 + config.pureOpOffset);  // [89] := op(src1)  ->  [89] := op(regB)
  memorySnapshot2[89] = config.opFunc(102);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(89), config.opFunc(102));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(0 + config.pureOpOffset);  // [1410] := op(src2)  ->  [1410] := op(regA)
  memorySnapshot2[1410] = config.opFunc(101);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1410), config.opFunc(101));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3 + config.pureOpOffset);  // [89] := op(src3)  ->  [89] := op([1024])
  memorySnapshot2[89] = config.opFunc(memorySnapshot2[1024]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(89), config.opFunc(74));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3 + config.pureOpOffset);  // [1410] := op(src4)  ->  [1410] := op([1025])
  memorySnapshot2[1410] = config.opFunc(memorySnapshot2[1025]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1410), config.opFunc(75));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST_P(unaryInstructionToBinaryCodeConversion, unaryOperationsVN_MemoryToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(memory) to memory - register does not need memory cell (uint8, short address)    - case [89] := op([src1])
  // move op(memory) to memory - register does not need memory cell (uint16, short address)   - case [1410] := op([src2])
  // move op(memory) to memory - register need memory cell (uint8, short address)             - case [89] := op([src3])
  // move op(memory) to memory - register need memory cell (uint16, short address)            - case [1410] := op([src4])
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src1", 89, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src2", 1410, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src3", 89, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src4", 1410, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 24 + 4 * config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(3 + config.pureOpOffset);  // [89] := op([src1])  ->  [89] := op([regB])
  memorySnapshot1[89] = config.opFunc(memorySnapshot1[102]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(89), config.opFunc(112));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3 + config.pureOpOffset);  // [1410] := op([src2])  ->  [1410] := op([regA])
  memorySnapshot1[1410] = config.opFunc(memorySnapshot1[101]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), config.opFunc(111));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(5 + config.pureOpOffset);  // [89] := op([src3])  ->  [89] := op([[64]])
  memorySnapshot1[89] = config.opFunc(memorySnapshot1[memorySnapshot1[64]]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(89), config.opFunc(84));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(5 + config.pureOpOffset);  // [1410] := op([src4])  ->  [1410] := op([[65]])
  memorySnapshot1[1410] = config.opFunc(memorySnapshot1[memorySnapshot1[65]]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), config.opFunc(85));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move op(memory) to memory - register does not need memory cell (uint8, long address)     - case [89] := op([src1])
  // move op(memory) to memory - register does not need memory cell (uint16, long address)    - case [1410] := op([src2])
  // move op(memory) to memory - register need memory cell (uint8, long address)              - case [89] := op([src3])
  // move op(memory) to memory - register need memory cell (uint16, long address)             - case [1410] := op([src4])
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src1", 89, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src2", 1410, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src3", 89, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src4", 1410, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 26 + 4 * config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(3 + config.pureOpOffset);  // [89] := op([src1])  ->  [89] := op([regB])
  memorySnapshot2[89] = config.opFunc(memorySnapshot2[102]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(89), config.opFunc(112));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3 + config.pureOpOffset);  // [1410] := op([src2])  ->  [1410] := op([regA])
  memorySnapshot2[1410] = config.opFunc(memorySnapshot2[101]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1410), config.opFunc(111));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(5 + config.pureOpOffset);  // [89] := op([src3])  ->  [89] := op([[1024]])
  memorySnapshot2[89] = config.opFunc(memorySnapshot2[memorySnapshot2[1024]]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(89), config.opFunc(84));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(5 + config.pureOpOffset);  // [1410] := op([src4])  ->  [1410] := op([[1025]])
  memorySnapshot2[1410] = config.opFunc(memorySnapshot2[memorySnapshot2[1025]]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1410), config.opFunc(85));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

/* Register allocation result for unaryOperationsNV programs (short/long address):
 *
 * dst1 -> regB, dst2 -> regA, dst3 -> [64/1024], dst4 -> [65/1025]
*/

TEST_P(unaryInstructionToBinaryCodeConversion, unaryOperationsNV_ConstantToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(constant) to register - register does not need memory cell (short address)   - case dst2 := op(89)
  // move op(constant) to register - register need memory cell (short address)            - case dst3 := op(89)
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst2", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst3", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 8 + 1 * config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(2);  // dst2 := op(constant)  ->  regA := op(89)
  ASSERT_EQ(emulator1.getRegA(), config.opFunc(89));
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3 + config.pureOpOffset);  // dst3 := op(constant)  ->  [64] := op(89)
  memorySnapshot1[64] = config.opFunc(89);
  ASSERT_EQ(emulator1.getRegA(), config.opFunc(89));
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(64), config.opFunc(89));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move op(constant) to register - register does not need memory cell (long address)   - case dst2 := op(89)
  // move op(constant) to register - register need memory cell (long address)            - case dst3 := op(89)
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst2", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst3", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 9 + 1 * config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(2);  // dst2 := op(constant)  ->  regA := op(89)
  ASSERT_EQ(emulator2.getRegA(), config.opFunc(89));
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3 + config.pureOpOffset);  // dst3 := op(constant)  ->  [1024] := op(89)
  memorySnapshot2[1024] = config.opFunc(89);
  ASSERT_EQ(emulator2.getRegA(), config.opFunc(89));
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1024), config.opFunc(89));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST_P(unaryInstructionToBinaryCodeConversion, unaryOperationsNV_ConstantToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(constant) to memory - register does not need memory cell (short address)   - case [dst2] := op(89)
  // move op(constant) to memory - register need memory cell (short address)            - case [dst3] := op(89)
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst2", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst3", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 14 + 1 * config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(5);  // [dst2] := op(constant)  ->  [regA] := op(89)
  memorySnapshot1[101] = config.opFunc(89);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(101), config.opFunc(89));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(6 + config.pureOpOffset);  // [dst3] := op(constant)  ->  [[64]] := op(89)
  memorySnapshot1[memorySnapshot1[64]] = config.opFunc(89);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(74), config.opFunc(89));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move op(constant) to memory - register does not need memory cell (long address)   - case [dst2] := op(89)
  // move op(constant) to memory - register need memory cell (long address)            - case [dst3] := op(89)
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst2", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst3", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 15 + 1 * config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(5);  // [dst2] := op(constant)  ->  [regA] := op(89)
  memorySnapshot2[101] = config.opFunc(89);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(101), config.opFunc(89));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(6 + config.pureOpOffset);  // [dst3] := op(constant)  ->  [[1024]] := op(89)
  memorySnapshot2[memorySnapshot2[1024]] = config.opFunc(89);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(74), config.opFunc(89));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST_P(unaryInstructionToBinaryCodeConversion, unaryOperationsNV_MemoryToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(memory) to register - register does not need memory cell (uint8, short address)      - case dst1 := op([89])
  // move op(memory) to register - register does not need memory cell (uint16, short address)     - case dst2 := op([1410])
  // move op(memory) to register - register need memory cell (uint8, short address)               - case dst3 := op([89])
  // move op(memory) to register - register need memory cell (uint16, short address)              - case dst4 := op([1410])
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst1", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst2", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst3", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst4", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 18 + 2 * config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(2);  // dst1 := op([89])  ->  regB := op([89])
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), config.opFunc(99));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // dst2 := op([1410])  ->  regA := op([1410])
  ASSERT_EQ(emulator1.getRegA(), config.opFunc(100));
  ASSERT_EQ(emulator1.getRegB(), config.opFunc(99));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3 + config.pureOpOffset);  // dst3 := op([89])  ->  [64] := op([89])
  memorySnapshot1[64] = config.opFunc(memorySnapshot1[89]);
  ASSERT_EQ(emulator1.getRegA(), config.opFunc(100));
  ASSERT_EQ(emulator1.getRegB(), config.opFunc(99));
  ASSERT_EQ(emulator1.getMemory(64), config.opFunc(99));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3 + config.pureOpOffset);  // dst4 := op([1410])  ->  [65] := op([1410])
  memorySnapshot1[65] = config.opFunc(memorySnapshot1[1410]);
  ASSERT_EQ(emulator1.getRegA(), config.opFunc(100));
  ASSERT_EQ(emulator1.getRegB(), config.opFunc(99));
  ASSERT_EQ(emulator1.getMemory(65), config.opFunc(100));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move op(memory) to register - register does not need memory cell (uint8, long address)       - case dst1 := op([89])
  // move op(memory) to register - register does not need memory cell (uint16, long address)      - case dst2 := op([1410])
  // move op(memory) to register - register need memory cell (uint8, long address)                - case dst3 := op([89])
  // move op(memory) to register - register need memory cell (uint16, long address)               - case dst4 := op([1410])
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst1", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst2", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst3", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst4", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 20 + 2 * config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(2);  // dst1 := op([89])  ->  regB := op([89])
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), config.opFunc(99));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // dst2 := op([1410])  ->  regA := op([1410])
  ASSERT_EQ(emulator2.getRegA(), config.opFunc(100));
  ASSERT_EQ(emulator2.getRegB(), config.opFunc(99));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3 + config.pureOpOffset);  // dst3 := op([89])  ->  [1024] := op([89])
  memorySnapshot2[1024] = config.opFunc(memorySnapshot2[89]);
  ASSERT_EQ(emulator2.getRegA(), config.opFunc(100));
  ASSERT_EQ(emulator2.getRegB(), config.opFunc(99));
  ASSERT_EQ(emulator2.getMemory(1024), config.opFunc(99));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3 + config.pureOpOffset);  // dst4 := op([1410])  ->  [1025] := op([1410])
  memorySnapshot2[1025] = config.opFunc(memorySnapshot2[1410]);
  ASSERT_EQ(emulator2.getRegA(), config.opFunc(100));
  ASSERT_EQ(emulator2.getRegB(), config.opFunc(99));
  ASSERT_EQ(emulator2.getMemory(1025), config.opFunc(100));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST_P(unaryInstructionToBinaryCodeConversion, unaryOperationsNV_MemoryToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(memory) to memory - register does not need memory cell (uint8, short address)        - case [dst1] := op([89])
  // move op(memory) to memory - register does not need memory cell (uint16, short address)       - case [dst2] := op([1410])
  // move op(memory) to memory - register need memory cell (uint8, short address)                 - case [dst1] := op([89])
  // move op(memory) to memory - register need memory cell (uint16, short address)                - case [dst4] := op([1410])
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst1", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst2", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst3", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst4", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 30 + 2 * config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(5);  // [dst1] := op([89])  ->  [regB] := op([89])
  memorySnapshot1[102] = config.opFunc(memorySnapshot1[89]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(102), config.opFunc(99));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(5);  // [dst2] := op([1410])  ->  [regA] := op([1410])
  memorySnapshot1[101] = config.opFunc(memorySnapshot1[1410]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(101), config.opFunc(100));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(6 + config.pureOpOffset);  // [dst3] := op([89])  ->  [[64]] := op([89])
  memorySnapshot1[memorySnapshot1[64]] = config.opFunc(memorySnapshot1[89]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(74), config.opFunc(99));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(6 + config.pureOpOffset);  // [dst4] := op([1410])  ->  [[65]] := op([1410])
  memorySnapshot1[memorySnapshot1[65]] = config.opFunc(memorySnapshot1[1410]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(75), config.opFunc(100));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move op(memory) to memory - register does not need memory cell (uint8, long address)         - case [dst1] := op([89])
  // move op(memory) to memory - register does not need memory cell (uint16, long address)        - case [dst2] := op([1410])
  // move op(memory) to memory - register need memory cell (uint8, long address)                  - case [dst1] := op([89])
  // move op(memory) to memory - register need memory cell (uint16, long address)                 - case [dst4] := op([1410])
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst1", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst2", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(89, "dst3", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst4", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 32 + 2 * config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(5);  // [dst1] := op([89])  ->  [regB] := op([89])
  memorySnapshot2[102] = config.opFunc(memorySnapshot2[89]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(102), config.opFunc(99));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(5);  // [dst2] := op([1410])  ->  [regA] := op([1410])
  memorySnapshot2[101] = config.opFunc(memorySnapshot2[1410]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(101), config.opFunc(100));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(6 + config.pureOpOffset);  // [dst3] := op([89])  ->  [[1024]] := op([89])
  memorySnapshot2[memorySnapshot2[1024]] = config.opFunc(memorySnapshot2[89]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(74), config.opFunc(99));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(6 + config.pureOpOffset);  // [dst4] := op([1410])  ->  [[1025]] := op([1410])
  memorySnapshot2[memorySnapshot2[1025]] = config.opFunc(memorySnapshot2[1410]);
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(75), config.opFunc(100));
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST_P(unaryInstructionToBinaryCodeConversion, unaryOperationsNN_ConstantToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(constant) to memory - int8     - case [89] := op(37)
  // move op(constant) to memory - int16    - case [1410] := op(37)
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(37, 89, BBUnaryOperationNN::SourceType::CONSTANT, BBUnaryOperationNN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(37, 1410, BBUnaryOperationNN::SourceType::CONSTANT, BBUnaryOperationNN::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 11 + 2 * config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(3 + config.pureOpOffset);  // [89] := op(constant)  ->  [89] := op(37)
  memorySnapshot1[89] = config.opFunc(37);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(89), config.opFunc(37));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3 + config.pureOpOffset);  // [1410] := op(constant)  ->  [1410] := op(37)
  memorySnapshot1[1410] = config.opFunc(37);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), config.opFunc(37));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);
}

TEST_P(unaryInstructionToBinaryCodeConversion, unaryOperationsNN_MemoryToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(memory) to memory - int8, int8     - case [37] := op([89])
  // move op(memory) to memory - int8, int16    - case [1410] := op([89])
  // move op(memory) to memory - int16, int8    - case [37] := op([1920])
  // move op(memory) to memory - int16, int16   - case [1410] := op([1920])
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(89, 37, BBUnaryOperationNN::SourceType::MEMORY, BBUnaryOperationNN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(89, 1410, BBUnaryOperationNN::SourceType::MEMORY, BBUnaryOperationNN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(1920, 37, BBUnaryOperationNN::SourceType::MEMORY, BBUnaryOperationNN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(1920, 1410, BBUnaryOperationNN::SourceType::MEMORY, BBUnaryOperationNN::DestinationType::MEMORY, config.operation));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 24 + 4 * config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(3 + config.pureOpOffset);  // [37] := op([89])  ->  [37] := op([89])
  memorySnapshot1[37] = config.opFunc(memorySnapshot1[89]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(37), config.opFunc(99));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3 + config.pureOpOffset);  // [1410] := op([89])  ->  [1410] := op([89])
  memorySnapshot1[1410] = config.opFunc(memorySnapshot1[89]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), config.opFunc(99));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3 + config.pureOpOffset);  // [37] := op([1410])  ->  [37] := op([1920])
  memorySnapshot1[37] = config.opFunc(memorySnapshot1[1920]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(37), config.opFunc(120));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3 + config.pureOpOffset);  // [1410] := op([1920])  ->  [1410] := op([1920])
  memorySnapshot1[1410] = config.opFunc(memorySnapshot1[1920]);
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), config.opFunc(120));
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);
}

UnaryOpTestCaseConfig negTestCaseConfig{BBUnaryOperationEnum::NEG, 1, [](uint8_t x) {
                                          return static_cast<uint8_t>(-x);
                                        }};
UnaryOpTestCaseConfig notTestCaseConfig{BBUnaryOperationEnum::NOT, 1, [](uint8_t x) {
                                          return ~x;
                                        }};
UnaryOpTestCaseConfig incTestCaseConfig{BBUnaryOperationEnum::INC, 3, [](uint8_t x) {
                                          return static_cast<uint8_t>(x + 1);
                                        }};
UnaryOpTestCaseConfig decTestCaseConfig{BBUnaryOperationEnum::DEC, 3, [](uint8_t x) {
                                          return static_cast<uint8_t>(x - 1);
                                        }};
UnaryOpTestCaseConfig shlTestCaseConfig{BBUnaryOperationEnum::SHL, 1, [](uint8_t x) {
                                          return static_cast<uint8_t>(x << 1);
                                        }};
UnaryOpTestCaseConfig shrTestCaseConfig{BBUnaryOperationEnum::SHR, 1, [](uint8_t x) {
                                          return static_cast<uint8_t>(x >> 1);
                                        }};
UnaryOpTestCaseConfig sarTestCaseConfig{BBUnaryOperationEnum::SAR, 1, [](uint8_t x) {
                                          return static_cast<uint8_t>(static_cast<int8_t>(x) >> 1);
                                        }};

INSTANTIATE_TEST_SUITE_P(unaryInstructions, unaryInstructionToBinaryCodeConversion, ::testing::Values(negTestCaseConfig, notTestCaseConfig, incTestCaseConfig, decTestCaseConfig, shlTestCaseConfig, shrTestCaseConfig, sarTestCaseConfig));
