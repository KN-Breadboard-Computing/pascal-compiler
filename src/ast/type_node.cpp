#include "type_node.hpp"

namespace ast {
virtual void TypeNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> TypeNode::clone() const override {
  return std::make_unique<TypeNode>(typeType_);
}

virtual void TypeNode::print(std::ostream& out, int tab) const override {
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