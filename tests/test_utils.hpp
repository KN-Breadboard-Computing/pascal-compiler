#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include "../src/ast/program_node.hpp"
#include "../src/bblocks/bb_ssa_generator.hpp"
#include "../src/machine_code/machine_code_generator.hpp"

#include "emulator_connector.hpp"

void translateBasicBlockToMachineCode(const std::vector<std::string>& readVariables, const std::vector<std::string>& writeVariables, bblocks::BasicBlock&& basicBlock, uint16_t variablesOffset,
                                      std::vector<machine_code::MachineInstruction>& machineInstructions) {
  constexpr std::size_t readVariableStepsNumber = 1;
  constexpr std::size_t writeVariableStepsNumber = 1;

  for (const auto& variable : std::ranges::views::reverse(readVariables)) {
    std::vector<bblocks::BBCall::Argument> readArguments;
    readArguments.emplace_back(bblocks::BBCall::Argument::Type::VARIABLE_DEF, variable, 0);
    basicBlock.addInstructionToStart(std::make_unique<bblocks::BBCall>("read", std::move(readArguments), false));
  }

  for (const auto& variable : writeVariables) {
    std::vector<bblocks::BBCall::Argument> writeArguments;
    writeArguments.emplace_back(bblocks::BBCall::Argument::Type::VARIABLE_USE, variable, 0);
    basicBlock.addInstruction(std::make_unique<bblocks::BBCall>("write", std::move(writeArguments), false));
  }

  basicBlock.addInstruction(std::make_unique<bblocks::BBHalt>());

  bblocks::BBControlFlowGraph functionCfg{"main", basicBlock};
  std::map<std::string, bblocks::BBControlFlowGraph> programCfg = {{"program", functionCfg}};

  machine_code::MachineCodeGenerator machineCodeGenerator;
  machineCodeGenerator.generate(programCfg, machine_code::MachineCodeGenerator::RegisterAllocator::LINEAR_SCAN, variablesOffset);
  machineInstructions.insert(machineInstructions.end(), machineCodeGenerator.getMachineCode().at("program").begin() + readVariableStepsNumber * readVariables.size() + 1,
                             machineCodeGenerator.getMachineCode().at("program").end() - writeVariableStepsNumber * writeVariables.size() - 1);
}

void translateBasicBlockToBinaryCode(const std::vector<std::string>& readVariables, const std::vector<std::string>& writeVariables, bblocks::BasicBlock&& basicBlock, uint16_t variablesOffset, std::vector<uint8_t>& binaryCode) {
  constexpr std::size_t readVariableStepsNumber = 1;
  constexpr std::size_t writeVariableStepsNumber = 1;

  for (const auto& variable : std::ranges::views::reverse(readVariables)) {
    std::vector<bblocks::BBCall::Argument> readArguments;
    readArguments.emplace_back(bblocks::BBCall::Argument::Type::VARIABLE_DEF, variable, 0);
    basicBlock.addInstructionToStart(std::make_unique<bblocks::BBCall>("read", std::move(readArguments), false));
  }

  for (const auto& variable : writeVariables) {
    std::vector<bblocks::BBCall::Argument> writeArguments;
    writeArguments.emplace_back(bblocks::BBCall::Argument::Type::VARIABLE_USE, variable, 0);
    basicBlock.addInstruction(std::make_unique<bblocks::BBCall>("write", std::move(writeArguments), false));
  }

  basicBlock.addInstruction(std::make_unique<bblocks::BBHalt>());

  bblocks::BBControlFlowGraph functionCfg{"main", basicBlock};
  std::map<std::string, bblocks::BBControlFlowGraph> programCfg = {{"program", functionCfg}};

  machine_code::MachineCodeGenerator machineCodeGenerator;
  machineCodeGenerator.generate(programCfg, machine_code::MachineCodeGenerator::RegisterAllocator::LINEAR_SCAN, variablesOffset);

  binaryCode = machineCodeGenerator.getBinaryCode();
  binaryCode.erase(binaryCode.begin(), binaryCode.begin() + readVariableStepsNumber * readVariables.size());
  binaryCode.erase(binaryCode.end() - writeVariableStepsNumber * writeVariables.size() - 1, binaryCode.end());
}

void prepareEmulatorForTest(EmulatorConnector& emulator, const std::vector<uint8_t>& binaryCode, const std::map<uint16_t, uint8_t>& nonZeroMemory = {}, uint8_t registerA = 0, uint8_t registerB = 0, uint16_t instructionCounter = 0x0000,
                            uint16_t stackPointer = 0xFFFF) {
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

#endif  // TEST_UTILS_HPP