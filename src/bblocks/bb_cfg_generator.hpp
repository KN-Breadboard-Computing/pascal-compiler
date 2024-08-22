#ifndef BBLOCKS_BB_CFG_GENERATOR_HPP
#define BBLOCKS_BB_CFG_GENERATOR_HPP

#include <map>
#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "../ast/ast_visitor.hpp"

#include "../ast/arguments_list_node.hpp"
#include "../ast/array_type_node.hpp"
#include "../ast/assign_node.hpp"
#include "../ast/break_node.hpp"
#include "../ast/call_node.hpp"
#include "../ast/case_node.hpp"
#include "../ast/compound_statement_node.hpp"
#include "../ast/constant_node.hpp"
#include "../ast/continue_node.hpp"
#include "../ast/expression_node.hpp"
#include "../ast/for_node.hpp"
#include "../ast/goto_node.hpp"
#include "../ast/identifier_node.hpp"
#include "../ast/if_node.hpp"
#include "../ast/params_group_node.hpp"
#include "../ast/params_node.hpp"
#include "../ast/program_node.hpp"
#include "../ast/record_type_node.hpp"
#include "../ast/repeat_node.hpp"
#include "../ast/routine_body_node.hpp"
#include "../ast/routine_decl_head_node.hpp"
#include "../ast/simple_type_node.hpp"
#include "../ast/while_node.hpp"

#include "bb_control_flow_graph.hpp"

namespace bblocks {
class BbCfgGenerator : public ast::AstVisitor {
 public:
  BbCfgGenerator() = default;

  BbCfgGenerator(const BbCfgGenerator&) = delete;
  BbCfgGenerator(BbCfgGenerator&&) = default;

  BbCfgGenerator& operator=(const BbCfgGenerator&) = delete;
  BbCfgGenerator& operator=(BbCfgGenerator&&) = default;

  virtual ~BbCfgGenerator() = default;

  virtual void visit(const ast::ArgumentsListNode* node) override;
  virtual void visit(const ast::ArrayTypeNode* node) override;
  virtual void visit(const ast::AssignNode* node) override;
  virtual void visit(const ast::BuiltinCallNode* node) override;
  virtual void visit(const ast::UserDefineCallNode* node) override;
  virtual void visit(const ast::CaseNode* node) override;
  virtual void visit(const ast::CompoundStatementNode* node) override;
  virtual void visit(const ast::ConstantNode* node) override;
  virtual void visit(const ast::MathExpressionNode* node) override;
  virtual void visit(const ast::SpecialExpressionNode* node) override;
  virtual void visit(const ast::BreakNode* node) override;
  virtual void visit(const ast::ContinueNode* node) override;
  virtual void visit(const ast::ForNode* node) override;
  virtual void visit(const ast::GotoNode* node) override;
  virtual void visit(const ast::IdentifierNode* node) override;
  virtual void visit(const ast::IfNode* node) override;
  virtual void visit(const ast::ParamsGroupNode* node) override;
  virtual void visit(const ast::ParamsNode* node) override;
  virtual void visit(const ast::ProgramNode* node) override;
  virtual void visit(const ast::RecordTypeNode* node) override;
  virtual void visit(const ast::RepeatNode* node) override;
  virtual void visit(const ast::RoutineBodyNode* node) override;
  virtual void visit(const ast::RoutineDeclarationNode* node) override;
  virtual void visit(const ast::RoutineHeadNode* node) override;
  virtual void visit(const ast::RoutineNode* node) override;
  virtual void visit(const ast::ConstRangeTypeNode* node) override;
  virtual void visit(const ast::EnumerationTypeNode* node) override;
  virtual void visit(const ast::RenameTypeNode* node) override;
  virtual void visit(const ast::BasicTypeNode* node) override;
  virtual void visit(const ast::VarRangeTypeNode* node) override;
  virtual void visit(const ast::WhileNode* node) override;

  [[nodiscard]] std::map<std::string, BBControlFlowGraph> generate(const std::unique_ptr<ast::ProgramNode>& program);

 private:
  void newControlFlowGraph(const std::string& label);
  void saveBasicBlock(const std::string& label, const std::string& description, bool connectToLastBlock, bool setAsExit);

  void generateVariableMove(ast::ExpressionNode* dest, const std::string& src);

  std::string currentScope_;
  BasicBlock currentBasicBlock_;
  std::stack<BBControlFlowGraph> controlFlowGraphs_;
  std::map<std::string, BBControlFlowGraph> functionControlFlowGraphs_;
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_CFG_GENERATOR_HPP
