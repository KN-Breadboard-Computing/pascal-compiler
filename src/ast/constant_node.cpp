#include "constant_node.hpp"

namespace ast {
void ConstantNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> ConstantNode::clone() const {

  if (constantType_ == ConstantType::INTEGER) {
    const IntegerConstantNode* constInt = dynamic_cast<const IntegerConstantNode*>(this);
    return std::make_unique<IntegerConstantNode>(constInt->getValue());
  }

  if (constantType_ == ConstantType::CHAR) {
    const CharConstantNode* constChar = dynamic_cast<const CharConstantNode*>(this);
    return std::make_unique<CharConstantNode>(constChar->getValue());
  }

  if (constantType_ == ConstantType::BOOLEAN) {
    const BooleanConstantNode* constBool = dynamic_cast<const BooleanConstantNode*>(this);
    return std::make_unique<BooleanConstantNode>(constBool->getValue());
  }

  if (constantType_ == ConstantType::STRING) {
    const StringConstantNode* constString = dynamic_cast<const StringConstantNode*>(this);
    return std::make_unique<StringConstantNode>(constString->getValue());
  }

  return nullptr;
}

void ConstantNode::print(std::ostream& out, int tab) const {
  if (constantType_ == ConstantType::INTEGER) {
    const IntegerConstantNode* constInt = dynamic_cast<const IntegerConstantNode*>(this);
    out << std::string(tab, ' ') << "ConstantInteger<" << constInt->getValue() << ">\n";
  }
  else if (constantType_ == ConstantType::CHAR) {
    const CharConstantNode* constChar = dynamic_cast<const CharConstantNode*>(this);
    out << std::string(tab, ' ') << "ConstantChar<" << constChar->getValue() << ">\n";
  }
  else if (constantType_ == ConstantType::BOOLEAN) {
    const BooleanConstantNode* constBool = dynamic_cast<const BooleanConstantNode*>(this);
    out << std::string(tab, ' ') << "ConstantBoolean<" << constBool->getValue() << ">\n";
  }
  else if (constantType_ == ConstantType::STRING) {
    const StringConstantNode* constString = dynamic_cast<const StringConstantNode*>(this);
    out << std::string(tab, ' ') << "ConstantString<" << constString->getValue() << ">\n";
  }
  else {
    out << std::string(tab, ' ') << "Constant<unknown>\n";
  }
}
}  // namespace ast
