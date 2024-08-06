#ifndef AST_AST_VISITOR_HPP
#define AST_AST_VISITOR_HPP

namespace ast {
class AstVisitor {
 public:
  AstVisitor() = default;
  virtual ~AstVisitor() = default;

  virtual void visit(class ArgumentsListNode& node) = 0;
  virtual void visit(class ArrayTypeNode& node) = 0;
  virtual void visit(class AssignNode& node) = 0;
  virtual void visit(class AssignToArrayNode& node) = 0;
  virtual void visit(class AssignToRecordFieldNode& node) = 0;
  virtual void visit(class AssignToVariableNode& node) = 0;
  virtual void visit(class AstNode& node) = 0;
  virtual void visit(class BuiltinCallNode& node) = 0;
  virtual void visit(class CallNode& node) = 0;
  virtual void visit(class UserDefineCallNode& node) = 0;
  virtual void visit(class CaseNode& node) = 0;
  virtual void visit(class CompoundStatementNode& node) = 0;
  virtual void visit(class ConstantNode& node) = 0;
  //  virtual void visit(class ConstantNodeSpec& node) = 0;
  //  virtual void visit(class IntegerConstantNode& node) = 0;
  //  virtual void visit(class CharConstantNode& node) = 0;
  //  virtual void visit(class BooleanConstantNode& node) = 0;
  //  virtual void visit(class StringConstantNode& node) = 0;
  virtual void visit(class ExpressionNode& node) = 0;
  virtual void visit(class SpecialExpressionNode& node) = 0;
  virtual void visit(class BreakNode& node) = 0;
  virtual void visit(class ContinueNode& node) = 0;
  virtual void visit(class ForNode& node) = 0;
  virtual void visit(class GotoNode& node) = 0;
  virtual void visit(class IdentifierNode& node) = 0;
  virtual void visit(class IfNode& node) = 0;
  virtual void visit(class ParamsGroupNode& node) = 0;
  virtual void visit(class ParamsNode& node) = 0;
  virtual void visit(class ProgramNode& node) = 0;
  virtual void visit(class RecordTypeNode& node) = 0;
  virtual void visit(class RepeatNode& node) = 0;
  virtual void visit(class RoutineBodyNode& node) = 0;
  virtual void visit(class RoutineDeclarationNode& node) = 0;
  virtual void visit(class RoutineHeadNode& node) = 0;
  virtual void visit(class RoutineNode& node) = 0;
  virtual void visit(class ConstRangeTypeNode& node) = 0;
  virtual void visit(class EnumerationTypeNode& node) = 0;
  virtual void visit(class RenameTypeNode& node) = 0;
  virtual void visit(class SimpleTypeNode& node) = 0;
  virtual void visit(class VarRangeTypeNode& node) = 0;
  virtual void visit(class StatementNode& node) = 0;
  virtual void visit(class TypeNode& node) = 0;
  virtual void visit(class WhileNode& node) = 0;
};
}  // namespace ast

#endif  // AST_AST_VISITOR_HPP
