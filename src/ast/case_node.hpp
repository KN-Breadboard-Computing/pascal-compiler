#ifndef AST_CASE_NODE_HPP
#define AST_CASE_NODE_HPP

#include <memory>
#include <vector>

#include "expression_node.hpp"
#include "statement_node.hpp"

namespace ast {
class CaseNode : public StatementNode {
 public:
  CaseNode() : StatementNode{} { type_ = Type::CASE; }
  CaseNode(ExpressionNode* expression, std::vector<std::pair<AstNode*, StatementNode*>*>* caseStatements)
      : StatementNode{}, expression_{expression}, statements_{std::move(caseStatements)} {}

  CaseNode(const CaseNode&) = delete;
  CaseNode(CaseNode&&) = default;

  CaseNode& operator=(const CaseNode&) = delete;
  CaseNode& operator=(CaseNode&&) = default;

  ~CaseNode() override = default;

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    ExpressionNode* newExpression = dynamic_cast<ExpressionNode*>(expression_->clone().release());
    std::vector<std::pair<AstNode*, StatementNode*>*>* newStatements =
        new std::vector<std::pair<AstNode*, StatementNode*>*>{};
    for (auto& statement : *statements_) {
      newStatements->push_back(new std::pair<AstNode*, StatementNode*>{
          statement->first->clone().release(), dynamic_cast<StatementNode*>(statement->second->clone().release())});
    }

    return std::make_unique<CaseNode>(newExpression, newStatements);
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(2 * tab, ' ') << "CaseNode:" << std::endl;
    out << std::string(2 * (tab + 1), ' ') << "expression: ";
    expression_->print(out, tab + 1);
    out << std::string(2 * (tab + 1), ' ') << "statements: " << std::endl;
    for (auto& statement : *statements_) {
      out << std::string(2 * (tab + 2), ' ') << "Expression: ";
      statement->first->print(out, tab + 2);
      out << std::string(2 * (tab + 2), ' ') << "Statement: ";
      statement->second->print(out, tab + 2);
    }
  }

  [[nodiscard]] const ExpressionNode* getExpression() const { return expression_.get(); }
  [[nodiscard]] const std::vector<std::pair<AstNode*, StatementNode*>*>* getStatements() const { return statements_.get(); }

 private:
  std::unique_ptr<ExpressionNode> expression_;
  std::unique_ptr<std::vector<std::pair<AstNode*, StatementNode*>*>> statements_;
};
}  // namespace ast

#endif  // AST_CASE_NODE_HPP
