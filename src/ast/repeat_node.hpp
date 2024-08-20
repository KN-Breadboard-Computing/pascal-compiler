#ifndef AST_REPEAT_NODE_HPP
#define AST_REPEAT_NODE_HPP

#include <memory>
#include <vector>

#include "expression_node.hpp"
#include "statement_node.hpp"

namespace ast {
class RepeatNode : public StatementNode {
 public:
  RepeatNode() : StatementNode{Category::REPEAT} {}
  RepeatNode(ExpressionNode* condition, std::vector<StatementNode*>* statements)
      : StatementNode{Category::REPEAT}, condition_{condition}, statements_{statements} {}

  RepeatNode(const RepeatNode&) = delete;
  RepeatNode(RepeatNode&&) = default;

  RepeatNode& operator=(const RepeatNode&) = delete;
  RepeatNode& operator=(RepeatNode&&) = default;

  ~RepeatNode() override = default;

  const std::unique_ptr<ExpressionNode>& getCondition() const { return condition_; }
  const std::unique_ptr<std::vector<StatementNode*>>& getStatements() const { return statements_; }

  void setCondition(std::unique_ptr<ExpressionNode> condition) { condition_ = std::move(condition); }
  void setStatements(std::unique_ptr<std::vector<StatementNode*>> statements) { statements_ = std::move(statements); }

  virtual void accept(AstVisitor* visitor) const override;
  virtual std::unique_ptr<AstNode> clone() const override;
  virtual void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<ExpressionNode> condition_;
  std::unique_ptr<std::vector<StatementNode*>> statements_;
};
}  // namespace ast

#endif  // AST_REPEAT_NODE_HPP
