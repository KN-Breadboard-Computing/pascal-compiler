#ifndef AST_PROGRAM_NODE_HPP
#define AST_PROGRAM_NODE_HPP

#include <memory>
#include <string>

#include "ast_node.hpp"
#include "routine_decl_head_node.hpp"

namespace ast {
class ProgramNode : public AstNode {
 public:
  ProgramNode() : AstNode{Type::PROGRAM} {}
  ProgramNode(std::string name, RoutineNode* routine) : AstNode{Type::PROGRAM}, name_{std::move(name)}, routine_{routine} {}

  ProgramNode(const ProgramNode&) = delete;
  ProgramNode(ProgramNode&&) = default;

  ProgramNode& operator=(const ProgramNode&) = delete;
  ProgramNode& operator=(ProgramNode&&) = default;

  ~ProgramNode() override = default;

  [[nodiscard]] const std::string& getName() const { return name_; }
  [[nodiscard]] const std::unique_ptr<RoutineNode>& getRoutine() const { return routine_; }

  void setName(std::string name) { name_ = std::move(name); }
  void setRoutine(std::unique_ptr<RoutineNode> routine) { routine_ = std::move(routine); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    auto clone = std::make_unique<ProgramNode>();
    clone->setName(name_);
    clone->setRoutine(std::unique_ptr<RoutineNode>(dynamic_cast<RoutineNode*>(routine_->clone().release())));
    return clone;
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "ProgramNode:\n";
    out << std::string(tab + 2, ' ') << "Name: " << name_ << '\n';
    routine_->print(out, tab + 2);
  }

 private:
  std::string name_;
  std::unique_ptr<RoutineNode> routine_;
};
}  // namespace ast

#endif  // AST_PROGRAM_NODE_HPP
