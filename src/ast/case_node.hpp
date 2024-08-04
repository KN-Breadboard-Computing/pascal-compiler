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
    std::vector<std::pair<AstNode*, StatementNode*>*>* newStatements = new std::vector<std::pair<AstNode*, StatementNode*>*>{};
    for (auto& statement : *statements_) {
      newStatements->push_back(new std::pair<AstNode*, StatementNode*>{
          statement->first->clone().release(), dynamic_cast<StatementNode*>(statement->second->clone().release())});
    }

    return std::make_unique<CaseNode>(newExpression, newStatements);
  }

  virtual void print(std::ostream& out, int tab) const override {
    if (getLabel().has_value()) {
      out << std::string(tab, ' ') << "CaseNode with label: " << getLabel().value() << std::endl;
    }
    else {
      out << std::string(tab, ' ') << "CaseNode:" << std::endl;
    }

    expression_->print(out, tab + 2);
    size_t index{0};
    for (auto& statement : *statements_) {
      out << std::string(tab + 2, ' ') << "Case " << index++ << ":\n";
      out << std::string(tab + 4, ' ') << "Expression:\n";
      if (statement->first != nullptr) {
        statement->first->print(out, tab + 6);
      }
      else {
        out << std::string(tab + 6, ' ') << "Otherwise\n";
      }
      out << std::string(tab + 4, ' ') << "Statement:\n";
      statement->second->print(out, tab + 6);
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
