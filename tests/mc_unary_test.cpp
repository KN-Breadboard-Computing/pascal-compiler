#include <iostream>
#include <ranges>

#include "gtest/gtest.h"
#include "test_utils.hpp"

using namespace bblocks;
using namespace machine_code;

struct UnaryOpTestCaseConfig {
  BBUnaryOperationEnum operation;
  std::vector<MachineInstruction> pureOpAA;
  std::vector<MachineInstruction> pureOpAB;
  std::vector<MachineInstruction> pureOpBA;
  std::vector<MachineInstruction> pureOpBB;
  std::vector<MachineInstruction> pureOpMemA;
  std::vector<MachineInstruction> pureOpMemZpA;
  std::vector<MachineInstruction> pureOpMemB;
  std::vector<MachineInstruction> pureOpMemZpB;
  std::vector<MachineInstruction> pureOpStcA;
  std::vector<MachineInstruction> pureOpStcB;
};

class unaryInstructionToMachineInstructionConversion : public ::testing::TestWithParam<UnaryOpTestCaseConfig> {};

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsVV_ConstantToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src", "dst", BBUnaryOperationVV::SourceType::CONSTANT, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src", "dst"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsVV_ConstantToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVV>("src", "dst", BBUnaryOperationVV::SourceType::CONSTANT, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src", "dst"}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsVV_RegisterToRegister) {
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
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 9);

  size_t cnt = 0;
  for (size_t i = 0; i < config.pureOpMemZpB.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpB.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpB.at(i).getOperands().size());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), config.pureOpMemZpB.at(i).getOperands());
    ++cnt;
  }

  for (size_t i = 0; i < config.pureOpBA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpBA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpBA.at(i).getOperands().size());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), config.pureOpBA.at(i).getOperands());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<uint8_t>({0b01000001}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), config.pureOpAA.at(i).getOperands());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<uint8_t>({0b01000011}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), config.pureOpMemA.at(i).getOperands());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  // move op(register) to register - any register need memory cell (long address)    - case dst2 := op(src2)
  // move op(register) to register - first register need memory cell (long address)  - case dst3 := op(src3)
  // move op(register) to register - second register need memory cell (long address) - case dst1 := op(src1)
  // move op(register) to register - each register need memory cell (long address)   - case dst4 := op(src4)
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src1", "dst1", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src2", "dst2", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src3", "dst3", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src4", "dst4", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 5);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsVV_RegisterToMemory) {
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
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 12);

  // move op(register) to memory - any register need memory cell (long address)     - case [dst2] := op(src2)
  // move op(register) to memory - first register need memory cell (long address)   - case [dst3] := op(src3)
  // move op(register) to memory - second register need memory cell (long address)  - case [dst1] := op(src1)
  // move op(register) to memory - each register need memory cell (long address)    - case [dst4] := op(src4)
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src1", "dst1", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src2", "dst2", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src3", "dst3", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src4", "dst4", BBUnaryOperationVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 12);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsVV_MemoryToRegister) {
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
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 14);

  // move op(memory) to register - any register need memory cell (long address)    - case dst2 := op([src2])
  // move op(memory) to register - first register need memory cell (long address)  - case dst3 := op([src3])
  // move op(memory) to register - second register need memory cell (long address) - case dst1 := op([src1])
  // move op(memory) to register - each register need memory cell (long address)   - case dst4 := op([src4])
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src1", "dst1", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src2", "dst2", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src3", "dst3", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src4", "dst4", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 14);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsVV_MemoryToMemory) {
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
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 20);

  // move op(memory) to memory - any register need memory cell (long address)    - case [dst2] := op([src2])
  // move op(memory) to memory - first register need memory cell (long address)  - case [dst3] := op([src3])
  // move op(memory) to memory - second register need memory cell (long address) - case [dst1] := op([src1])
  // move op(memory) to memory - each register need memory cell (long address)   - case [dst4] := op([src4])
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src1", "dst1", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src2", "dst2", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src3", "dst3", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVV>("src4", "dst4", BBUnaryOperationVV::SourceType::MEMORY, BBUnaryOperationVV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 20);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsVN_ConstantToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src", 42, BBUnaryOperationVN::SourceType::CONSTANT, BBUnaryOperationVN::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsVN_ConstantToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(constant) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src", 42, BBUnaryOperationVN::SourceType::CONSTANT, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsVN_RegisterToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src", 42, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsVN_RegisterToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(register) to memory - register does not need memory cell (uint8, short address)      - case [42] := op(src1)
  // move op(register) to memory - register does not need memory cell (uint16, short address)     - case [1410] := op(src2)
  // move op(register) to memory - register need memory cell (uint8, short address)               - case [42] := op(src3)
  // move op(register) to memory - register need memory cell (uint16, short address)              - case [1410] := op(src4)
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src1", 42, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src2", 1410, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src3", 42, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src4", 1410, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 6);

  // move op(register) to memory - register does not need memory cell (uint8, long address)      - case [42] := op(src1)
  // move op(register) to memory - register does not need memory cell (uint16, long address)     - case [1410] := op(src2)
  // move op(register) to memory - register need memory cell (uint8, long address)               - case [42] := op(src3)
  // move op(register) to memory - register need memory cell (uint16, long address)              - case [1410] := op(src4)
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src1", 42, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src2", 1410, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src3", 42, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src4", 1410, BBUnaryOperationVN::SourceType::REGISTER, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 6);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsVN_MemoryToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src", 42, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"src"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsVN_MemoryToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(memory) to memory - register does not need memory cell (uint8, short address)    - case [42] := op([src1])
  // move op(memory) to memory - register does not need memory cell (uint16, short address)   - case [1410] := op([src2])
  // move op(memory) to memory - register need memory cell (uint8, short address)             - case [42] := op([src3])
  // move op(memory) to memory - register need memory cell (uint16, short address)            - case [1410] := op([src4])
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src1", 42, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src2", 1410, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src3", 42, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationVN>("src4", 1410, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 20);

  // move op(memory) to memory - register does not need memory cell (uint8, long address)     - case [42] := op([src1])
  // move op(memory) to memory - register does not need memory cell (uint16, long address)    - case [1410] := op([src2])
  // move op(memory) to memory - register need memory cell (uint8, long address)              - case [42] := op([src3])
  // move op(memory) to memory - register need memory cell (uint16, long address)             - case [1410] := op([src4])
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src1", 42, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src2", 1410, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src3", 42, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationVN>("src4", 1410, BBUnaryOperationVN::SourceType::MEMORY, BBUnaryOperationVN::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 20);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsNV_ConstantToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(constant) to register - register does not need memory cell (short address)   - case src2 := op(42)
  // move op(constant) to register - register need memory cell (short address)            - case src3 := op(42)
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst2", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst3", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 2);

  // move op(constant) to register - register does not need memory cell (long address)   - case src2 := op(42)
  // move op(constant) to register - register need memory cell (long address)            - case src3 := op(42)
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst2", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst3", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 2);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsNV_ConstantToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(constant) to memory - register does not need memory cell (short address)   - case [src2] := op(42)
  // move op(constant) to memory - register need memory cell (short address)            - case [src3] := op(42)
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst2", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst3", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 4);

  // move op(constant) to memory - register does not need memory cell (long address)   - case [src2] := op(42)
  // move op(constant) to memory - register need memory cell (long address)            - case [src3] := op(42)
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst2", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst3", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 4);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsNV_RegisterToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst", BBUnaryOperationNV::SourceType::REGISTER, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {"dst"}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsNV_RegisterToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst", BBUnaryOperationNV::SourceType::REGISTER, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({"dst"}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsNV_MemoryToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(memory) to register - register does not need memory cell (uint8, short address)      - case dst1 := op([42])
  // move op(memory) to register - register does not need memory cell (uint16, short address)     - case dst2 := op([1410])
  // move op(memory) to register - register need memory cell (uint8, short address)               - case dst3 := op([42])
  // move op(memory) to register - register need memory cell (uint16, short address)              - case dst4 := op([1410])
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst1", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst2", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst3", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst4", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 6);

  // move op(memory) to register - register does not need memory cell (uint8, long address)       - case dst1 := op([42])
  // move op(memory) to register - register does not need memory cell (uint16, long address)      - case dst2 := op([1410])
  // move op(memory) to register - register need memory cell (uint8, long address)                - case dst3 := op([42])
  // move op(memory) to register - register need memory cell (uint16, long address)               - case dst4 := op([1410])
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst1", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst2", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst3", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst4", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 6);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsNV_MemoryToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(memory) to memory - register does not need memory cell (uint8, short address)        - case [dst1] := op([42])
  // move op(memory) to memory - register does not need memory cell (uint16, short address)       - case [dst2] := op([1410])
  // move op(memory) to memory - register need memory cell (uint8, short address)                 - case [dst1] := op([42])
  // move op(memory) to memory - register need memory cell (uint16, short address)                - case [dst4] := op([1410])
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst1", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst2", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst3", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst4", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 16);

  // move op(memory) to memory - register does not need memory cell (uint8, long address)         - case [dst1] := op([42])
  // move op(memory) to memory - register does not need memory cell (uint16, long address)        - case [dst2] := op([1410])
  // move op(memory) to memory - register need memory cell (uint8, long address)                  - case [dst1] := op([42])
  // move op(memory) to memory - register need memory cell (uint16, long address)                 - case [dst4] := op([1410])
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst1", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst2", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst3", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(1410, "dst4", BBUnaryOperationNV::SourceType::MEMORY, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), 16);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsNN_ConstantToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(constant) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(37, 42, BBUnaryOperationNN::SourceType::CONSTANT, BBUnaryOperationNN::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsNN_ConstantToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(constant) to memory - int8     - case [42] := op(37)
  // move op(constant) to memory - int16    - case [1410] := op(37)
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(37, 42, BBUnaryOperationNN::SourceType::CONSTANT, BBUnaryOperationNN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(37, 1410, BBUnaryOperationNN::SourceType::CONSTANT, BBUnaryOperationNN::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 2);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsNN_RegisterToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(register) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(37, 42, BBUnaryOperationNN::SourceType::REGISTER, BBUnaryOperationNN::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsNN_RegisterToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(register) to memory - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(37, 42, BBUnaryOperationNN::SourceType::REGISTER, BBUnaryOperationNN::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsNN_MemoryToRegister) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(memory) to register - not allowed for this template specialization
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(37, 42, BBUnaryOperationNN::SourceType::MEMORY, BBUnaryOperationNN::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions1;

  ASSERT_THROW(translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 0, machineInstructions1), std::invalid_argument);
}

TEST_P(unaryInstructionToMachineInstructionConversion, unaryOperationsNN_MemoryToMemory) {
  UnaryOpTestCaseConfig config = GetParam();

  // move op(memory) to memory - int8, int8     - case [37] := op([42])
  // move op(memory) to memory - int8, int16    - case [1410] := op([42])
  // move op(memory) to memory - int16, int8    - case [37] := op([1410])
  // move op(memory) to memory - int16, int16   - case [1410] := op([1920])
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(42, 37, BBUnaryOperationNN::SourceType::MEMORY, BBUnaryOperationNN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(42, 1410, BBUnaryOperationNN::SourceType::MEMORY, BBUnaryOperationNN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(1920, 37, BBUnaryOperationNN::SourceType::MEMORY, BBUnaryOperationNN::DestinationType::MEMORY, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBUnaryOperationNN>(1920, 1410, BBUnaryOperationNN::SourceType::MEMORY, BBUnaryOperationNN::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  ASSERT_EQ(machineInstructions1.size(), 8);
}

UnaryOpTestCaseConfig negTestCaseConfig{BBUnaryOperationEnum::NEG,
                                        {MachineInstruction{MachineInstruction::Type::NEG_A_A}},
                                        {MachineInstruction{MachineInstruction::Type::NEG_A_B}},
                                        {MachineInstruction{MachineInstruction::Type::NEG_B_A}},
                                        {MachineInstruction{MachineInstruction::Type::NEG_B_B}}};

INSTANTIATE_TEST_SUITE_P(unaryInstructions, unaryInstructionToMachineInstructionConversion, ::testing::Values(negTestCaseConfig));