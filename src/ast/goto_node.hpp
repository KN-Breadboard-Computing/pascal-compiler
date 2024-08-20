#ifndef AST_GOTO_NODE_HPP
#define AST_GOTO_NODE_HPP

#include "statement_node.hpp"

namespace ast {
class GotoNode : public StatementNode {
 public:
  GotoNode() : StatementNode{Category::GOTO}, line_{0} {}
  explicit GotoNode(uint64_t line) : StatementNode{Category::GOTO}, line_{line} {}

  GotoNode(const GotoNode&) = delete;
  GotoNode(GotoNode&&) = default;

  GotoNode& operator=(const GotoNode&) = delete;
  GotoNode& operator=(GotoNode&&) = default;

  ~GotoNode() override = default;

  [[nodiscard]] uint64_t getLine() const { return line_; }

  void setLine(uint64_t line) { line_ = line; }

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  uint64_t line_;
};
}  // namespace ast

#endif  // AST_GOTO_NODE_HPP
