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
  CaseNode(ExpressionNode *expression, std::vector<std::pair<AstNode*, ast::StatementNode*>*>* caseStatements)
	  : StatementNode{}, expression_{expression}, statements_{std::move(caseStatements)} { }

  CaseNode(const CaseNode &) = delete;
  CaseNode(CaseNode &&) = default;

  CaseNode &operator=(const CaseNode &) = delete;
  CaseNode &operator=(CaseNode &&) = default;

  ~CaseNode() override = default;

 private:
  std::unique_ptr<ExpressionNode> expression_;
  std::unique_ptr<std::vector<std::pair<AstNode*, ast::StatementNode*>*>> statements_;
};
} // namespace ast

#endif // AST_CASE_NODE_HPP
