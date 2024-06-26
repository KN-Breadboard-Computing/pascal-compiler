#ifndef AST_REPEAT_NODE_HPP
#define AST_REPEAT_NODE_HPP

#include <memory>
#include <vector>

#include "expression_node.hpp"
#include "statement_node.hpp"

namespace ast {
class RepeatNode : public StatementNode {
 public:
  RepeatNode() : StatementNode{} { type_ = Type::REPEAT; }
  RepeatNode(ExpressionNode *condition, std::vector<ast::StatementNode *> *statements)
	  : StatementNode{}, condition_{condition}, statements_{statements} {}

  RepeatNode(const RepeatNode &) = delete;
  RepeatNode(RepeatNode &&) = default;

  RepeatNode &operator=(const RepeatNode &) = delete;
  RepeatNode &operator=(RepeatNode &&) = default;

  ~RepeatNode() override = default;

  const std::unique_ptr<ExpressionNode> &getCondition() const { return condition_; }
  const std::unique_ptr<std::vector<ast::StatementNode *>> &getStatements() const { return statements_; }

  void setCondition(std::unique_ptr<ExpressionNode> condition) { condition_ = std::move(condition); }
  void setStatements(std::unique_ptr<std::vector<ast::StatementNode *>> statements) {
	statements_ = std::move(statements);
  }

 private:
  std::unique_ptr<ExpressionNode> condition_;
  std::unique_ptr<std::vector<ast::StatementNode *>> statements_;
};
} // namespace ast

#endif // AST_REPEAT_NODE_HPP
