#ifndef BBLOCKS_BASIC_BLOCK_HPP
#define BBLOCKS_BASIC_BLOCK_HPP

#include <memory>
#include <vector>

#include "instructions/BBBinaryOperation.hpp"
#include "instructions/BBHalt.hpp"
#include "instructions/BBInstruction.hpp"
#include "instructions/BBMove.hpp"
#include "instructions/BBPop.hpp"
#include "instructions/BBPush.hpp"
#include "instructions/BBUnaryOperation.hpp"

namespace bblocks {
class BasicBlock {
 public:
  BasicBlock() = default;
  virtual ~BasicBlock() = default;

  [[nodiscard]] const std::vector<std::unique_ptr<BBInstruction>>& getInstructions() const { return instructions_; }

 private:
  std::vector<std::unique_ptr<BBInstruction>> instructions_;
};
}  // namespace bblocks

#endif  // BBLOCKS_BASIC_BLOCK_HPP
