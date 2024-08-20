#ifndef AST_CASE_NODE_HPP
#define AST_CASE_NODE_HPP

#include <memory>
#include <vector>

#include "expression_node.hpp"
#include "statement_node.hpp"

namespace ast {
class CaseNode : public StatementNode {
 public:
  CaseNode() : StatementNode{Category::CASE} {}
  CaseNode(ExpressionNode* expression, std::vector<std::pair<ExpressionNode*, StatementNode*>*>* caseStatements)
      : StatementNode{Category::CASE}, expression_{expression}, statements_{caseStatements} {}

  CaseNode(const CaseNode&) = delete;
  CaseNode(CaseNode&&) = default;

  CaseNode& operator=(const CaseNode&) = delete;
  CaseNode& operator=(CaseNode&&) = default;

  ~CaseNode() override = default;

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  virtual void print(std::ostream& out, int tab) const override;

  [[nodiscard]] const ExpressionNode* getExpression() const { return expression_.get(); }
  [[nodiscard]] const std::vector<std::pair<ExpressionNode*, StatementNode*>*>* getStatements() const {
    return statements_.get();
  }

 private:
  std::unique_ptr<ExpressionNode> expression_;
  std::unique_ptr<std::vector<std::pair<ExpressionNode*, StatementNode*>*>> statements_;
};
}  // namespace ast

#endif  // AST_CASE_NODE_HPP
