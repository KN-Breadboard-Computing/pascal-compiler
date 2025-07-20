#include <iostream>
#include <ranges>

#include "gtest/gtest.h"
#include "test_utils.hpp"

using namespace bblocks;
using namespace machine_code;

/* Register allocation result for movesVV programs (short/long address):
 *
 * src1 -> regB, src2 -> regA, src3 -> [66/1026], src4 -> [67/1027]
 * dst1 -> [64/1024], dst2 -> regB, dst3 -> regA, dst4 -> [65/1025]
*/

TEST(movInstructionToBinaryCodeConversion, movesVV_RegisterToRegister) {
  // move register to register - any register need memory cell (short address)    - case dst2 := src2
  // move register to register - first register need memory cell (short address)  - case dst3 := src3
  // move register to register - second register need memory cell (short address) - case dst1 := src1
  // move register to register - each register need memory cell (short address)   - case dst4 := src4
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 9);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(1);  // dst1 := src1  ->  [64] := regB
  memorySnapshot1[64] = 102;
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(64), 102);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // dst2 := src2  ->  regB := regA
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 101);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // dst3 := src3  ->  regA := [66]
  ASSERT_EQ(emulator1.getRegA(), 76);
  ASSERT_EQ(emulator1.getRegB(), 101);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // dst4 := src4  ->  [65] := [67]
  memorySnapshot1[65] = memorySnapshot1[67];
  ASSERT_EQ(emulator1.getRegA(), 76);
  ASSERT_EQ(emulator1.getRegB(), 101);
  ASSERT_EQ(emulator1.getMemory(65), 77);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move register to register - any register need memory cell (long address)    - case dst2 := src2
  // move register to register - first register need memory cell (long address)  - case dst3 := src3
  // move register to register - second register need memory cell (long address) - case dst1 := src1
  // move register to register - each register need memory cell (long address)   - case dst4 := src4
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::REGISTER));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 13);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(1);  // dst1 := src1  ->  [1024] := regB
  memorySnapshot2[1024] = 102;
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1024), 102);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // dst2 := src2  ->  regB := regA
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 101);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // dst3 := src3  ->  regA := [1026]
  ASSERT_EQ(emulator2.getRegA(), 76);
  ASSERT_EQ(emulator2.getRegB(), 101);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // dst4 := src4  ->  [1025] := [1027]
  memorySnapshot2[1025] = memorySnapshot2[1027];
  ASSERT_EQ(emulator2.getRegA(), 76);
  ASSERT_EQ(emulator2.getRegB(), 101);
  ASSERT_EQ(emulator2.getMemory(1025), 77);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(movInstructionToBinaryCodeConversion, movesVV_RegisterToMemory) {
  // move register to memory - any register need memory cell (short address)    - case [dst2] := src2
  // move register to memory - first register need memory cell (short address)  - case [dst3] := src3
  // move register to memory - second register need memory cell (short address) - case [dst1] := src1
  // move register to memory - each register need memory cell (short address)   - case [dst4] := src4
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 16);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(3);  // [dst1] := src1  ->  [[64]] := regB
  memorySnapshot1[memorySnapshot1[64]] = 102;
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(74), 102);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // [dst2] := src2  ->  [regB] := regA
  memorySnapshot1[102] = 101;
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(102), 101);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3);  // [dst3] := src3  ->  [regA] := [66]
  memorySnapshot1[101] = memorySnapshot1[66];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(101), 76);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(5);  // [dst4] := src4  ->  [[65]] := [67]
  memorySnapshot1[memorySnapshot1[65]] = memorySnapshot1[67];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(75), 77);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move register to memory - any register need memory cell (long address)     - case [dst2] := src2
  // move register to memory - first register need memory cell (long address)   - case [dst3] := src3
  // move register to memory - second register need memory cell (long address)  - case [dst1] := src1
  // move register to memory - each register need memory cell (long address)    - case [dst4] := src4
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::REGISTER, BBMoveVV::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 20);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(3);  // [dst1] := src1  ->  [[1024]] := regB
  memorySnapshot2[memorySnapshot2[1024]] = 102;
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(74), 102);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // [dst2] := src2  ->  [regB] := regA
  memorySnapshot2[102] = 101;
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(102), 101);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3);  // [dst3] := src3  ->  [regA] := [1026]
  memorySnapshot2[101] = memorySnapshot2[1026];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(101), 76);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(5);  // [dst4] := src4  ->  [[1025]] := [1027]
  memorySnapshot2[memorySnapshot2[1025]] = memorySnapshot2[1027];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(75), 77);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(movInstructionToBinaryCodeConversion, movesVV_MemoryToRegister) {
  // move memory to register - any register need memory cell (short address)    - case dst2 := [src2]
  // move memory to register - first register need memory cell (short address)  - case dst3 := [src3]
  // move memory to register - second register need memory cell (short address) - case dst1 := [src1]
  // move memory to register - each register need memory cell (short address)   - case dst4 := [src4]
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 18);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(4);  // dst1 := [src1]  ->  [64] := [regB]
  memorySnapshot1[64] = 112;
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(64), 112);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // dst2 := [src2]  ->  regB := [regA]
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 111);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3);  // dst3 := [src3]  ->  regA := [[66]]
  ASSERT_EQ(emulator1.getRegA(), 86);
  ASSERT_EQ(emulator1.getRegB(), 111);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(6);  // dst4 := [src4]  ->  [65] := [[67]]
  memorySnapshot1[65] = memorySnapshot1[memorySnapshot1[67]];
  ASSERT_EQ(emulator1.getRegA(), 86);
  ASSERT_EQ(emulator1.getRegB(), 111);
  ASSERT_EQ(emulator1.getMemory(65), 87);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move memory to register - any register need memory cell (long address)    - case dst2 := [src2]
  // move memory to register - first register need memory cell (long address)  - case dst3 := [src3]
  // move memory to register - second register need memory cell (long address) - case dst1 := [src1]
  // move memory to register - each register need memory cell (long address)   - case dst4 := [src4]
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::REGISTER));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 22);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(4);  // dst1 := [src1]  ->  [1024] := [regB]
  memorySnapshot2[1024] = 112;
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1024), 112);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // dst2 := [src2]  ->  regB := [regA]
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 111);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3);  // dst3 := [src3]  ->  regA := [[1026]]
  ASSERT_EQ(emulator2.getRegA(), 86);
  ASSERT_EQ(emulator2.getRegB(), 111);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(6);  // dst4 := [src4]  ->  [1025] := [[1027]]
  memorySnapshot2[1025] = memorySnapshot2[memorySnapshot2[1027]];
  ASSERT_EQ(emulator2.getRegA(), 86);
  ASSERT_EQ(emulator2.getRegB(), 111);
  ASSERT_EQ(emulator2.getMemory(1025), 87);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(movInstructionToBinaryCodeConversion, movesVV_MemoryToMemory) {
  // move memory to memory - any register need memory cell (short address)    - case [dst2] := [src2]
  // move memory to memory - first register need memory cell (short address)  - case [dst3] := [src3]
  // move memory to memory - second register need memory cell (short address) - case [dst1] := [src1]
  // move memory to memory - each register need memory cell (short address)   - case [dst4] := [src4]
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 24);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(5);  // [dst1] := [src1]  ->  [[64]] := [regB]
  memorySnapshot1[memorySnapshot1[64]] = memorySnapshot1[102];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(74), 112);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // [dst2] := [src2]  ->  [regB] := [regA]
  memorySnapshot1[102] = memorySnapshot1[101];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(102), 111);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(5);  // [dst3] := [src3]  ->  [regA] := [[66]]
  memorySnapshot1[101] = memorySnapshot1[memorySnapshot1[66]];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(101), 86);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(8);  // [dst4] := [src4]  ->  [[65]] := [[67]]
  memorySnapshot1[memorySnapshot1[65]] = memorySnapshot1[memorySnapshot1[67]];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(75), 87);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move memory to memory - any register need memory cell (long address)    - case [dst2] := [src2]
  // move memory to memory - first register need memory cell (long address)  - case [dst3] := [src3]
  // move memory to memory - second register need memory cell (long address) - case [dst1] := [src1]
  // move memory to memory - each register need memory cell (long address)   - case [dst4] := [src4]
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src1", "dst1", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src2", "dst2", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src3", "dst3", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveVV>("src4", "dst4", BBMoveVV::SourceType::MEMORY, BBMoveVV::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 28);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(5);  // [dst1] := [src1]  ->  [[1024]] := [regB]
  memorySnapshot2[memorySnapshot2[1024]] = memorySnapshot2[102];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(74), 112);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // [dst2] := [src2]  ->  [regB] := [regA]
  memorySnapshot2[102] = memorySnapshot2[101];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(102), 111);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(5);  // [dst3] := [src3]  ->  [regA] := [[1026]]
  memorySnapshot2[101] = memorySnapshot2[memorySnapshot2[1026]];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(101), 86);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(8);  // [dst4] := [src4]  ->  [[1025]] := [[1027]]
  memorySnapshot2[memorySnapshot2[1025]] = memorySnapshot2[memorySnapshot2[1027]];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(75), 87);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

/* Register allocation result for movesVN programs (short/long address):
 *
 * src1 -> regB, src2 -> regA, src3 -> [64/1024], src4 -> [65/1025]
*/

TEST(movInstructionToBinaryCodeConversion, movesVN_RegisterToMemory) {
  // move register to memory - register does not need memory cell (uint8, short address)      - case [89] := src1
  // move register to memory - register does not need memory cell (uint16, short address)     - case [1410] := src2
  // move register to memory - register need memory cell (uint8, short address)               - case [89] := src3
  // move register to memory - register need memory cell (uint16, short address)              - case [1410] := src4
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveVN>("src1", 89, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveVN>("src2", 1410, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveVN>("src3", 89, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveVN>("src4", 1410, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 14);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(1);  // [89] := src1  ->  [89] := regB
  memorySnapshot1[89] = 102;
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(89), 102);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // [1410] := src2  ->  [1410] := regA
  memorySnapshot1[1410] = 101;
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), 101);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // [89] := src3  ->  [89] := [64]
  memorySnapshot1[89] = memorySnapshot1[64];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(89), 74);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // [1410] := src4  ->  [1410] := [65]
  memorySnapshot1[1410] = memorySnapshot1[65];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), 75);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move register to memory - register does not need memory cell (uint8, long address)      - case [89] := src1
  // move register to memory - register does not need memory cell (uint16, long address)     - case [1410] := src2
  // move register to memory - register need memory cell (uint8, long address)               - case [89] := src3
  // move register to memory - register need memory cell (uint16, long address)              - case [1410] := src4
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBMoveVN>("src1", 89, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveVN>("src2", 1410, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveVN>("src3", 89, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveVN>("src4", 1410, BBMoveVN::SourceType::REGISTER, BBMoveVN::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 16);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(1);  // [89] := src1  ->  [89] := regB
  memorySnapshot2[89] = 102;
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(89), 102);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // [1410] := src2  ->  [1410] := regA
  memorySnapshot2[1410] = 101;
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1410), 101);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // [89] := src3  ->  [89] := [1024]
  memorySnapshot2[89] = memorySnapshot2[1024];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(89), 74);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // [1410] := src4  ->  [1410] := [1025]
  memorySnapshot2[1410] = memorySnapshot2[1025];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1410), 75);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(movInstructionToBinaryCodeConversion, movesVN_MemoryToMemory) {
  // move memory to memory - register does not need memory cell (uint8, short address)    - case [89] := [src1]
  // move memory to memory - register does not need memory cell (uint16, short address)   - case [1410] := [src2]
  // move memory to memory - register need memory cell (uint8, short address)             - case [89] := [src3]
  // move memory to memory - register need memory cell (uint16, short address)            - case [1410] := [src4]
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveVN>("src1", 89, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveVN>("src2", 1410, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveVN>("src3", 89, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveVN>("src4", 1410, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 28);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(4);  // [89] := [src1]  ->  [89] := [regB]
  memorySnapshot1[89] = memorySnapshot1[102];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(89), 112);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(4);  // [1410] := [src2]  ->  [1410] := [regA]
  memorySnapshot1[1410] = memorySnapshot1[101];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), 111);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(6);  // [89] := [src3]  ->  [89] := [[64]]
  memorySnapshot1[89] = memorySnapshot1[memorySnapshot1[64]];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(89), 84);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(6);  // [1410] := [src4]  ->  [1410] := [[65]]
  memorySnapshot1[1410] = memorySnapshot1[memorySnapshot1[65]];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), 85);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move memory to memory - register does not need memory cell (uint8, long address)     - case [89] := [src1]
  // move memory to memory - register does not need memory cell (uint16, long address)    - case [1410] := [src2]
  // move memory to memory - register need memory cell (uint8, long address)              - case [89] := [src3]
  // move memory to memory - register need memory cell (uint16, long address)             - case [1410] := [src4]
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBMoveVN>("src1", 89, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveVN>("src2", 1410, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveVN>("src3", 89, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveVN>("src4", 1410, BBMoveVN::SourceType::MEMORY, BBMoveVN::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 30);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(4);  // [89] := [src1]  ->  [89] := [regB]
  memorySnapshot2[89] = memorySnapshot2[102];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(89), 112);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(4);  // [1410] := [src2]  ->  [1410] := [regA]
  memorySnapshot2[1410] = memorySnapshot2[101];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1410), 111);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(6);  // [89] := [src3]  ->  [89] := [[1024]]
  memorySnapshot2[89] = memorySnapshot2[memorySnapshot2[1024]];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(89), 84);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(6);  // [1410] := [src4]  ->  [1410] := [[1025]]
  memorySnapshot2[1410] = memorySnapshot2[memorySnapshot2[1025]];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1410), 85);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

/* Register allocation result for movesNV programs (short/long address):
 *
 * dst1 -> regB, dst2 -> regA, dst3 -> [64/1024], dst4 -> [65/1025]
*/

TEST(movInstructionToBinaryCodeConversion, movesNV_ConstantToRegister) {
  // move constant to register - register does not need memory cell (short address)   - case dst2 := 89
  // move constant to register - register need memory cell (short address)            - case dst3 := 89
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveNV>(89, "dst2", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  basicBlock1.addInstruction(std::make_unique<BBMoveNV>(89, "dst3", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 5);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(1);  // dst2 := 89  ->  regA := 89
  ASSERT_EQ(emulator1.getRegA(), 89);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // dst3 := 89  ->  [64] = 89
  memorySnapshot1[64] = 89;
  ASSERT_EQ(emulator1.getRegA(), 89);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(64), 89);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move constant to register - register does not need memory cell (long address)   - case dst2 := 89
  // move constant to register - register need memory cell (long address)            - case dst3 := 89
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBMoveNV>(89, "dst2", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  basicBlock2.addInstruction(std::make_unique<BBMoveNV>(89, "dst3", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::REGISTER));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 6);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(1);  // dst2 := 89  ->  regA := 89
  ASSERT_EQ(emulator2.getRegA(), 89);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // dst3 := 89  ->  [1024] = 89
  memorySnapshot2[1024] = 89;
  ASSERT_EQ(emulator2.getRegA(), 89);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(1024), 89);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(movInstructionToBinaryCodeConversion, movesNV_ConstantToMemory) {
  // move constant to memory - register does not need memory cell (short address)   - case [dst2] := 89
  // move constant to memory - register need memory cell (short address)            - case [dst3] := 89
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveNV>(89, "dst2", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveNV>(89, "dst3", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 7);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(1);  // [dst2] := 89  ->  [regA] := 89
  memorySnapshot1[101] = 89;
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(101), 89);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3);  // [dst3] := 89  ->  [[64]] := 89
  memorySnapshot1[memorySnapshot1[64]] = 89;
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(74), 89);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move constant to memory - register does not need memory cell (long address)   - case [dst2] := 89
  // move constant to memory - register need memory cell (long address)            - case [dst3] := 89
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBMoveNV>(89, "dst2", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveNV>(89, "dst3", BBMoveNV::SourceType::CONSTANT, BBMoveNV::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 8);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(1);  // [dst2] := 89  ->  [regA] := 89
  memorySnapshot2[101] = 89;
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(101), 89);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3);  // [dst3] := 89  ->  [[64]] := 89
  memorySnapshot2[memorySnapshot2[1024]] = 89;
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(74), 89);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(movInstructionToBinaryCodeConversion, movesNV_MemoryToRegister) {
  // move memory to register - register does not need memory cell (uint8, short address)      - case dst1 := [89]
  // move memory to register - register does not need memory cell (uint16, short address)     - case dst2 := [1410]
  // move memory to register - register need memory cell (uint8, short address)               - case dst3 := [89]
  // move memory to register - register need memory cell (uint16, short address)              - case dst4 := [1410]
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveNV>(89, "dst1", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  basicBlock1.addInstruction(std::make_unique<BBMoveNV>(1410, "dst2", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  basicBlock1.addInstruction(std::make_unique<BBMoveNV>(89, "dst3", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  basicBlock1.addInstruction(std::make_unique<BBMoveNV>(1410, "dst4", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 14);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(1);  // dst1 := [89]  ->  regB := [89]
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 99);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // dst2 := [1410]  ->  regA := [1410]
  ASSERT_EQ(emulator1.getRegA(), 100);
  ASSERT_EQ(emulator1.getRegB(), 99);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // dst3 := [89]  ->  [64] = [89]
  memorySnapshot1[64] = memorySnapshot1[89];
  ASSERT_EQ(emulator1.getRegA(), 100);
  ASSERT_EQ(emulator1.getRegB(), 99);
  ASSERT_EQ(emulator1.getMemory(64), 99);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // dst4 := [1410]  ->  [65] = [1410]
  memorySnapshot1[65] = memorySnapshot1[1410];
  ASSERT_EQ(emulator1.getRegA(), 100);
  ASSERT_EQ(emulator1.getRegB(), 99);
  ASSERT_EQ(emulator1.getMemory(65), 100);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move memory to register - register does not need memory cell (uint8, long address)       - case dst1 := [89]
  // move memory to register - register does not need memory cell (uint16, long address)      - case dst2 := [1410]
  // move memory to register - register need memory cell (uint8, long address)                - case dst3 := [89]
  // move memory to register - register need memory cell (uint16, long address)               - case dst4 := [1410]
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBMoveNV>(89, "dst1", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  basicBlock2.addInstruction(std::make_unique<BBMoveNV>(1410, "dst2", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  basicBlock2.addInstruction(std::make_unique<BBMoveNV>(89, "dst3", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  basicBlock2.addInstruction(std::make_unique<BBMoveNV>(1410, "dst4", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::REGISTER));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 16);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(1);  // dst1 := [89]  ->  regB := [89]
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 99);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(1);  // dst2 := [1410]  ->  regA := [1410]
  ASSERT_EQ(emulator2.getRegA(), 100);
  ASSERT_EQ(emulator2.getRegB(), 99);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // dst3 := [89]  ->  [1024] = [89]
  memorySnapshot2[1024] = memorySnapshot2[89];
  ASSERT_EQ(emulator2.getRegA(), 100);
  ASSERT_EQ(emulator2.getRegB(), 99);
  ASSERT_EQ(emulator2.getMemory(1024), 99);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(2);  // dst4 := [1410]  ->  [1025] = [1410]
  memorySnapshot2[1025] = memorySnapshot2[1410];
  ASSERT_EQ(emulator2.getRegA(), 100);
  ASSERT_EQ(emulator2.getRegB(), 99);
  ASSERT_EQ(emulator2.getMemory(1025), 100);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(movInstructionToBinaryCodeConversion, movesNV_MemoryToMemory) {
  // move memory to memory - register does not need memory cell (uint8, short address)        - case [dst1] := [89]
  // move memory to memory - register does not need memory cell (uint16, short address)       - case [dst2] := [1410]
  // move memory to memory - register need memory cell (uint8, short address)                 - case [dst3] := [89]
  // move memory to memory - register need memory cell (uint16, short address)                - case [dst4] := [1410]
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveNV>(89, "dst1", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveNV>(1410, "dst2", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveNV>(89, "dst3", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveNV>(1410, "dst4", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 24);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(3);  // [dst1] := [89]  ->  [regB] := [89]
  memorySnapshot1[102] = memorySnapshot1[89];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(102), 99);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(3);  // [dst2] := [1410]  ->  [regA] := [1410]
  memorySnapshot1[101] = memorySnapshot1[1410];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(101), 100);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(5);  // [dst3] := [89]  ->  [[64]] := [89]
  memorySnapshot1[memorySnapshot1[64]] = memorySnapshot1[89];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(74), 99);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(5);  // [dst4] := [1410]  ->  [[65]] := [1410]
  memorySnapshot1[memorySnapshot1[65]] = memorySnapshot1[1410];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(75), 100);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  // move memory to memory - register does not need memory cell (uint8, long address)         - case [dst1] := [89]
  // move memory to memory - register does not need memory cell (uint16, long address)        - case [dst2] := [1410]
  // move memory to memory - register need memory cell (uint8, long address)                  - case [dst3] := [89]
  // move memory to memory - register need memory cell (uint16, long address)                 - case [dst4] := [1410]
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBMoveNV>(89, "dst1", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveNV>(1410, "dst2", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveNV>(89, "dst3", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  basicBlock2.addInstruction(std::make_unique<BBMoveNV>(1410, "dst4", BBMoveNV::SourceType::MEMORY, BBMoveNV::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), 26);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {1024, 74}, {1025, 75}, {1026, 76}, {1027, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();

  emulator2.runInstructions(3);  // [dst1] := [89]  ->  [regB] := [89]
  memorySnapshot2[102] = memorySnapshot2[89];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(102), 99);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(3);  // [dst2] := [1410]  ->  [regA] := [1410]
  memorySnapshot2[101] = memorySnapshot2[1410];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(101), 100);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(5);  // [dst3] := [89]  ->  [[1024]] := [89]
  memorySnapshot2[memorySnapshot2[1024]] = memorySnapshot2[89];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(74), 99);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);

  emulator2.runInstructions(5);  // [dst4] := [1410]  ->  [[1025]] := [1410]
  memorySnapshot2[memorySnapshot2[1025]] = memorySnapshot2[1410];
  ASSERT_EQ(emulator2.getRegA(), 101);
  ASSERT_EQ(emulator2.getRegB(), 102);
  ASSERT_EQ(emulator2.getMemory(75), 100);
  ASSERT_EQ(emulator2.getMemorySnapshot(), memorySnapshot2);
}

TEST(movInstructionToBinaryCodeConversion, movesNN_ConstantToMemory) {
  // move constant to memory - int8     - case [89] := 37
  // move constant to memory - int16    - case [1410] := 37
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveNN>(37, 89, BBMoveNN::SourceType::CONSTANT, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveNN>(37, 1410, BBMoveNN::SourceType::CONSTANT, BBMoveNN::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 7);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(1);  // [89] := 37
  memorySnapshot1[89] = 37;
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(89), 37);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(1);  // [1410] := 37
  memorySnapshot1[1410] = 37;
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), 37);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);
}

TEST(movInstructionToBinaryCodeConversion, movesNN_MemoryToMemory) {
  // move memory to memory - int8, int8     - case [37] := [89]
  // move memory to memory - int8, int16    - case [1410] := [89]
  // move memory to memory - int16, int8    - case [37] := [1920]
  // move memory to memory - int16, int16   - case [1410] := [1920]
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBMoveNN>(89, 37, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveNN>(89, 1410, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveNN>(1920, 37, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  basicBlock1.addInstruction(std::make_unique<BBMoveNN>(1920, 1410, BBMoveNN::SourceType::MEMORY, BBMoveNN::DestinationType::MEMORY));
  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), 20);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  emulator1.runInstructions(2);  // [37] := [89]
  memorySnapshot1[37] = memorySnapshot1[89];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(37), 99);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // [1410] := [89]
  memorySnapshot1[1410] = memorySnapshot1[89];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), 99);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // [37] := [1920]
  memorySnapshot1[37] = memorySnapshot1[1920];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(37), 120);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);

  emulator1.runInstructions(2);  // [1410] := [1920]
  memorySnapshot1[1410] = memorySnapshot1[1920];
  ASSERT_EQ(emulator1.getRegA(), 101);
  ASSERT_EQ(emulator1.getRegB(), 102);
  ASSERT_EQ(emulator1.getMemory(1410), 120);
  ASSERT_EQ(emulator1.getMemorySnapshot(), memorySnapshot1);
}