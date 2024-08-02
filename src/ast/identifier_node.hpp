#ifndef AST_IDENTIFIER_NODE_HPP
#define AST_IDENTIFIER_NODE_HPP

#include <string>

#include "ast_node.hpp"

namespace ast {
class IdentifierNode : public AstNode {
 public:
  IdentifierNode() : AstNode{Type::IDENTIFIER} {}
  explicit IdentifierNode(std::string name) : AstNode{Type::IDENTIFIER}, name_{std::move(name)} {}

  IdentifierNode(const IdentifierNode&) = delete;
  IdentifierNode(IdentifierNode&&) = default;

  IdentifierNode& operator=(const IdentifierNode&) = delete;
  IdentifierNode& operator=(IdentifierNode&&) = default;

  ~IdentifierNode() override = default;

  [[nodiscard]] const std::string& getName() const { return name_; }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override { return std::make_unique<IdentifierNode>(name_); }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "IdentifierNode: " << name_ << '\n';
  }

 private:
  std::string name_;
};
}  // namespace ast

#endif  // AST_IDENTIFIER_NODE_HPP
