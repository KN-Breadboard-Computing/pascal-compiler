#ifndef AST_WHILE_NODE_HPP
#define AST_WHILE_NODE_HPP

#include <memory>

#include "expression_node.hpp"
#include "statement_node.hpp"

namespace ast {
class WhileNode : public StatementNode {
 public:
  WhileNode() : StatementNode{Category::WHILE} {}
  WhileNode(ExpressionNode* condition, StatementNode* statements) : StatementNode{Category::WHILE}, condition_{condition}, statements_{statements} {}

  WhileNode(const WhileNode&) = delete;
  WhileNode(WhileNode&&) = default;

  WhileNode& operator=(const WhileNode&) = delete;
  WhileNode& operator=(WhileNode&&) = default;

  ~WhileNode() override = default;

  const std::unique_ptr<ExpressionNode>& getCondition() const { return condition_; }
  const std::unique_ptr<StatementNode>& getStatements() const { return statements_; }

  void setCondition(std::unique_ptr<ExpressionNode> condition) { condition_ = std::move(condition); }
  void setStatements(std::unique_ptr<StatementNode> statements) { statements_ = std::move(statements); }

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  virtual void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<ExpressionNode> condition_;
  std::unique_ptr<StatementNode> statements_;
};
}  // namespace ast

#endif  // AST_WHILE_NODE_HPP
