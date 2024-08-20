#ifndef AST_BREAK_NODE_HPP
#define AST_BREAK_NODE_HPP

#include <memory>

#include "statement_node.hpp"

namespace ast {
class BreakNode : public StatementNode {
 public:
  BreakNode() : StatementNode{Category::BREAK} {}
  BreakNode(const BreakNode&) = delete;
  BreakNode(BreakNode&&) = default;

  BreakNode& operator=(const BreakNode&) = delete;
  BreakNode& operator=(BreakNode&&) = default;

  ~BreakNode() override = default;

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;
};
}  // namespace ast

#endif  // AST_BREAK_NODE_HPP
