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
  RepeatNode(ExpressionNode* condition, std::vector<StatementNode*>* statements)
      : StatementNode{}, condition_{condition}, statements_{statements} {}

  RepeatNode(const RepeatNode&) = delete;
  RepeatNode(RepeatNode&&) = default;

  RepeatNode& operator=(const RepeatNode&) = delete;
  RepeatNode& operator=(RepeatNode&&) = default;

  ~RepeatNode() override = default;

  const std::unique_ptr<ExpressionNode>& getCondition() const { return condition_; }
  const std::unique_ptr<std::vector<StatementNode*>>& getStatements() const { return statements_; }

  void setCondition(std::unique_ptr<ExpressionNode> condition) { condition_ = std::move(condition); }
  void setStatements(std::unique_ptr<std::vector<StatementNode*>> statements) { statements_ = std::move(statements); }

  virtual std::unique_ptr<AstNode> clone() const override {
    auto clone = std::make_unique<RepeatNode>();

    clone->setCondition(std::unique_ptr<ExpressionNode>(dynamic_cast<ExpressionNode*>(condition_->clone().release())));
    std::vector<StatementNode*> statements;
    for (const auto& statement : *statements_) {
      statements.push_back(dynamic_cast<StatementNode*>(statement->clone().release()));
    }
    clone->setStatements(std::make_unique<std::vector<StatementNode*>>(std::move(statements)));

    return clone;
  }

  virtual void print(std::ostream& out, int tab) const override {
    if(getLabel().has_value()) {
      out << std::string(tab, ' ') << "RepeatNode with label: " << getLabel().value() << std::endl;
    } else {
      out << std::string(tab, ' ') << "RepeatNode:\n";
    }

    condition_->print(out, tab + 2);
    for (const auto& statement : *statements_) {
      statement->print(out, tab + 2);
    }
  }

 private:
  std::unique_ptr<ExpressionNode> condition_;
  std::unique_ptr<std::vector<StatementNode*>> statements_;
};
}  // namespace ast

#endif  // AST_REPEAT_NODE_HPP
