#ifndef BBLOCKS_BB_CFG_GENERATOR_HPP
#define BBLOCKS_BB_CFG_GENERATOR_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../ast/ast_visitor.hpp"
#include "control_flow_graph.hpp"

namespace bblocks {
class BbCfgGenerator : public ast::AstVisitor {
 public:
  BbCfgGenerator() = default;

  BbCfgGenerator(const BbCfgGenerator&) = delete;
  BbCfgGenerator(BbCfgGenerator&&) = default;

  BbCfgGenerator& operator=(const BbCfgGenerator&) = delete;
  BbCfgGenerator& operator=(BbCfgGenerator&&) = default;

  virtual ~BbCfgGenerator() = default;

  virtual void visit(const ast::ArgumentsListNode& node) override;
  virtual void visit(const ast::ArrayTypeNode& node) override;
  virtual void visit(const ast::AssignToArrayNode& node) override;
  virtual void visit(const ast::AssignToRecordFieldNode& node) override;
  virtual void visit(const ast::AssignToVariableNode& node) override;
  virtual void visit(const ast::AstNode& node) override;
  virtual void visit(const ast::BuiltinCallNode& node) override;
  virtual void visit(const ast::CallNode& node) override;
  virtual void visit(const ast::UserDefineCallNode& node) override;
  virtual void visit(const ast::CaseNode& node) override;
  virtual void visit(const ast::CompoundStatementNode& node) override;
  virtual void visit(const ast::ConstantNode& node) override;
  virtual void visit(const ast::ExpressionNode& node) override;
  virtual void visit(const ast::SpecialExpressionNode& node) override;
  virtual void visit(const ast::BreakNode& node) override;
  virtual void visit(const ast::ContinueNode& node) override;
  virtual void visit(const ast::ForNode& node) override;
  virtual void visit(const ast::GotoNode& node) override;
  virtual void visit(const ast::IdentifierNode& node) override;
  virtual void visit(const ast::IfNode& node) override;
  virtual void visit(const ast::ParamsGroupNode& node) override;
  virtual void visit(const ast::ParamsNode& node) override;
  virtual void visit(const ast::ProgramNode& node) override;
  virtual void visit(const ast::RecordTypeNode& node) override;
  virtual void visit(const ast::RepeatNode& node) override;
  virtual void visit(const ast::RoutineBodyNode& node) override;
  virtual void visit(const ast::RoutineDeclarationNode& node) override;
  virtual void visit(const ast::RoutineHeadNode& node) override;
  virtual void visit(const ast::RoutineNode& node) override;
  virtual void visit(const ast::ConstRangeTypeNode& node) override;
  virtual void visit(const ast::EnumerationTypeNode& node) override;
  virtual void visit(const ast::RenameTypeNode& node) override;
  virtual void visit(const ast::SimpleTypeNode& node) override;
  virtual void visit(const ast::VarRangeTypeNode& node) override;
  virtual void visit(const ast::StatementNode& node) override;
  virtual void visit(const ast::TypeNode& node) override;
  virtual void visit(const ast::WhileNode& node) override;

  void generate(const std::unique_ptr<ast::ProgramNode>& program) const;

// private:
//  std::map<std::string, ControlFlowGraph> controlFlowGraphs_;
//  ControlFlowGraph currentControlFlowGraph_;
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_CFG_GENERATOR_HPP
