#ifndef AST_CONTINUE_NODE_HPP
#define AST_CONTINUE_NODE_HPP

#include <memory>

#include "statement_node.hpp"

namespace ast {
class ContinueNode : public StatementNode {
 public:
  ContinueNode() : StatementNode{Category::CONTINUE} {}
  ContinueNode(const ContinueNode &) = delete;
  ContinueNode(ContinueNode &&) = default;

  ContinueNode &operator=(const ContinueNode &) = delete;
  ContinueNode &operator=(ContinueNode &&) = default;

  ~ContinueNode() override = default;

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream &out, int tab) const override;
};
} // namespace ast

#endif // AST_CONTINUE_NODE_HPP
