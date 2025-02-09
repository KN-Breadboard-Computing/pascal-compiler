#include <fstream>
#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "../src/ast/program_node.hpp"
#include "../src/bblocks/bb_ssa_generator.hpp"
#include "../src/machine_code/machine_code_generator.hpp"

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program);

void translateBasicBlockToMachineCode(bblocks::BasicBlock&& basicBlock,
                                      std::vector<machine_code::MachineInstruction>& machineInstructions,
                                      std::ostream& registerAllocationInfo) {
  bblocks::BBControlFlowGraph cfg{"main", basicBlock};

  bblocks::BbSsaGenerator ssaGenerator;
  ssaGenerator.toSsa("program", cfg);
  ssaGenerator.propagateConstants();
  ssaGenerator.removeRedundantAssignments();
  ssaGenerator.fromSsa();

  machine_code::MachineCodeGenerator machineCodeGenerator;
  machineCodeGenerator.generate(ssaGenerator.getControlFlowGraphs(),
                                machine_code::MachineCodeGenerator::RegisterAllocator::LINEAR_SCAN);
  machineInstructions = machineCodeGenerator.getMachineCode().at("program");
}

//TEST(instructionToMachineInstructionConversion, builtinFunctions) {}

//TEST(instructionToMachineInstructionConversion, moves) {}

TEST(instructionToMachineInstructionConversion, unaryOperations) {
  const std::vector<std::pair<bblocks::BBUnaryOperationEnum, machine_code::MachineInstruction::Type::NEG_A_A>> operations = {
      bblocks::BBUnaryOperationEnum::NEG, bblocks::BBUnaryOperationEnum::NOT, bblocks::BBUnaryOperationEnum::INC,
      bblocks::BBUnaryOperationEnum::DEC, bblocks::BBUnaryOperationEnum::SHL, bblocks::BBUnaryOperationEnum::SHL,
      bblocks::BBUnaryOperationEnum::SAR};

  for (const auto operation : operations) {
    bblocks::BasicBlock basicBlock;
    basicBlock.addInstruction(std::make_unique<bblocks::BBMoveNV>(0, "src", bblocks::BBMoveVV::SourceType::CONSTANT,
                                                                  bblocks::BBMoveVV::DestinationType::REGISTER));
    basicBlock.addInstruction(std::make_unique<bblocks::BBUnaryOperationVV>(
        "src", "dst", bblocks::BBUnaryOperationVV::SourceType::REGISTER, bblocks::BBUnaryOperationVV::DestinationType::REGISTER,
        bblocks::BBUnaryOperationEnum::NEG));

    std::vector<machine_code::MachineInstruction> machineInstructions;
    std::stringstream tmp;
    translateBasicBlockToMachineCode(std::move(basicBlock), machineInstructions, tmp);

    std::cout << "Machine instructions: " << std::endl;
    for (const auto& machineInstruction : machineInstructions) {
      std::cout << machineInstruction.toString() << std::endl;
    }

    ASSERT_EQ(machineInstructions.size(), 3);
    ASSERT_EQ(machineInstructions[0].getType(), machine_code::MachineInstruction::Type::LABEL);
    ASSERT_EQ(machineInstructions[0].getOperands().size(), 1);
    ASSERT_EQ(machineInstructions[0].getOperands()[0], "main");
    ASSERT_EQ(machineInstructions[1].getType(), operation.second);
    ASSERT_EQ(machineInstructions[1].getOperands().size(), 1);
    ASSERT_EQ(machineInstructions[1].getOperands()[0], "0b00000000");
    ASSERT_EQ(machineInstructions[2].getType(), machine_code::MachineInstruction::Type::NEG_A_A);
    ASSERT_EQ(machineInstructions[2].getOperands().size(), 0);
  }
}

//TEST(instructionToMachineInstructionConversion, binaryOperations) {}

//TEST(instructionToMachineInstructionConversion, branches) {}

//TEST(instructionToMachineInstructionConversion, calls) {}

//TEST(instructionToMachineInstructionConversion, returns) {}

//TEST(instructionToMachineInstructionConversion, phis) {}

//TEST(instructionToMachineInstructionConversion, halts) {}

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