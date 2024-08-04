#ifndef AST_GOTO_NODE_HPP
#define AST_GOTO_NODE_HPP

#include "statement_node.hpp"

namespace ast {
class GotoNode : public StatementNode {
 public:
  GotoNode() : StatementNode{}, line_{0} { type_ = Type::GO_TO; }
  explicit GotoNode(uint64_t line) : StatementNode{}, line_{line} { type_ = Type::GO_TO; }

  GotoNode(const GotoNode&) = delete;
  GotoNode(GotoNode&&) = default;

  GotoNode& operator=(const GotoNode&) = delete;
  GotoNode& operator=(GotoNode&&) = default;

  ~GotoNode() override = default;

  [[nodiscard]] uint64_t getLine() const { return line_; }

  void setLine(uint64_t line) { line_ = line; }

  [[nodiscard]] std::unique_ptr<AstNode> clone() const override { return std::make_unique<GotoNode>(line_); }

  void print(std::ostream& out, int tab) const override {
    if (getLabel().has_value()) {
      out << std::string(tab, ' ') << "GotoNode with label: " << getLabel().value() << '\n';
    }
    else {
      out << std::string(tab, ' ') << "GotoNode\n";
    }

    out << std::string(tab, ' ') << "  Line: " << line_ << '\n';
  }

 private:
  uint64_t line_;
};
}  // namespace ast

#endif  // AST_GOTO_NODE_HPP
