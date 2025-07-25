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
#include "../bblocks/instructions/bb_binary_operation.hpp"
#include "../bblocks/instructions/bb_branch.hpp"
#include "../bblocks/instructions/bb_call.hpp"
#include "../bblocks/instructions/bb_halt.hpp"
#include "../bblocks/instructions/bb_move.hpp"
#include "../bblocks/instructions/bb_phi.hpp"
#include "../bblocks/instructions/bb_ret.hpp"
#include "../bblocks/instructions/bb_unary_operation.hpp"

#include "live_range.hpp"
#include "live_ranges_generator.hpp"
#include "machine_instruction.hpp"

#include "register_allocation/interference_graph_reg_alloc.hpp"
#include "register_allocation/linear_scan_reg_alloc.hpp"
#include "register_allocation/reg_alloc.hpp"

#define MC_DEBUG

namespace machine_code {
class MachineCodeGenerator {
 public:
  enum RegisterAllocator { LINEAR_SCAN, GRAPH_COLORING };

  MachineCodeGenerator() = default;

  MachineCodeGenerator(const MachineCodeGenerator&) = delete;
  MachineCodeGenerator(MachineCodeGenerator&&) = default;

  MachineCodeGenerator& operator=(const MachineCodeGenerator&) = delete;
  MachineCodeGenerator& operator=(MachineCodeGenerator&&) = default;

  ~MachineCodeGenerator() = default;

  void generate(const std::map<std::string, bblocks::BBControlFlowGraph>& cfg, RegisterAllocator allocator, uint16_t variablesOffset);

  const std::map<std::string, std::vector<LiveRange>>& getLiveRanges(const std::string& name) const { return liveRanges_.at(name).getLiveRanges(); }
  void saveLiveRanges(std::ostream& output) const;

  const std::map<std::string, std::vector<MachineInstruction>>& getMachineCode() const { return machineCode_; }
  void saveMachineCode(std::ostream& output) const;

  std::vector<std::string> getAssembly() const;
  void saveAssembly(std::ostream& output) const;

  std::vector<uint8_t> getBinaryCode() const;
  void saveBinary(std::ostream& output) const;

 private:
  static int registersNumber_;

  void enumerateBlockLabels(const std::string& name, const bblocks::BBControlFlowGraph& cfg);
  void generateVariableAddresses(const std::string& name, uint16_t variablesOffset);
  void calculateLabelValues(const std::string& name);

  std::vector<MachineInstruction> generate(const std::unique_ptr<bblocks::BBInstruction>& instruction);

  std::vector<MachineInstruction> generateMove(const bblocks::BBMoveVV& instruction);
  std::vector<MachineInstruction> generateMove(const bblocks::BBMoveVN& instruction);
  std::vector<MachineInstruction> generateMove(const bblocks::BBMoveNV& instruction);
  std::vector<MachineInstruction> generateMove(const bblocks::BBMoveNN& instruction);

  std::vector<MachineInstruction> generateMoveConstReg(uint8_t src, int dest);                        // reg := const
  std::vector<MachineInstruction> generateMoveConstMem(uint8_t src, uint16_t dest);                   // [addr] := const
  std::vector<MachineInstruction> generateMoveConstMemImmReg(uint8_t src, int immDest);               // [reg] := const
  std::vector<MachineInstruction> generateMoveConstMemImmMem(uint8_t src, uint16_t immDest);          // [[addr]] := const
  std::vector<MachineInstruction> generateMoveRegReg(int src, int dest);                              // reg := reg
  std::vector<MachineInstruction> generateMoveRegMem(int src, uint16_t dest);                         // [addr] := reg
  std::vector<MachineInstruction> generateMoveRegMemImmReg(int src, int immDest);                     // [reg] := reg
  std::vector<MachineInstruction> generateMoveRegMemImmMem(int src, uint16_t immDest);                // [[addr]] := reg
  std::vector<MachineInstruction> generateMoveMemReg(uint16_t src, int dest);                         // reg := [addr]
  std::vector<MachineInstruction> generateMoveMemMem(uint16_t src, uint16_t dest);                    // [addr] := [addr]
  std::vector<MachineInstruction> generateMoveMemMemImmReg(uint16_t src, int immDest);                // [reg] := [addr]
  std::vector<MachineInstruction> generateMoveMemMemImmMem(uint16_t src, uint16_t immDest);           // [[addr]] := [addr]
  std::vector<MachineInstruction> generateMoveMemImmRegReg(int immSrc, int dest);                     // reg := [reg]
  std::vector<MachineInstruction> generateMoveMemImmRegMem(int immSrc, uint16_t dest);                // [addr] := [reg]
  std::vector<MachineInstruction> generateMoveMemImmRegMemImmReg(int immSrc, int immDest);            // [reg] := [reg]
  std::vector<MachineInstruction> generateMoveMemImmRegMemImmMem(int immSrc, uint16_t immDest);       // [[addr]] := [reg]
  std::vector<MachineInstruction> generateMoveMemImmMemReg(uint16_t immSrc, int dest);                // reg := [[addr]]
  std::vector<MachineInstruction> generateMoveMemImmMemMem(uint16_t immSrc, uint16_t dest);           // [addr] := [[addr]]
  std::vector<MachineInstruction> generateMoveMemImmMemMemImmReg(uint16_t immSrc, int immDest);       // [reg] := [[addr]]
  std::vector<MachineInstruction> generateMoveMemImmMemMemImmMem(uint16_t immSrc, uint16_t immDest);  // [[addr]] := [[addr]]

  std::vector<MachineInstruction> generateUnaryOperation(const bblocks::BBUnaryOperationVV& instruction);
  std::vector<MachineInstruction> generateUnaryOperation(const bblocks::BBUnaryOperationVN& instruction);
  std::vector<MachineInstruction> generateUnaryOperation(const bblocks::BBUnaryOperationNV& instruction);
  std::vector<MachineInstruction> generateUnaryOperation(const bblocks::BBUnaryOperationNN& instruction);

  std::vector<MachineInstruction> generateUnOpConstReg(uint8_t src, int dest, bblocks::BBUnaryOperationEnum op);                        // reg := op(const)
  std::vector<MachineInstruction> generateUnOpConstMem(uint8_t src, uint16_t dest, bblocks::BBUnaryOperationEnum op);                   // [addr] := op(const)
  std::vector<MachineInstruction> generateUnOpConstMemImmReg(uint8_t src, int immDest, bblocks::BBUnaryOperationEnum op);               // [reg] := op(const)
  std::vector<MachineInstruction> generateUnOpConstMemImmMem(uint8_t src, uint16_t immDest, bblocks::BBUnaryOperationEnum op);          // [[addr]] := op(const)
  std::vector<MachineInstruction> generateUnOpRegReg(int src, int dest, bblocks::BBUnaryOperationEnum op);                              // reg := op(reg)
  std::vector<MachineInstruction> generateUnOpRegMem(int src, uint16_t dest, bblocks::BBUnaryOperationEnum op);                         // [addr] := op(reg)
  std::vector<MachineInstruction> generateUnOpRegMemImmReg(int src, int immDest, bblocks::BBUnaryOperationEnum op);                     // [reg] := op(reg)
  std::vector<MachineInstruction> generateUnOpRegMemImmMem(int src, uint16_t immDest, bblocks::BBUnaryOperationEnum op);                // [[addr]] := op(reg)
  std::vector<MachineInstruction> generateUnOpMemReg(uint16_t src, int dest, bblocks::BBUnaryOperationEnum op);                         // reg := op([addr])
  std::vector<MachineInstruction> generateUnOpMemMem(uint16_t src, uint16_t dest, bblocks::BBUnaryOperationEnum op);                    // [addr] := op([addr])
  std::vector<MachineInstruction> generateUnOpMemMemImmReg(uint16_t src, int immDest, bblocks::BBUnaryOperationEnum op);                // [reg] := op([addr])
  std::vector<MachineInstruction> generateUnOpMemMemImmMem(uint16_t src, uint16_t immDest, bblocks::BBUnaryOperationEnum op);           // [[addr]] := op([addr])
  std::vector<MachineInstruction> generateUnOpMemImmRegReg(int immSrc, int dest, bblocks::BBUnaryOperationEnum op);                     // reg := op([reg])
  std::vector<MachineInstruction> generateUnOpMemImmRegMem(int immSrc, uint16_t dest, bblocks::BBUnaryOperationEnum op);                // [addr] := op([reg])
  std::vector<MachineInstruction> generateUnOpMemImmRegMemImmReg(int immSrc, int immDest, bblocks::BBUnaryOperationEnum op);            // [reg] := op([reg])
  std::vector<MachineInstruction> generateUnOpMemImmRegMemImmMem(int immSrc, uint16_t immDest, bblocks::BBUnaryOperationEnum op);       // [[addr]] := op([reg])
  std::vector<MachineInstruction> generateUnOpMemImmMemReg(uint16_t immSrc, int dest, bblocks::BBUnaryOperationEnum op);                // reg := op([[addr]])
  std::vector<MachineInstruction> generateUnOpMemImmMemMem(uint16_t immSrc, uint16_t dest, bblocks::BBUnaryOperationEnum op);           // [addr] := op([[addr]])
  std::vector<MachineInstruction> generateUnOpMemImmMemMemImmReg(uint16_t immSrc, int immDest, bblocks::BBUnaryOperationEnum op);       // [reg] := op([[addr]])
  std::vector<MachineInstruction> generateUnOpMemImmMemMemImmMem(uint16_t immSrc, uint16_t immDest, bblocks::BBUnaryOperationEnum op);  // [[addr]] := op([[addr]])

  void generateUnaryOperatorAA(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op);
  void generateUnaryOperatorAB(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op);
  void generateUnaryOperatorBA(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op);
  void generateUnaryOperatorBB(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op);
  void generateUnaryOperatorAMem(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op, uint16_t dest);
  void generateUnaryOperatorBMem(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op, uint16_t dest);
  void generateUnaryOperatorAStc(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op);
  void generateUnaryOperatorBStc(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op);

  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationVVV& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationVVN& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationVNV& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationVNN& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationNVV& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationNVN& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationNNV& instruction);
  std::vector<MachineInstruction> generateBinaryOperation(const bblocks::BBBinaryOperationNNN& instruction);

  std::vector<MachineInstruction> generateBinaryOperationRegRegReg(int src1, int src2, int dest, bblocks::BBBinaryOperationEnum type);
  std::vector<MachineInstruction> generateBinaryOperationRegRegMem(int src1, int src2, uint16_t dest, bblocks::BBBinaryOperationEnum type);
  std::vector<MachineInstruction> generateBinaryOperationRegMemReg(int src1, uint16_t src2, int dest, bblocks::BBBinaryOperationEnum type);
  std::vector<MachineInstruction> generateBinaryOperationRegMemMem(int src1, uint16_t src2, uint16_t dest, bblocks::BBBinaryOperationEnum type);
  std::vector<MachineInstruction> generateBinaryOperationMemRegReg(uint16_t src1, int src2, int dest, bblocks::BBBinaryOperationEnum type);
  std::vector<MachineInstruction> generateBinaryOperationMemRegMem(uint16_t src1, int src2, uint16_t dest, bblocks::BBBinaryOperationEnum type);
  std::vector<MachineInstruction> generateBinaryOperationMemMemReg(uint16_t src1, uint16_t src2, int dest, bblocks::BBBinaryOperationEnum type);
  std::vector<MachineInstruction> generateBinaryOperationMemMemMem(uint16_t src1, uint16_t src2, uint16_t dest, bblocks::BBBinaryOperationEnum type);

  std::vector<MachineInstruction> generateBranch(const bblocks::BBBranchV& instruction);
  std::vector<MachineInstruction> generateBranch(const bblocks::BBBranchN& instruction);
  std::vector<MachineInstruction> generateBranchReg(int val, bblocks::BBBranchCondition condition, const std::string& trueLabel, const std::string& falseLabel);
  std::vector<MachineInstruction> generateBranchMem(uint16_t val, bblocks::BBBranchCondition condition, const std::string& trueLabel, const std::string& falseLabel);
  std::vector<MachineInstruction> generateBranchConst(uint8_t val, bblocks::BBBranchCondition condition, const std::string& trueLabel, const std::string& falseLabel);
  void appendBranchJumps(std::vector<MachineInstruction>& instructions, bblocks::BBBranchCondition condition, const std::string& trueLabel, const std::string& falseLabel);

  std::vector<MachineInstruction> generateCall(const bblocks::BBCall& instruction);
  std::vector<MachineInstruction> generateRet(const bblocks::BBRet& instruction);
  std::vector<MachineInstruction> generateHalt(const bblocks::BBHalt& instruction);

  static std::string getBinaryInt(int8_t number);
  static std::string getBinaryUint(uint8_t number);
  static std::string getBinaryAnyInt(int number);
  static std::pair<std::optional<std::string>, std::string> getBinaryAddress(uint16_t address);
  static std::pair<std::string, std::string> getBinaryFullAddress(uint16_t address);

  std::string currentScope;
  std::map<std::string, std::map<std::string, std::pair<std::size_t, std::size_t>>> blockBounds_;
  std::map<std::string, std::vector<std::string>> blocksOrder_;
  std::map<std::string, std::vector<MachineInstruction>> machineCode_;
  std::map<std::string, LiveRangesGenerator> liveRanges_;
  std::map<std::string, std::unique_ptr<RegAlloc>> regAllocators_;
  std::map<std::string, std::map<std::string, uint16_t>> variableAddresses_;
  std::map<std::string, std::map<std::string, uint16_t>> labelValues_;
};
}  // namespace machine_code

#endif  // MACHINE_CODE_MACHINE_CODE_GENERATOR_HPP