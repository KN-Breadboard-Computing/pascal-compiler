#include <iostream>
#include <ranges>

#include "gtest/gtest.h"
#include "test_utils.hpp"

using namespace bblocks;
using namespace machine_code;

struct BinaryOpTestCaseConfig {
  BBBinaryOperationEnum operation;
  size_t pureOpOffset;
  std::function<uint8_t(uint8_t, uint8_t)> opFunc;
};

class binaryInstructionToBinaryCodeConversion : public ::testing::TestWithParam<BinaryOpTestCaseConfig> {};

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVVV_RegisterRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to register -
  // move op(register, register) to register -
  // move op(register, register) to register -
  // move op(register, register) to register -
  // move op(register, register) to register -
  // move op(register, register) to register -
  // move op(register, register) to register -
  // move op(register, register) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(register, register) to register -
  // move op(register, register) to register -
  // move op(register, register) to register -
  // move op(register, register) to register -
  // move op(register, register) to register -
  // move op(register, register) to register -
  // move op(register, register) to register -
  // move op(register, register) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVVV_RegisterRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVVV_RegisterMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVVV_RegisterMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVVV_MemoryRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVVV_MemoryRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVVV_MemoryMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVVV_MemoryMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst1", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src2", "src3", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src2", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVV>("src3", "src4", "dst2", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVVN_RegisterRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -
  // move op(register, register) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVVN_RegisterMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 42, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 1410, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVVN_MemoryRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVVN_MemoryMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 42, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src2", "src3", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src2", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVVN>("src3", "src4", 1410, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVNV_RegisterConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to register -
  // move op(register, constant) to register -
  // move op(register, constant) to register -
  // move op(register, constant) to register -
  // move op(register, constant) to register -
  // move op(register, constant) to register -
  // move op(register, constant) to register -
  // move op(register, constant) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(register, constant) to register -
  // move op(register, constant) to register -
  // move op(register, constant) to register -
  // move op(register, constant) to register -
  // move op(register, constant) to register -
  // move op(register, constant) to register -
  // move op(register, constant) to register -
  // move op(register, constant) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVNV_RegisterConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVNV_RegisterMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -
  // move op(register, memory) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVNV_RegisterMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVNV_MemoryConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVNV_MemoryConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVNV_MemoryMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVNV_MemoryMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 1410, "dst1", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 42, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src2", 1410, "dst2", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 42, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src3", 1410, "dst3", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 42, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNV>("src4", 1410, "dst4", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVNN_RegisterConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -
  // move op(register, constant) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVNN_RegisterMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -
  // move op(register, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 37, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 1920, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVNN_MemoryConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsVNN_MemoryMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src2", 1410, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src3", 42, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 37, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationVNN>("src4", 1410, 1920, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNVV_ConstantRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to register -
  // move op(constant, register) to register -
  // move op(constant, register) to register -
  // move op(constant, register) to register -
  // move op(constant, register) to register -
  // move op(constant, register) to register -
  // move op(constant, register) to register -
  // move op(constant, register) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(constant, register) to register -
  // move op(constant, register) to register -
  // move op(constant, register) to register -
  // move op(constant, register) to register -
  // move op(constant, register) to register -
  // move op(constant, register) to register -
  // move op(constant, register) to register -
  // move op(constant, register) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNVV_ConstantRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNVV_ConstantMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNVV_ConstantMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNVV_MemoryRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -
  // move op(memory, register) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNVV_MemoryRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNVV_MemoryMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNVV_MemoryMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNVN_ConstantRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src1", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src1", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src2", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src2", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src3", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src3", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src4", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src4", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -
  // move op(constant, register) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src1", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src1", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src2", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src2", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src3", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src3", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src4", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src4", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNVN_ConstantMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src1", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src1", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src2", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src2", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src3", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src3", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src4", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src4", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src1", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src1", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src2", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src2", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src3", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src3", 37, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src4", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src4", 1920, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNVN_MemoryRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src1", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src1", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src2", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src2", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src3", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src3", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src4", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src4", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -
  // move op(memory, register) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src1", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src1", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src2", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src2", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src3", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src3", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src4", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src4", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNVN_MemoryMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src1", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src1", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src2", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src2", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src3", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src3", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src4", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src4", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src1", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src1", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src2", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src2", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src3", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src3", 37, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(42, "src4", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNVN>(1410, "src4", 1920, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNNV_ConstantConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to register -
  // move op(constant, constant) to register -
  // move op(constant, constant) to register -
  // move op(constant, constant) to register -
  // move op(constant, constant) to register -
  // move op(constant, constant) to register -
  // move op(constant, constant) to register -
  // move op(constant, constant) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(constant, constant) to register -
  // move op(constant, constant) to register -
  // move op(constant, constant) to register -
  // move op(constant, constant) to register -
  // move op(constant, constant) to register -
  // move op(constant, constant) to register -
  // move op(constant, constant) to register -
  // move op(constant, constant) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNNV_ConstantConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNNV_ConstantMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -
  // move op(constant, memory) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNNV_ConstantMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNNV_MemoryConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -
  // move op(memory, constant) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNNV_MemoryConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNNV_MemoryMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -
  // move op(memory, memory) to register -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNNV_MemoryMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst1", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst2", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 37, "dst3", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(42, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNV>(1410, 1920, "dst4", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNNN_ConstantConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -
  // move op(constant, constant) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNNN_ConstantMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -
  // move op(constant, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNNN_MemoryConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -
  // move op(memory, constant) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

TEST_P(binaryInstructionToBinaryCodeConversion, binaryOperationsNNN_MemoryMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode1;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock1), 1 << 6, binaryCode1);

  ASSERT_EQ(binaryCode1.size(), config.pureOpOffset);

  EmulatorConnector emulator1;
  prepareEmulatorForTest(emulator1, binaryCode1, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot1 = emulator1.getMemorySnapshot();

  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -
  // move op(memory, memory) to memory -

  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 37, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(42, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBBinaryOperationNNN>(1410, 1920, 1791, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));

  std::vector<uint8_t> binaryCode2;
  translateBasicBlockToBinaryCode({}, {}, std::move(basicBlock2), 1 << 10, binaryCode2);

  ASSERT_EQ(binaryCode2.size(), config.pureOpOffset);

  EmulatorConnector emulator2;
  prepareEmulatorForTest(emulator2, binaryCode2, {{89, 99}, {1410, 100}, {1920, 120}, {64, 74}, {65, 75}, {66, 76}, {67, 77}, {74, 84}, {75, 85}, {76, 86}, {77, 87}, {101, 111}, {102, 112}}, 101, 102);
  std::vector<uint8_t> memorySnapshot2 = emulator2.getMemorySnapshot();
}

BinaryOpTestCaseConfig addTestCaseConfig{BBBinaryOperationEnum::ADD, 1, [](uint8_t x, uint8_t y) {
                                           return static_cast<uint8_t>(x + y);
                                         }};

INSTANTIATE_TEST_SUITE_P(binaryInstructions, binaryInstructionToBinaryCodeConversion, ::testing::Values(addTestCaseConfig));
