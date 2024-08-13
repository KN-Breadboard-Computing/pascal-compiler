#include "bb_cfg_generator.hpp"

namespace bblocks {
void BbCfgGenerator::visit(const ast::ArgumentsListNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::ArrayTypeNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::AssignToArrayNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::AssignToRecordFieldNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::AssignToVariableNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::AstNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::BuiltinCallNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::CallNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::UserDefineCallNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::CaseNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::CompoundStatementNode& /*node*/) {
//  currentControlFlowGraph_ = ControlFlowGraph();
//  for (const auto& statement : */*node*/.getStatements()) {
//    statement->accept(*this);
//  }
}

void BbCfgGenerator::visit(const ast::ConstantNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::ExpressionNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::SpecialExpressionNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::BreakNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::ContinueNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::ForNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::GotoNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::IdentifierNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::IfNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::ParamsGroupNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::ParamsNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::ProgramNode& /*node*/) {
//  /*node*/.getRoutine()->accept(*this);
}

void BbCfgGenerator::visit(const ast::RecordTypeNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::RepeatNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::RoutineBodyNode& /*node*/) {
//  /*node*/.getStatements()->accept(*this);
}

void BbCfgGenerator::visit(const ast::RoutineDeclarationNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::RoutineHeadNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::RoutineNode& /*node*/) {
//  /*node*/.getHead()->accept(*this);
//  /*node*/.getBody()->accept(*this);
}

void BbCfgGenerator::visit(const ast::ConstRangeTypeNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::EnumerationTypeNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::RenameTypeNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::SimpleTypeNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::VarRangeTypeNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::StatementNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::TypeNode& /*node*/) {}

void BbCfgGenerator::visit(const ast::WhileNode& /*node*/) {}

void BbCfgGenerator::generate(const std::unique_ptr<ast::ProgramNode>& program) const {
//    const std::unique_ptr<ast::ProgramNode>& program) const {
//  program->accept(*this);

//  return controlFlowGraphs_;
}
}  // namespace bblocks
