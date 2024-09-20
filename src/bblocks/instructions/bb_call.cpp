#include "bb_call.hpp"

namespace bblocks {
void BBCall::visitDefVariables(std::function<void(const VariableType&)> /*visitor*/) const {}

void BBCall::visitUseVariables(std::function<void(const VariableType&)> /*visitor*/) const {}

std::unique_ptr<BBInstruction> BBCall::replaceVariable(const VariableType& /*from*/, const VariableType& /*to*/) {
  return clone();
}

std::unique_ptr<BBInstruction> BBCall::replaceVariable(const VariableType& /*from*/, const NumericType& /*to*/) {
  return clone();
}

}  // namespace bblocks