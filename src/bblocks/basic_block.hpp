#ifndef BBLOCKS_BASIC_BLOCK_HPP
#define BBLOCKS_BASIC_BLOCK_HPP

#include <memory>
#include <ostream>
#include <vector>

#include "instructions/bb_binary_operation.hpp"
#include "instructions/bb_branch.hpp"
#include "instructions/bb_call.hpp"
#include "instructions/bb_halt.hpp"
#include "instructions/bb_instruction.hpp"
#include "instructions/bb_move.hpp"
#include "instructions/bb_ret.hpp"
#include "instructions/bb_unary_operation.hpp"

namespace bblocks {
class BasicBlock {
 public:
  BasicBlock() = default;

  BasicBlock(const BasicBlock& bblock) {
    for (const auto& instr : bblock.instructions_) {
      instructions_.emplace_back(instr->clone());
    }
  }

  BasicBlock(BasicBlock&&) = default;

  BasicBlock& operator=(const BasicBlock& bblock) {
    if (this != &bblock) {
      instructions_.clear();
      for (const auto& instr : bblock.instructions_) {
        instructions_.emplace_back(instr->clone());
      }
    }
    return *this;
  }

  BasicBlock& operator=(BasicBlock&&) = default;

  virtual ~BasicBlock() = default;

  void addInstruction(std::unique_ptr<BBInstruction> instruction) { instructions_.emplace_back(std::move(instruction)); }
  void addInstructionToStart(std::unique_ptr<BBInstruction> instruction) {
    instructions_.insert(instructions_.begin(), std::move(instruction));
  }
  [[nodiscard]] const std::vector<std::unique_ptr<BBInstruction>>& getInstructions() const { return instructions_; }
  [[nodiscard]] std::vector<std::unique_ptr<BBInstruction>>& instructions() { return instructions_; }
  [[nodiscard]] bool empty() const { return instructions_.empty(); }
  [[nodiscard]] std::size_t size() const { return instructions_.size(); }

  friend std::ostream& operator<<(std::ostream& out, const BasicBlock& basicBlock) {
    for (const auto& instruction : basicBlock.instructions_) {
      instruction->print(out, 2);
    }
    return out;
  }

 private:
  std::vector<std::unique_ptr<BBInstruction>> instructions_;
};
}  // namespace bblocks

#endif  // BBLOCKS_BASIC_BLOCK_HPP
