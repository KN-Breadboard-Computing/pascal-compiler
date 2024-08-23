#include "array_type_node.hpp"

namespace ast {
std::string ArrayTypeNode::flat() const {
  return "array@@" + range_->flat() + "@" + elementType_->flat() + "@@";
}

void ArrayTypeNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

[[nodiscard]] std::unique_ptr<AstNode> ArrayTypeNode::clone() const {
  SimpleTypeNode* newRange = dynamic_cast<SimpleTypeNode*>(range_->clone().release());
  TypeNode* newElementType = dynamic_cast<TypeNode*>(elementType_->clone().release());

  return std::make_unique<ArrayTypeNode>(newRange, newElementType);
}

void ArrayTypeNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ArrayTypeNode:\n";
  out << std::string(tab + 2, ' ') << "Range:\n";
  range_->print(out, tab + 4);
  out << std::string(tab + 2, ' ') << "Element type:\n";
  elementType_->print(out, tab + 4);
}
}  // namespace ast
