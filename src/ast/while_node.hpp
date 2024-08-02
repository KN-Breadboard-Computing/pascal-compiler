#ifndef AST_WHILE_NODE_HPP
#define AST_WHILE_NODE_HPP

#include <memory>

#include "expression_node.hpp"
#include "statement_node.hpp"

namespace ast {
class WhileNode : public StatementNode {
 public:
  WhileNode() : StatementNode{} { type_ = Type::WHILE; }
  WhileNode(ExpressionNode* condition, StatementNode* statements) : condition_{condition}, statements_{statements} {
    type_ = Type::WHILE;
  }

  WhileNode(const WhileNode&) = delete;
  WhileNode(WhileNode&&) = default;

  WhileNode& operator=(const WhileNode&) = delete;
  WhileNode& operator=(WhileNode&&) = default;

  ~WhileNode() override = default;

  const std::unique_ptr<ExpressionNode>& getCondition() const { return condition_; }
  const std::unique_ptr<StatementNode>& getStatements() const { return statements_; }

  void setCondition(std::unique_ptr<ExpressionNode> condition) { condition_ = std::move(condition); }
  void setStatements(std::unique_ptr<StatementNode> statements) { statements_ = std::move(statements); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    auto clone = std::make_unique<WhileNode>();
    clone->setCondition(std::unique_ptr<ExpressionNode>(dynamic_cast<ExpressionNode*>(condition_->clone().release())));
    clone->setStatements(std::unique_ptr<StatementNode>(dynamic_cast<StatementNode*>(statements_->clone().release())));

    return clone;
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "WhileNode:\n";
    condition_->print(out, tab + 2);
    statements_->print(out, tab + 2);
  }

 private:
  std::unique_ptr<ExpressionNode> condition_;
  std::unique_ptr<StatementNode> statements_;
};
}  // namespace ast

#endif  // AST_WHILE_NODE_HPP
