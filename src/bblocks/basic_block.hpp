#ifndef BBLOCKS_BASIC_BLOCK_HPP
#define BBLOCKS_BASIC_BLOCK_HPP

#include <memory>
#include <ostream>
#include <vector>

#include "instructions/bb_binary_operation.hpp"
#include "instructions/bb_halt.hpp"
#include "instructions/bb_instruction.hpp"
#include "instructions/bb_move.hpp"
#include "instructions/bb_pop.hpp"
#include "instructions/bb_push.hpp"
#include "instructions/bb_unary_operation.hpp"

namespace bblocks {
class BasicBlock {
 public:
  BasicBlock() = default;
  virtual ~BasicBlock() = default;

  [[nodiscard]] const std::vector<std::unique_ptr<BBInstruction>>& getInstructions() const { return instructions_; }

  friend std::ostream& operator<<(std::ostream& out, const BasicBlock& basicBlock) {
    for (const auto& instruction : basicBlock.instructions_) {
      out << *instruction;
    }
    return out;
  }

 private:
  std::vector<std::unique_ptr<BBInstruction>> instructions_;
};
}  // namespace bblocks

#endif  // BBLOCKS_BASIC_BLOCK_HPP
