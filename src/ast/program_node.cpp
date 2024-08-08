#include "program_node.hpp"

namespace ast {
void ProgramNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> ProgramNode::clone() const {
  auto clone = std::make_unique<ProgramNode>();
  clone->setName(name_);
  clone->setRoutine(std::unique_ptr<RoutineNode>(dynamic_cast<RoutineNode*>(routine_->clone().release())));
  return clone;
}

void ProgramNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ProgramNode " << name_ << ":\n";
  routine_->print(out, tab + 2);
}
}  // namespace ast
