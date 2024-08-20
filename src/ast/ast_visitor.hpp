#ifndef AST_AST_VISITOR_HPP
#define AST_AST_VISITOR_HPP

namespace ast {
class AstVisitor {
 public:
  AstVisitor() = default;
  virtual ~AstVisitor() = default;

  virtual void visit(const class ArgumentsListNode* node) = 0;
  virtual void visit(const class ArrayTypeNode* node) = 0;
  virtual void visit(const class AssignNode* node) = 0;
  virtual void visit(const class BuiltinCallNode* node) = 0;
  virtual void visit(const class UserDefineCallNode* node) = 0;
  virtual void visit(const class CaseNode* node) = 0;
  virtual void visit(const class CompoundStatementNode* node) = 0;
  virtual void visit(const class ConstantNode* node) = 0;
  virtual void visit(const class MathExpressionNode* node) = 0;
  virtual void visit(const class SpecialExpressionNode* node) = 0;
  virtual void visit(const class BreakNode* node) = 0;
  virtual void visit(const class ContinueNode* node) = 0;
  virtual void visit(const class ForNode* node) = 0;
  virtual void visit(const class GotoNode* node) = 0;
  virtual void visit(const class IdentifierNode* node) = 0;
  virtual void visit(const class IfNode* node) = 0;
  virtual void visit(const class ParamsGroupNode* node) = 0;
  virtual void visit(const class ParamsNode* node) = 0;
  virtual void visit(const class ProgramNode* node) = 0;
  virtual void visit(const class RecordTypeNode* node) = 0;
  virtual void visit(const class RepeatNode* node) = 0;
  virtual void visit(const class RoutineBodyNode* node) = 0;
  virtual void visit(const class RoutineDeclarationNode* node) = 0;
  virtual void visit(const class RoutineHeadNode* node) = 0;
  virtual void visit(const class RoutineNode* node) = 0;
  virtual void visit(const class ConstRangeTypeNode* node) = 0;
  virtual void visit(const class EnumerationTypeNode* node) = 0;
  virtual void visit(const class RenameTypeNode* node) = 0;
  virtual void visit(const class BasicTypeNode* node) = 0;
  virtual void visit(const class VarRangeTypeNode* node) = 0;
  virtual void visit(const class WhileNode* node) = 0;
};
}  // namespace ast

#endif  // AST_AST_VISITOR_HPP
