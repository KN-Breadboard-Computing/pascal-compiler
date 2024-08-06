#ifndef BBLOCKS_BB_CFG_GENERATOR_HPP
#define BBLOCKS_BB_CFG_GENERATOR_HPP

#include <memory>
#include <vector>

#include "../ast/ast_visitor.hpp"
#include "control_flow_graph.hpp"

namespace bblocks {
class BbCfgGenerator : public ast::AstVisitor {
 public:
  BbCfgGenerator() = default;
  virtual ~BbCfgGenerator() = default;

  virtual void visit(ast::ArgumentsListNode& node) override;
  virtual void visit(ast::ArrayTypeNode& node) override;
  virtual void visit(ast::AssignNode& node) override;
  virtual void visit(ast::AssignToArrayNode& node) override;
  virtual void visit(ast::AssignToRecordFieldNode& node) override;
  virtual void visit(ast::AssignToVariableNode& node) override;
  virtual void visit(ast::AstNode& node) override;
  virtual void visit(ast::BuiltinCallNode& node) override;
  virtual void visit(ast::CallNode& node) override;
  virtual void visit(ast::UserDefineCallNode& node) override;
  virtual void visit(ast::CaseNode& node) override;
  virtual void visit(ast::CompoundStatementNode& node) override;
  virtual void visit(ast::ConstantNode& node) override;
  //  virtual void visit(ast::ConstantNodeSpec& node) override;
  //    virtual void visit(ast::IntegerConstantNode& node) override;
  //    virtual void visit(ast::CharConstantNode& node) override;
  //    virtual void visit(ast::BooleanConstantNode& node) override;
  //    virtual void visit(ast::StringConstantNode& node) override;
  virtual void visit(ast::ExpressionNode& node) override;
  virtual void visit(ast::SpecialExpressionNode& node) override;
  virtual void visit(ast::BreakNode& node) override;
  virtual void visit(ast::ContinueNode& node) override;
  virtual void visit(ast::ForNode& node) override;
  virtual void visit(ast::GotoNode& node) override;
  virtual void visit(ast::IdentifierNode& node) override;
  virtual void visit(ast::IfNode& node) override;
  virtual void visit(ast::ParamsGroupNode& node) override;
  virtual void visit(ast::ParamsNode& node) override;
  virtual void visit(ast::ProgramNode& node) override;
  virtual void visit(ast::RecordTypeNode& node) override;
  virtual void visit(ast::RepeatNode& node) override;
  virtual void visit(ast::RoutineBodyNode& node) override;
  virtual void visit(ast::RoutineDeclarationNode& node) override;
  virtual void visit(ast::RoutineHeadNode& node) override;
  virtual void visit(ast::RoutineNode& node) override;
  virtual void visit(ast::ConstRangeTypeNode& node) override;
  virtual void visit(ast::EnumerationTypeNode& node) override;
  virtual void visit(ast::RenameTypeNode& node) override;
  virtual void visit(ast::SimpleTypeNode& node) override;
  virtual void visit(ast::VarRangeTypeNode& node) override;
  virtual void visit(ast::StatementNode& node) override;
  virtual void visit(ast::TypeNode& node) override;
  virtual void visit(ast::WhileNode& node) override;

  [[nodiscard]] ControlFlowGraph generate(const std::unique_ptr<ast::ProgramNode>& program) const {
    ControlFlowGraph controlFlowGraph;
    return controlFlowGraph;
  }
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_CFG_GENERATOR_HPP
