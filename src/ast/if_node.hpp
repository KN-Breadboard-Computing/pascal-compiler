#ifndef AST_IF_NODE_HPP
#define AST_IF_NODE_HPP

#include <memory>

#include "expression_node.hpp"
#include "statement_node.hpp"

namespace ast {
class IfNode : public StatementNode {
 public:
  IfNode() : StatementNode{} { type_ = Type::IF; }
  IfNode(ExpressionNode *condition, StatementNode *thenStatement)
	  : StatementNode{}, condition_{condition}, thenStatement_{thenStatement}, elseStatement_{nullptr} {}
  IfNode(ExpressionNode *condition, StatementNode *thenStatement, StatementNode *elseStatement)
	  : StatementNode{}, condition_{condition}, thenStatement_{thenStatement}, elseStatement_{elseStatement} {}
  IfNode(ExpressionNode *condition, StatementNode *thenStatement, IfNode *elsePart)
	  : StatementNode{},
		condition_{condition},
		thenStatement_{thenStatement},
		elseStatement_{std::move(elsePart->elseStatement_)} {}

  IfNode(const IfNode &) = delete;
  IfNode(IfNode &&) = default;

  IfNode &operator=(const IfNode &) = delete;
  IfNode &operator=(IfNode &&) = default;

  ~IfNode() override = default;

  [[nodiscard]] const std::unique_ptr<ExpressionNode> &getCondition() const { return condition_; }
  [[nodiscard]] const std::unique_ptr<StatementNode> &getThenStatement() const { return thenStatement_; }
  [[nodiscard]] const std::unique_ptr<StatementNode> &getElseStatement() const { return elseStatement_; }

  void setCondition(std::unique_ptr<ExpressionNode> condition) { condition_ = std::move(condition); }
  void setThenStatement(std::unique_ptr<StatementNode> thenStatement) { thenStatement_ = std::move(thenStatement); }
  void setElseStatement(std::unique_ptr<StatementNode> elseStatement) { elseStatement_ = std::move(elseStatement); }

 private:
  std::unique_ptr<ExpressionNode> condition_;
  std::unique_ptr<StatementNode> thenStatement_;
  std::unique_ptr<StatementNode> elseStatement_;
};
} // namespace ast

#endif // AST_IF_NODE_HPP
