#ifndef MACHINE_CODE_MACHINE_CODE_GENERATOR_HPP
#define MACHINE_CODE_MACHINE_CODE_GENERATOR_HPP

#include <bitset>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "../bblocks/bb_control_flow_graph.hpp"
#include "live_ranges_generator.hpp"
#include "machine_instruction.hpp"

#include "../bblocks/instructions/bb_binary_operation.hpp"
#include "../bblocks/instructions/bb_branch.hpp"
#include "../bblocks/instructions/bb_call.hpp"
#include "../bblocks/instructions/bb_halt.hpp"
#include "../bblocks/instructions/bb_move.hpp"
#include "../bblocks/instructions/bb_phi.hpp"
#include "../bblocks/instructions/bb_ret.hpp"
#include "../bblocks/instructions/bb_unary_operation.hpp"

namespace machine_code {
class MachineCodeGenerator {
 public:
  MachineCodeGenerator() = default;

  MachineCodeGenerator(const MachineCodeGenerator&) = delete;
  MachineCodeGenerator(MachineCodeGenerator&&) = default;

  MachineCodeGenerator& operator=(const MachineCodeGenerator&) = delete;
  MachineCodeGenerator& operator=(MachineCodeGenerator&&) = default;

  ~MachineCodeGenerator() = default;

  void generate(const std::map<std::string, bblocks::BBControlFlowGraph>& cfg);
  void saveMachineCode(const std::string& filename);
  void saveAssembly(const std::string& filename);
  void saveBinary(const std::string& filename);

 private:
  void enumerateBlockLabels(const std::string& name, const bblocks::BBControlFlowGraph& cfg);
  void generateVariableAddresses(const std::string& name, const bblocks::BBControlFlowGraph& cfg,
                                 const LiveRangesGenerator& liveRanges);
  void calculateLabelValues(const std::string& name);

  std::vector<MachineInstruction> generate(const std::unique_ptr<bblocks::BBInstruction>& instruction);

  std::vector<MachineInstruction> generateMove(const bblocks::BBMoveVV& instruction);
  std::vector<MachineInstruction> generateMove(const bblocks::BBMoveVN& instruction);
  std::vector<MachineInstruction> generateMove(const bblocks::BBMoveNV& instruction);
  std::vector<MachineInstruction> generateMove(const bblocks::BBMoveNN& instruction);

  std::vector<MachineInstruction> generateUnaryOperation(const bblocks::BBUnaryOperationVV& instruction);
  std::vector<MachineInstruction> generateUnaryOperation(const bblocks::BBUnaryOperationVN& instruction);
  std::vector<MachineInstruction> generateUnaryOperation(const bblocks::BBUnaryOperationNV& instruction);
  std::vector<MachineInstruction> generateUnaryOperation(const bblocks::BBUnaryOperationNN& instruction);

  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationVVV& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationVVN& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationVNV& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationVNN& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationNVV& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationNVN& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationNNV& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationNNN& instruction);

  std::vector<MachineInstruction> generateBranch(const bblocks::BBBranchV& instruction);
  std::vector<MachineInstruction> generateBranch(const bblocks::BBBranchN& instruction);

  std::vector<MachineInstruction> generateCall(const bblocks::BBCall& instruction);
  std::vector<MachineInstruction> generateRet(const bblocks::BBRet& instruction);
  std::vector<MachineInstruction> generateHalt(const bblocks::BBHalt& instruction);

  static std::string getBinaryInt(int8_t number);
  static std::string getBinaryUint(uint8_t number);
  static std::string getBinaryAnyInt(int number);
  static std::pair<std::optional<std::string>, std::string> getBinaryAddress(uint16_t address);
  static std::pair<std::string, std::string> getBinaryFullAddress(uint16_t address);

  std::map<std::string, std::map<std::string, std::pair<size_t, size_t>>> blockBounds_;
  std::map<std::string, std::vector<MachineInstruction>> machineCode_;
  std::map<std::string, LiveRangesGenerator> liveRanges_;
  //  std::map<std::string, std::map<std::string, uint16_t>> variableAddresses_;
  std::map<std::string, uint16_t> variableAddresses_;
  std::map<std::string, std::map<std::string, uint16_t>> labelValues_;
};
}  // namespace machine_code

#endif  // MACHINE_CODE_MACHINE_CODE_GENERATOR_HPP