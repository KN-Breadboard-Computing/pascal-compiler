#include "params_group_node.hpp"

namespace ast {
virtual void ParamsGroupNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> ParamsGroupNode::clone() const override {
  auto clone = std::make_unique<ParamsGroupNode>();
  clone->setPassType(passType_);
  clone->setParamsType(std::unique_ptr<SimpleTypeNode>(dynamic_cast<SimpleTypeNode*>(paramsType_->clone().release())));

  std::vector<IdentifierNode*> params;
  for (const auto& param : *params_) {
    params.push_back(dynamic_cast<IdentifierNode*>(param->clone().release()));
  }
  clone->setParams(std::make_unique<std::vector<IdentifierNode*>>(std::move(params)));

  return clone;
}

virtual void ParamsGroupNode::print(std::ostream& out, int tab) const override {
  out << std::string(tab, ' ') << "ParamsGroupNode:\n";
  out << std::string(tab + 2, ' ') << "PassType: ";
  switch (passType_) {
    case PassType::UNSPECIFIED:
      out << "UNSPECIFIED\n";
      break;
    case PassType::PASS_BY_VALUE:
      out << "PASS_BY_VALUE\n";
      break;
    case PassType::PASS_BY_REFERENCE:
      out << "PASS_BY_REFERENCE\n";
      break;
  }
  out << std::string(tab + 2, ' ') << "ParamsType:\n";
  paramsType_->print(out, tab + 4);
  out << std::string(tab + 2, ' ') << "Params:\n";
  for (const auto& param : *params_) {
    param->print(out, tab + 4);
  }
}
}  // namespace ast
