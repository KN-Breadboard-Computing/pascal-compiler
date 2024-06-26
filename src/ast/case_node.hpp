#ifndef AST_CASE_NODE_HPP
#define AST_CASE_NODE_HPP

#include "ast_node.hpp"

namespace ast {
class CaseNode : public AstNode {
 public:
  CaseNode() : AstNode(Type::CASE) {}

  CaseNode(const CaseNode &) = delete;
  CaseNode(CaseNode &&) = default;

  CaseNode &operator=(const CaseNode &) = delete;
  CaseNode &operator=(CaseNode &&) = default;

  ~CaseNode() override = default;
};
} // namespace ast

#endif // AST_CASE_NODE_HPP
