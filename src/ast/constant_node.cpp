#include "constant_node.hpp"

namespace ast {
virtual void ConstantNode::accept(AstVisitor& visitor) const override {}

[[nodiscard]] std::unique_ptr<AstNode> ConstantNode::clone() const override {}

void ConstantNode::print(std::ostream& out, int tab) const override {}
}  // namespace ast
