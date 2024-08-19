#include "params_node.hpp"

namespace ast {
void ParamsNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

[[nodiscard]] std::unique_ptr<AstNode> ParamsNode::clone() const {
  auto clone = std::make_unique<ParamsNode>();

  std::vector<ParamsGroupNode*> params;
  for (const auto& param : *params_) {
    params.push_back(dynamic_cast<ParamsGroupNode*>(param->clone().release()));
  }
  clone->setParams(std::make_unique<std::vector<ParamsGroupNode*>>(std::move(params)));

  return clone;
}

void ParamsNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ParamsNode:\n";
  for (const auto& param : *params_) {
    param->print(out, tab + 2);
  }
}
}  // namespace ast
