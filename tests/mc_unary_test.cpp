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

  ASSERT_EQ(machineInstructions1.size(), config.pureOpMemZpB.size() + config.pureOpBA.size() + config.pureOpAA.size() + config.pureOpMemZpA.size() + 4);

  size_t cnt = 0;
  for (size_t i = 0; i < config.pureOpMemZpB.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpB.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpB.at(i).getOperands().size());
    if (!config.pureOpMemZpB.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000000"});
    }
    ++cnt;
  }

  for (size_t i = 0; i < config.pureOpBA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpBA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpBA.at(i).getOperands().size());
    if (!config.pureOpBA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    if (!config.pureOpAA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000011"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000001"});
    }
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

  ASSERT_EQ(machineInstructions2.size(), config.pureOpMemB.size() + config.pureOpBA.size() + config.pureOpAA.size() + config.pureOpMemA.size() + 4);

  cnt = 0;
  for (size_t i = 0; i < config.pureOpMemB.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemB.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemB.at(i).getOperands().size());
    if (!config.pureOpMemB.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));
    }
    ++cnt;
  }

  for (size_t i = 0; i < config.pureOpBA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpBA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpBA.at(i).getOperands().size());
    if (!config.pureOpBA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000010"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    if (!config.pureOpAA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000011"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;
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

  ASSERT_EQ(machineInstructions1.size(), config.pureOpStcB.size() + config.pureOpStcA.size() + config.pureOpBB.size() + config.pureOpStcA.size() + 16);

  size_t cnt = 0;
  for (size_t i = 0; i < config.pureOpStcB.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpStcB.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpStcB.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000000"});
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_TL_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpStcA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpStcA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpStcA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_B_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_B_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpBB.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpBB.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpBB.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_A_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000011"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpStcA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpStcA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpStcA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000001"});
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

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

  ASSERT_EQ(machineInstructions2.size(), config.pureOpStcB.size() + config.pureOpStcA.size() + config.pureOpBB.size() + config.pureOpStcA.size() + 16);

  cnt = 0;
  for (size_t i = 0; i < config.pureOpStcB.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpStcB.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpStcB.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_TL_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpStcA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpStcA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpStcA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_B_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_B_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000010"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpBB.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpBB.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpBB.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_A_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000011"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpStcA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpStcA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpStcA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;
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

  ASSERT_EQ(machineInstructions1.size(), config.pureOpMemZpA.size() + config.pureOpBB.size() + config.pureOpAA.size() + config.pureOpMemZpA.size() + 12);

  size_t cnt = 0;
  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_AT_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000000"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_B_AT_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpBB.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpBB.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpBB.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000010"});
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000011"});
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000001"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

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

  ASSERT_EQ(machineInstructions2.size(), config.pureOpMemA.size() + config.pureOpBB.size() + config.pureOpAA.size() + config.pureOpMemA.size() + 12);

  cnt = 0;
  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_AT_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_B_AT_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpBB.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpBB.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpBB.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000010"}));
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000011"}));
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;
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

  ASSERT_EQ(machineInstructions1.size(), config.pureOpStcA.size() + config.pureOpAA.size() + config.pureOpBB.size() + config.pureOpAA.size() + 25);

  size_t cnt = 0;
  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_AT_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpStcA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpStcA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpStcA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000000"});
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_TH_AT_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_B_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_B_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000010"});
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_TL_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_B_AT_TL);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpBB.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpBB.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpBB.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_A_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000001"});
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000011"});
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_TL_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

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

  ASSERT_EQ(machineInstructions2.size(), config.pureOpStcA.size() + config.pureOpAA.size() + config.pureOpBB.size() + config.pureOpAA.size() + 25);

  cnt = 0;
  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_AT_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpStcA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpStcA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpStcA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_TH_AT_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_B_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_B_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000010"}));
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_TL_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_B_AT_TL);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpBB.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpBB.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpBB.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_A_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000011"}));
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_TL);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_TL_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;
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

  ASSERT_EQ(machineInstructions1.size(), config.pureOpMemZpB.size() + config.pureOpMemA.size() + config.pureOpMemZpA.size() + config.pureOpMemA.size() + 6);

  size_t cnt = 0;
  for (size_t i = 0; i < config.pureOpMemZpB.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpB.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpB.at(i).getOperands().size());
    if (!config.pureOpMemZpB.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
    }
    ++cnt;
  }

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000000"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000001"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

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

  ASSERT_EQ(machineInstructions2.size(), config.pureOpMemZpB.size() + config.pureOpMemA.size() + config.pureOpMemZpA.size() + config.pureOpMemA.size() + 6);

  cnt = 0;
  for (size_t i = 0; i < config.pureOpMemZpB.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemZpB.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemZpB.at(i).getOperands().size());
    if (!config.pureOpMemZpB.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
    }
    ++cnt;
  }

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;
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

  ASSERT_EQ(machineInstructions1.size(), config.pureOpMemZpA.size() + config.pureOpMemB.size() + config.pureOpMemZpA.size() + config.pureOpMemA.size() + 16);

  size_t cnt = 0;
  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_AT_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_B_AT_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemB.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemB.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemB.at(i).getOperands().size());
    if (!config.pureOpMemB.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000000"});
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000001"});
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

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

  ASSERT_EQ(machineInstructions2.size(), config.pureOpMemZpA.size() + config.pureOpMemB.size() + config.pureOpMemZpA.size() + config.pureOpMemA.size() + 16);

  cnt = 0;
  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_AT_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_B_AT_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemB.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemB.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemB.at(i).getOperands().size());
    if (!config.pureOpMemB.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_TL_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_AT_TL);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;
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

  ASSERT_EQ(machineInstructions1.size(), config.pureOpAA.size() + config.pureOpMemZpA.size() + 4);

  size_t cnt = 0;
  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_IMM);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    if (!config.pureOpAA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_IMM);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000000"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  // move op(constant) to register - register does not need memory cell (long address)   - case src2 := op(42)
  // move op(constant) to register - register need memory cell (long address)            - case src3 := op(42)
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst2", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst3", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::REGISTER, config.operation));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions2.size(), config.pureOpAA.size() + config.pureOpMemA.size() + 4);

  cnt = 0;
  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_IMM);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    if (!config.pureOpAA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_IMM);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;
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

  ASSERT_EQ(machineInstructions1.size(), config.pureOpBB.size() + config.pureOpStcA.size() + 10);

  size_t cnt = 0;
  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_B_IMM);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpBB.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpBB.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpBB.at(i).getOperands().size());
    if (!config.pureOpBB.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_A_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_IMM);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpStcA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpStcA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpStcA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000000"});
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  // move op(constant) to memory - register does not need memory cell (long address)   - case [src2] := op(42)
  // move op(constant) to memory - register need memory cell (long address)            - case [src3] := op(42)
  BasicBlock basicBlock2;
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst2", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  basicBlock2.addInstruction(std::make_unique<BBUnaryOperationNV>(42, "dst3", BBUnaryOperationNV::SourceType::CONSTANT, BBUnaryOperationNV::DestinationType::MEMORY, config.operation));
  std::vector<MachineInstruction> machineInstructions2;
  translateBasicBlockToMachineCode({"dst1"}, {"dst1", "dst2", "dst3"}, std::move(basicBlock2), 1 << 10, machineInstructions2);

  ASSERT_EQ(machineInstructions1.size(), config.pureOpBB.size() + config.pureOpStcA.size() + 10);

  cnt = 0;
  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_B_IMM);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpBB.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpBB.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpBB.at(i).getOperands().size());
    if (!config.pureOpBB.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_A_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_IMM);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpStcA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpStcA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpStcA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;
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

  ASSERT_EQ(machineInstructions1.size(), config.pureOpBB.size() + config.pureOpAA.size() + config.pureOpMemZpA.size() + config.pureOpMemZpA.size() + 8);

  size_t cnt = 0;
  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_B_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpBB.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpBB.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpBB.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000000"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000001"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

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

  ASSERT_EQ(machineInstructions2.size(), config.pureOpBB.size() + config.pureOpAA.size() + config.pureOpMemA.size() + config.pureOpMemA.size() + 8);

  cnt = 0;
  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_B_ABS_ZP);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpBB.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpBB.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpBB.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;
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

  ASSERT_EQ(machineInstructions1.size(), config.pureOpAA.size() + config.pureOpBB.size() + config.pureOpStcA.size() + config.pureOpStcA.size() + 20);

  size_t cnt = 0;
  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_B_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_B_ABS);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpBB.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpBB.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpBB.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_A_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpStcA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpStcA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpStcA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000000"});
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpStcA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpStcA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpStcA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b01000001"});
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

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

  ASSERT_EQ(machineInstructions2.size(), config.pureOpAA.size() + config.pureOpBB.size() + config.pureOpStcA.size() + config.pureOpStcA.size() + 20);

  cnt = 0;
  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpAA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpAA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpAA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_B_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_B_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpBB.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpBB.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpBB.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_A_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_B);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpStcA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpStcA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpStcA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000000"}));
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpStcA.size(); ++i) {
    ASSERT_EQ(machineInstructions2.at(cnt).getType(), config.pureOpStcA.at(i).getType());
    ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), config.pureOpStcA.at(i).getOperands().size());
    ++cnt;
  }

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands(), (std::vector<std::string>{"0b00000100", "0b00000001"}));
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::MOV_AT_A_TH);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions2.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions2.at(cnt).getOperands().size(), 0);
  ++cnt;
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

  ASSERT_EQ(machineInstructions1.size(), config.pureOpMemZpA.size() + config.pureOpMemZpA.size() + 6);

  size_t cnt = 0;
  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_IMM);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00100101"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_IMM);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00100101"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;
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

  ASSERT_EQ(machineInstructions1.size(), config.pureOpMemZpA.size() + config.pureOpMemA.size() + config.pureOpMemZpA.size() + config.pureOpMemA.size() + 12);

  size_t cnt = 0;
  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00100101"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS_ZP);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 1);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00101010"});
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), (std::vector<std::string>{"0b00000111", "0b10000000"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemZpA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemZpA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemZpA.at(i).getOperands().size());
    if (!config.pureOpMemZpA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), std::vector<std::string>{"0b00100101"});
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::PUSH_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::MOV_A_ABS);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 2);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), (std::vector<std::string>{"0b00000111", "0b10000000"}));
  ++cnt;

  for (size_t i = 0; i < config.pureOpMemA.size(); ++i) {
    ASSERT_EQ(machineInstructions1.at(cnt).getType(), config.pureOpMemA.at(i).getType());
    ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), config.pureOpMemA.at(i).getOperands().size());
    if (!config.pureOpMemA.at(i).getOperands().empty()) {
      ASSERT_EQ(machineInstructions1.at(cnt).getOperands(), (std::vector<std::string>{"0b00000101", "0b10000010"}));
    }
    ++cnt;
  }

  ASSERT_EQ(machineInstructions1.at(cnt).getType(), MachineInstruction::POP_A);
  ASSERT_EQ(machineInstructions1.at(cnt).getOperands().size(), 0);
  ++cnt;
}

UnaryOpTestCaseConfig negTestCaseConfig{BBUnaryOperationEnum::NEG,
                                        {MachineInstruction{MachineInstruction::NEG_A_A}},
                                        {MachineInstruction{MachineInstruction::NEG_A_B}},
                                        {MachineInstruction{MachineInstruction::NEG_B_A}},
                                        {MachineInstruction{MachineInstruction::NEG_B_B}},
                                        {MachineInstruction{MachineInstruction::NEG_MEM_A, {"arg1", "arg2"}}},
                                        {MachineInstruction{MachineInstruction::NEG_MEM_ZP_A, {"arg1"}}},
                                        {MachineInstruction{MachineInstruction::NEG_MEM_B, {"arg1", "arg2"}}},
                                        {MachineInstruction{MachineInstruction::NEG_MEM_ZP_B, {"arg1"}}},
                                        {MachineInstruction{MachineInstruction::NEG_STC_A}},
                                        {MachineInstruction{MachineInstruction::NEG_STC_B}}};

UnaryOpTestCaseConfig notTestCaseConfig{BBUnaryOperationEnum::NOT,
                                        {MachineInstruction{MachineInstruction::INV_A_A}},
                                        {MachineInstruction{MachineInstruction::INV_A_B}},
                                        {MachineInstruction{MachineInstruction::INV_B_A}},
                                        {MachineInstruction{MachineInstruction::INV_B_B}},
                                        {MachineInstruction{MachineInstruction::INV_MEM_A, {"arg1", "arg2"}}},
                                        {MachineInstruction{MachineInstruction::INV_MEM_ZP_A, {"arg1"}}},
                                        {MachineInstruction{MachineInstruction::INV_MEM_B, {"arg1", "arg2"}}},
                                        {MachineInstruction{MachineInstruction::INV_MEM_ZP_B, {"arg1"}}},
                                        {MachineInstruction{MachineInstruction::INV_STC_A}},
                                        {MachineInstruction{MachineInstruction::INV_STC_B}}};

UnaryOpTestCaseConfig incTestCaseConfig{BBUnaryOperationEnum::INC,
                                        {MachineInstruction{MachineInstruction::INC_A}},
                                        {MachineInstruction{MachineInstruction::INC_B}, MachineInstruction{MachineInstruction::MOV_A_B}, MachineInstruction{MachineInstruction::DEC_B}},
                                        {MachineInstruction{MachineInstruction::INC_A}, MachineInstruction{MachineInstruction::MOV_B_A}, MachineInstruction{MachineInstruction::DEC_A}},
                                        {MachineInstruction{MachineInstruction::INC_B}},
                                        {MachineInstruction{MachineInstruction::INC_A}, MachineInstruction{MachineInstruction::MOV_AT_ABS_A, {"arg1", "arg2"}}, MachineInstruction{MachineInstruction::DEC_A}},
                                        {MachineInstruction{MachineInstruction::INC_A}, MachineInstruction{MachineInstruction::MOV_AT_ABS_A_ZP, {"arg1"}}, MachineInstruction{MachineInstruction::DEC_A}},
                                        {MachineInstruction{MachineInstruction::INC_B}, MachineInstruction{MachineInstruction::MOV_AT_ABS_B, {"arg1", "arg2"}}, MachineInstruction{MachineInstruction::DEC_B}},
                                        {MachineInstruction{MachineInstruction::INC_B}, MachineInstruction{MachineInstruction::MOV_AT_ABS_B_ZP, {"arg1"}}, MachineInstruction{MachineInstruction::DEC_B}},
                                        {MachineInstruction{MachineInstruction::INC_A}, MachineInstruction{MachineInstruction::PUSH_A}, MachineInstruction{MachineInstruction::DEC_A}},
                                        {MachineInstruction{MachineInstruction::INC_B}, MachineInstruction{MachineInstruction::PUSH_B}, MachineInstruction{MachineInstruction::DEC_B}}};

UnaryOpTestCaseConfig decTestCaseConfig{BBUnaryOperationEnum::DEC,
                                        {MachineInstruction{MachineInstruction::DEC_A}},
                                        {MachineInstruction{MachineInstruction::DEC_B}, MachineInstruction{MachineInstruction::MOV_A_B}, MachineInstruction{MachineInstruction::INC_B}},
                                        {MachineInstruction{MachineInstruction::DEC_A}, MachineInstruction{MachineInstruction::MOV_B_A}, MachineInstruction{MachineInstruction::INC_A}},
                                        {MachineInstruction{MachineInstruction::DEC_B}},
                                        {MachineInstruction{MachineInstruction::DEC_A}, MachineInstruction{MachineInstruction::MOV_AT_ABS_A, {"arg1", "arg2"}}, MachineInstruction{MachineInstruction::INC_A}},
                                        {MachineInstruction{MachineInstruction::DEC_A}, MachineInstruction{MachineInstruction::MOV_AT_ABS_A_ZP, {"arg1"}}, MachineInstruction{MachineInstruction::INC_A}},
                                        {MachineInstruction{MachineInstruction::DEC_B}, MachineInstruction{MachineInstruction::MOV_AT_ABS_B, {"arg1", "arg2"}}, MachineInstruction{MachineInstruction::INC_B}},
                                        {MachineInstruction{MachineInstruction::DEC_B}, MachineInstruction{MachineInstruction::MOV_AT_ABS_B_ZP, {"arg1"}}, MachineInstruction{MachineInstruction::INC_B}},
                                        {MachineInstruction{MachineInstruction::DEC_A}, MachineInstruction{MachineInstruction::PUSH_A}, MachineInstruction{MachineInstruction::INC_A}},
                                        {MachineInstruction{MachineInstruction::DEC_B}, MachineInstruction{MachineInstruction::PUSH_B}, MachineInstruction{MachineInstruction::INC_B}}};

UnaryOpTestCaseConfig shlTestCaseConfig{BBUnaryOperationEnum::SHL,
                                        {MachineInstruction{MachineInstruction::SHL_A_A}},
                                        {MachineInstruction{MachineInstruction::SHL_A_B}},
                                        {MachineInstruction{MachineInstruction::SHL_B_A}},
                                        {MachineInstruction{MachineInstruction::SHL_B_B}},
                                        {MachineInstruction{MachineInstruction::SHL_MEM_A, {"arg1", "arg2"}}},
                                        {MachineInstruction{MachineInstruction::SHL_MEM_ZP_A, {"arg1"}}},
                                        {MachineInstruction{MachineInstruction::SHL_MEM_B, {"arg1", "arg2"}}},
                                        {MachineInstruction{MachineInstruction::SHL_MEM_ZP_B, {"arg1"}}},
                                        {MachineInstruction{MachineInstruction::SHL_STC_A}},
                                        {MachineInstruction{MachineInstruction::SHL_STC_B}}};

UnaryOpTestCaseConfig shrTestCaseConfig{BBUnaryOperationEnum::SHR,
                                        {MachineInstruction{MachineInstruction::SHR_A_A}},
                                        {MachineInstruction{MachineInstruction::SHR_A_B}},
                                        {MachineInstruction{MachineInstruction::SHR_B_A}},
                                        {MachineInstruction{MachineInstruction::SHR_B_B}},
                                        {MachineInstruction{MachineInstruction::SHR_MEM_A, {"arg1", "arg2"}}},
                                        {MachineInstruction{MachineInstruction::SHR_MEM_ZP_A, {"arg1"}}},
                                        {MachineInstruction{MachineInstruction::SHR_MEM_B, {"arg1", "arg2"}}},
                                        {MachineInstruction{MachineInstruction::SHR_MEM_ZP_B, {"arg1"}}},
                                        {MachineInstruction{MachineInstruction::SHR_STC_A}},
                                        {MachineInstruction{MachineInstruction::SHR_STC_B}}};

UnaryOpTestCaseConfig sarTestCaseConfig{BBUnaryOperationEnum::SAR,
                                        {MachineInstruction{MachineInstruction::DIV2_A_A}},
                                        {MachineInstruction{MachineInstruction::DIV2_A_B}},
                                        {MachineInstruction{MachineInstruction::DIV2_B_A}},
                                        {MachineInstruction{MachineInstruction::DIV2_B_B}},
                                        {MachineInstruction{MachineInstruction::DIV2_MEM_A, {"arg1", "arg2"}}},
                                        {MachineInstruction{MachineInstruction::DIV2_MEM_ZP_A, {"arg1"}}},
                                        {MachineInstruction{MachineInstruction::DIV2_MEM_B, {"arg1", "arg2"}}},
                                        {MachineInstruction{MachineInstruction::DIV2_MEM_ZP_B, {"arg1"}}},
                                        {MachineInstruction{MachineInstruction::DIV2_STC_A}},
                                        {MachineInstruction{MachineInstruction::DIV2_STC_B}}};

INSTANTIATE_TEST_SUITE_P(unaryInstructions, unaryInstructionToMachineInstructionConversion, ::testing::Values(negTestCaseConfig, notTestCaseConfig, /*, incTestCaseConfig, decTestCaseConfig*/ shlTestCaseConfig, shrTestCaseConfig, sarTestCaseConfig));