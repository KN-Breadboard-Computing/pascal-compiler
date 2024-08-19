#include "type_node.hpp"

namespace ast {
void TypeNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

[[nodiscard]] std::unique_ptr<AstNode> TypeNode::clone() const {
  return std::make_unique<TypeNode>(typeType_);
}

void TypeNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "TypeNode ";
  switch (typeType_) {
    case SIMPLE:
      out << "SIMPLE";
      break;
    case ARRAY:
      out << "ARRAY";
      break;
    case RECORD:
      out << "RECORD";
      break;
    default:
      out << "UNSPECIFIED";
      break;
  }
  out << '\n';
}
}  // namespace ast