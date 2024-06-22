#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <memory>
#include <vector>

namespace ast {
class AstNode {
 public:
  AstNode() = default;

  AstNode(const AstNode &) = default;
  AstNode(AstNode &&) = default;

  AstNode &operator=(const AstNode &) = default;
  AstNode &operator=(AstNode &&) = default;

  virtual ~AstNode() = default;
 private:
  std::vector<std::shared_ptr<AstNode>> children_;
};
} // namespace ast

#endif // AST_NODE_HPP
