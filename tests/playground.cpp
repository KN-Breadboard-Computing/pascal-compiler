#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>

#include "../src/ast/program_node.hpp"
#include "../src/bblocks/bb_ssa_generator.hpp"
#include "../src/machine_code/machine_code_generator.hpp"

using namespace bblocks;
using namespace machine_code;

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program);

void readVariables(BasicBlock& basicBlock, const std::vector<std::string>& variables) {
  for (const auto& variable : variables) {
    std::vector<BBCall::Argument> readArguments;
    readArguments.emplace_back(BBCall::Argument::Type::VARIABLE_DEF, variable, 0);
    basicBlock.addInstructionToStart(std::make_unique<BBCall>("read", std::move(readArguments), false));
  }
}

void writeVariables(BasicBlock& basicBlock, const std::vector<std::string>& variables) {
  for (const auto& variable : variables) {
    std::vector<BBCall::Argument> writeArguments;
    writeArguments.emplace_back(BBCall::Argument::Type::VARIABLE_USE, variable, 0);
    basicBlock.addInstruction(std::make_unique<BBCall>("write", std::move(writeArguments), false));
  }
}

void halt(BasicBlock& basicBlock) {
  basicBlock.addInstruction(std::make_unique<BBHalt>());
}

void translateBasicBlockToMachineCode(const std::vector<std::string>& readVariables, const std::vector<std::string>& writeVariables, BasicBlock&& basicBlock, uint16_t variablesOffset, std::vector<MachineInstruction>& /*code*/) {
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
  std::vector<MachineInstruction> machineInstructions;
  machineInstructions.insert(machineInstructions.end(), machineCodeGenerator.getMachineCode().at("program").begin() + readVariableStepsNumber * readVariables.size() + 1,
                             machineCodeGenerator.getMachineCode().at("program").end() - writeVariableStepsNumber * writeVariables.size() - 1);

  std::cout << "Basic Block:" << std::endl << basicBlock << std::endl;

  std::cout << "Live Ranges:" << std::endl;
  machineCodeGenerator.saveLiveRanges(std::cout);
  std::cout << std::endl;

  std::cout << "Machine Instructions:" << std::endl;
  for (const auto& instruction : machineInstructions) {
    std::cout << instruction.toString() << std::endl;
  }
  std::cout << std::endl;

  std::vector<std::string> assembly = machineCodeGenerator.getAssembly();
  assembly.erase(assembly.begin(), assembly.begin() + readVariableStepsNumber * readVariables.size());
  assembly.erase(assembly.end() - writeVariableStepsNumber * writeVariables.size() - 1, assembly.end());

  std::cout << "Assembly Code:" << std::endl;
  for (const auto& instruction : assembly) {
    std::cout << instruction << std::endl;
  }
  std::cout << std::endl;

  std::vector<uint8_t> binaryCode = machineCodeGenerator.getBinaryCode();
  binaryCode.erase(binaryCode.begin(), binaryCode.begin() + readVariableStepsNumber * readVariables.size());
  binaryCode.erase(binaryCode.end() - writeVariableStepsNumber * writeVariables.size() - 1, binaryCode.end());

  std::cout << "Binary Code:" << std::endl;
  for (const auto& byte : binaryCode) {
    std::cout << std::hex << static_cast<int>(byte) << " ";
  }
  std::cout << std::dec << std::endl;
}

struct BinaryOpTestCaseConfig {
  BBBinaryOperationEnum operation;
  size_t pureOpOffset;
  std::function<uint8_t(uint8_t, uint8_t)> opFunc;
};

int main() {
  //  BasicBlock basicBlock1;
  //  std::vector<MachineInstruction> machineInstructions1;
  //  translateBasicBlockToMachineCode({}, {"dst1", "dst2", "dst3", "dst4"}, std::move(basicBlock1), 1 << 5, machineInstructions1);

  //  BasicBlock basicBlock2;
  //  std::vector<MachineInstruction> machineInstructions2;
  //  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock2),
  //                                   1 << 5, machineInstructions2);

  BinaryOpTestCaseConfig config{BBBinaryOperationEnum::ADD, 1, [](uint8_t x, uint8_t y) {
                                  return static_cast<uint8_t>(x + y);
                                }};
  BasicBlock basicBlock1;
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src1", "dst1", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src2", "dst2", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src3", "dst3", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(42, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));
  basicBlock1.addInstruction(std::make_unique<BBBinaryOperationNVV>(1410, "src4", "dst4", BBBinaryOperationNVV::SourceType::MEMORY, BBBinaryOperationNVV::SourceType::REGISTER, BBUnaryOperationVV::DestinationType::REGISTER, config.operation));

  std::vector<MachineInstruction> machineInstructions1;
  translateBasicBlockToMachineCode({"src1", "src2", "src3", "src4"}, {}, std::move(basicBlock1), 1 << 6, machineInstructions1);

  return 0;
}