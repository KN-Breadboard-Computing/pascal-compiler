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
  explicit ParamsNode(std::vector<ParamsGroupNode *> *params)
	  : AstNode{Type::PARAMS}, params_{params} {}

  ParamsNode(const ParamsNode &) = delete;
  ParamsNode(ParamsNode &&) = default;

  ParamsNode &operator=(const ParamsNode &) = delete;
  ParamsNode &operator=(ParamsNode &&) = default;

  ~ParamsNode() override = default;

  [[nodiscard]] const std::unique_ptr<std::vector<ParamsGroupNode *>> &getParams() const { return params_; }

  void setParams(std::unique_ptr<std::vector<ParamsGroupNode *>> params) { params_ = std::move(params); }

 private:
  std::unique_ptr<std::vector<ParamsGroupNode *>> params_;
};

} // namespace ast

#endif // AST_PARAMS_NODE_HPP
