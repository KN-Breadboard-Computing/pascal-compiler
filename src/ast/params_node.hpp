#ifndef AST_PARAMS_NODE_HPP
#define AST_PARAMS_NODE_HPP

#include <memory>
#include <utility>
#include <vector>

#include "ast_node.hpp"
#include "params_group_node.hpp"

namespace ast {
class ParamsNode : public AstNode {
 public:
  ParamsNode() : AstNode(Type::PARAMS) {}
  explicit ParamsNode(std::vector<ParamsGroupNode*>* params) : AstNode{Type::PARAMS}, params_{params} {}

  ParamsNode(const ParamsNode&) = delete;
  ParamsNode(ParamsNode&&) = default;

  ParamsNode& operator=(const ParamsNode&) = delete;
  ParamsNode& operator=(ParamsNode&&) = default;

  ~ParamsNode() override = default;

  [[nodiscard]] const std::unique_ptr<std::vector<ParamsGroupNode*>>& getParams() const { return params_; }

  void setParams(std::unique_ptr<std::vector<ParamsGroupNode*>> params) { params_ = std::move(params); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    auto clone = std::make_unique<ParamsNode>();

    std::vector<ParamsGroupNode*> params;
    for (const auto& param : *params_) {
      params.push_back(dynamic_cast<ParamsGroupNode*>(param->clone().release()));
    }
    clone->setParams(std::make_unique<std::vector<ParamsGroupNode*>>(std::move(params)));

    return clone;
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "ParamsNode:\n";
    for (const auto& param : *params_) {
      param->print(out, tab + 2);
    }
  }

 private:
  std::unique_ptr<std::vector<ParamsGroupNode*>> params_;
};

}  // namespace ast

#endif  // AST_PARAMS_NODE_HPP
