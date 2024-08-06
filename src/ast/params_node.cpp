#include "params_node.hpp"

namespace ast {
virtual void ParamsNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> ParamsNode::clone() const override {
  auto clone = std::make_unique<ParamsNode>();

  std::vector<ParamsGroupNode*> params;
  for (const auto& param : *params_) {
    params.push_back(dynamic_cast<ParamsGroupNode*>(param->clone().release()));
  }
  clone->setParams(std::make_unique<std::vector<ParamsGroupNode*>>(std::move(params)));

  return clone;
}

virtual void ParamsNode::print(std::ostream& out, int tab) const override {
  out << std::string(tab, ' ') << "ParamsNode:\n";
  for (const auto& param : *params_) {
    param->print(out, tab + 2);
  }
}
}  // namespace ast
