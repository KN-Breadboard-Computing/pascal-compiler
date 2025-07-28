#include <iostream>
#include <ranges>

#include "gtest/gtest.h"
#include "test_utils.hpp"

using namespace bblocks;
using namespace machine_code;

struct BinaryOpTestCaseConfig {
  BBBinaryOperationEnum operation;
  std::vector<MachineInstruction> pureOpA;
  std::vector<MachineInstruction> pureOpB;
  std::vector<MachineInstruction> pureOpMem;
  std::vector<MachineInstruction> pureOpMemZp;
  std::vector<MachineInstruction> pureOpStc;
};

class binaryInstructionToMachineInstructionConversion : public ::testing::TestWithParam<BinaryOpTestCaseConfig> {};

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_ConstantConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst", BBBinaryOperationVVV::SourceType::CONSTANT, BBBinaryOperationVVV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_ConstantConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst", BBBinaryOperationVVV::SourceType::CONSTANT, BBBinaryOperationVVV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_ConstantRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst", BBBinaryOperationVVV::SourceType::CONSTANT, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_ConstantRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst", BBBinaryOperationVVV::SourceType::CONSTANT, BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_ConstantMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst", BBBinaryOperationVVV::SourceType::CONSTANT, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_ConstantMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst", BBBinaryOperationVVV::SourceType::CONSTANT, BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_RegisterConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_RegisterConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst", BBBinaryOperationVVV::SourceType::REGISTER, BBBinaryOperationVVV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_RegisterRegisterToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_RegisterRegisterToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_RegisterMemoryToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_RegisterMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_MemoryConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_MemoryConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVV>("src1", "src2", "dst", BBBinaryOperationVVV::SourceType::MEMORY, BBBinaryOperationVVV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_MemoryRegisterToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_MemoryRegisterToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_MemoryMemoryToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVV_MemoryMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_ConstantConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::CONSTANT, BBBinaryOperationVVN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_ConstantConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::CONSTANT, BBBinaryOperationVVN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_ConstantRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::CONSTANT, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_ConstantRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::CONSTANT, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_ConstantMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::CONSTANT, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_ConstantMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::CONSTANT, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_RegisterConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_RegisterConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_RegisterRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_RegisterRegisterToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_RegisterMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_RegisterMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_MemoryConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_MemoryConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_MemoryRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_MemoryRegisterToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_MemoryMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVVN>("src1", "src2", 49, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1", "src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVVN_MemoryMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_ConstantConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst", BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_ConstantConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst", BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_ConstantRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst", BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_ConstantRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst", BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_ConstantMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst", BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_ConstantMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst", BBBinaryOperationVNV::SourceType::CONSTANT, BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_RegisterConstantToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_RegisterConstantToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_RegisterRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_RegisterRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst", BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_RegisterMemoryToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_RegisterMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_MemoryConstantToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_MemoryConstantToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_MemoryRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_MemoryRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNV>("src1", 42, "dst", BBBinaryOperationVNV::SourceType::MEMORY, BBBinaryOperationVNV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_MemoryMemoryToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNV_MemoryMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_ConstantConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_ConstantConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_ConstantRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_ConstantRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_ConstantMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_ConstantMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_RegisterConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_RegisterConstantToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_RegisterRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_RegisterRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_RegisterMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_RegisterMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_MemoryConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_MemoryConstantToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_MemoryRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_MemoryRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_MemoryMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationVNN>("src1", 42, 49, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src1"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsVNN_MemoryMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_ConstantConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(37, "src2", "dst", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_ConstantConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(37, "src2", "dst", BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_ConstantRegisterToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_ConstantRegisterToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_ConstantMemoryToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_ConstantMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_RegisterConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(37, "src2", "dst", BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_RegisterConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(37, "src2", "dst", BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_RegisterRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(37, "src2", "dst", BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_RegisterRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(37, "src2", "dst", BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_RegisterMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(37, "src2", "dst", BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_RegisterMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(37, "src2", "dst", BBBinaryOperationNVV::SourceType::REGISTER, BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_MemoryConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(37, "src2", "dst", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_MemoryConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(37, "src2", "dst", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_MemoryRegisterToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_MemoryRegisterToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_MemoryMemoryToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVV_MemoryMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_ConstantConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_ConstantConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_ConstantRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_ConstantRegisterToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_ConstantMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_ConstantMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_RegisterConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_RegisterConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_RegisterRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_RegisterRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_RegisterMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_RegisterMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_MemoryConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_MemoryConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_MemoryRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_MemoryRegisterToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_MemoryMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVN>(37, "src2", 49, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationNVN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src2"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNVN_MemoryMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_ConstantConstantToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_ConstantConstantToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_ConstantRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(37, 42, "dst", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_ConstantRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(37, 42, "dst", BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationNNV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_ConstantMemoryToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_ConstantMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_RegisterConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(37, 42, "dst", BBBinaryOperationNNV::SourceType::REGISTER, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_RegisterConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(37, 42, "dst", BBBinaryOperationNNV::SourceType::REGISTER, BBBinaryOperationNNV::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_RegisterRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(37, 42, "dst", BBBinaryOperationNNV::SourceType::REGISTER, BBBinaryOperationNNV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_RegisterRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(37, 42, "dst", BBBinaryOperationNNV::SourceType::REGISTER, BBBinaryOperationNNV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_RegisterMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(37, 42, "dst", BBBinaryOperationNNV::SourceType::REGISTER, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_RegisterMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(37, 42, "dst", BBBinaryOperationNNV::SourceType::REGISTER, BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_MemoryConstantToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_MemoryConstantToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_MemoryRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(37, 42, "dst", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_MemoryRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNV>(37, 42, "dst", BBBinaryOperationNNV::SourceType::MEMORY, BBBinaryOperationNNV::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_MemoryMemoryToRegister) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNV_MemoryMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_ConstantConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_ConstantConstantToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_ConstantRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_ConstantRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_ConstantMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(constant, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_ConstantMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_RegisterConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::REGISTER, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_RegisterConstantToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::REGISTER, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_RegisterRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::REGISTER, BBBinaryOperationNNN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_RegisterRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::REGISTER, BBBinaryOperationNNN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_RegisterMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::REGISTER, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_RegisterMemoryToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(register, memory) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::REGISTER, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_MemoryConstantToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::CONSTANT, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_MemoryConstantToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_MemoryRegisterToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_MemoryRegisterToMemory) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::REGISTER, BBBinaryOperationVVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_MemoryMemoryToRegister) {
  BinaryOpTestCaseConfig config = GetParam();

  // move op(memory, memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNNN>(37, 42, 49, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationNNN::SourceType::MEMORY, BBBinaryOperationVVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(binaryInstructionToMachineInstructionConversion, binaryOperationsNNN_MemoryMemoryToMemory) {
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

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 0);

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

  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 0);
}

BinaryOpTestCaseConfig addTestCaseConfig{BBBinaryOperationEnum::ADD,
                                         {MachineInstruction{MachineInstruction::ADD_A}},
                                         {MachineInstruction{MachineInstruction::ADD_B}},
                                         {MachineInstruction{MachineInstruction::ADD_MEM, {"arg1", "arg2"}}},
                                         {MachineInstruction{MachineInstruction::ADD_MEM_ZP, {"arg1"}}},
                                         {MachineInstruction{MachineInstruction::ADD_STC}}};

INSTANTIATE_TEST_SUITE_P(binaryInstructions, binaryInstructionToMachineInstructionConversion, ::testing::Values(addTestCaseConfig));