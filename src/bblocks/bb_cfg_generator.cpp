#include "bb_cfg_generator.hpp"
#include "../context.hpp"

#include <stdexcept>

namespace bblocks {
Context* ctx = Context::getInstance();

void BbCfgGenerator::visit(const ast::ArgumentsListNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::ArrayTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::AssignNode* node) {
  node->getRhs()->accept(this);
  generateVariableMove(node->getLhs().get(), ctx->getLastTempVariable());
}

void BbCfgGenerator::visit(const ast::BuiltinCallNode* node) {
  const ast::BuiltinCallNode::FunctionName funName = node->getFunctionName();
  switch (funName) {
    case ast::BuiltinCallNode::READ: {
      currentBasicBlock_.addInstruction(std::make_unique<BBCall>("read", std::vector<std::string>{ctx->generateTempVariable()}));
      generateVariableMove(node->getArguments()->getArguments().front(), ctx->getLastTempVariable());
      break;
    }
    case ast::BuiltinCallNode::READLN: {
      std::make_unique<BBCall>("readln", std::vector<std::string>{});
      break;
    }
    case ast::BuiltinCallNode::WRITE:
    case ast::BuiltinCallNode::WRITELN: {
      std::vector<std::string> args{};
      for (auto* arg : node->getArguments()->getArguments()) {
        if (arg->getInferredType() == "string") {
          ast::StringConstantNode* constant = dynamic_cast<ast::StringConstantNode*>(arg);
          args.emplace_back(constant->getValue());
        }
        else {
          arg->accept(this);
          args.emplace_back(ctx->getLastTempVariable());
        }
      }
      currentBasicBlock_.addInstruction(
          std::make_unique<BBCall>(funName == ast::BuiltinCallNode::WRITE ? "write" : "writeln", args));
      break;
    }
    case ast::BuiltinCallNode::MEMORY_READ:
    case ast::BuiltinCallNode::STACK_READ: {
      node->getArguments()->getArguments().at(0)->accept(this);
      const std::string high = ctx->getLastTempVariable();
      node->getArguments()->getArguments().at(1)->accept(this);
      const std::string low = ctx->getLastTempVariable();

      currentBasicBlock_.addInstruction(
          std::make_unique<BBCall>(funName == ast::BuiltinCallNode::MEMORY_READ ? "mload" : "sload",
                                   std::vector<std::string>{high, low, ctx->generateTempVariable()}));
      generateVariableMove(node->getArguments()->getArguments().at(2), ctx->getLastTempVariable());
    }
    case ast::BuiltinCallNode::MEMORY_WRITE:
    case ast::BuiltinCallNode::STACK_WRITE: {
      node->getArguments()->getArguments().at(0)->accept(this);
      const std::string high = ctx->getLastTempVariable();
      node->getArguments()->getArguments().at(1)->accept(this);
      const std::string low = ctx->getLastTempVariable();
      node->getArguments()->getArguments().at(2)->accept(this);
      const std::string valVar = ctx->getLastTempVariable();

      currentBasicBlock_.addInstruction(std::make_unique<BBCall>(
          funName == ast::BuiltinCallNode::MEMORY_READ ? "mstore" : "sstore", std::vector<std::string>{high, low, valVar}));
    }
  }
}

void BbCfgGenerator::visit(const ast::UserDefineCallNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::CaseNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::CompoundStatementNode* node) {
  for (auto* const statement : *node->getStatements()) {
    statement->accept(this);
  }
}

void BbCfgGenerator::visit(const ast::ConstantNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::MathExpressionNode* node) {
  std::string leftOperand;
  if (node->getLeft() != nullptr) {
    node->getLeft()->accept(this);
    leftOperand = ctx->getLastTempVariable();
  }

  std::string rightOperand;
  if (node->getRight() != nullptr) {
    node->getRight()->accept(this);
    rightOperand = ctx->getLastTempVariable();
  }

  switch (node->getFunctionName()) {
    case ast::MathExpressionNode::ADDITION: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::ADD,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::SUBTRACTION: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::SUB,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::MULTIPLICATION: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::MUL,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::DIVISION: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::DIV,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::MODULUS: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::MOD,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::NEGATION: {
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(leftOperand, ctx->generateTempVariable(),
                                                                             BBUnaryOperationVV::OperationType::NEG,
                                                                             BBUnaryOperationVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::AND: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::AND,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::OR: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::OR,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::NOT: {
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(leftOperand, ctx->generateTempVariable(),
                                                                             BBUnaryOperationVV::OperationType::NOT,
                                                                             BBUnaryOperationVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::EQUAL: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::EQ,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::NOT_EQUAL: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::NE,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::LESS: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::LT,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::LESS_EQUAL: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::LE,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::GREATER: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::GT,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::GREATER_EQUAL: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::GE,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
  }
}

void BbCfgGenerator::visit(const ast::SpecialExpressionNode* node) {
  std::string argument1;
  if (node->getArgument1() != nullptr) {
    node->getArgument1()->accept(this);
    argument1 = ctx->getLastTempVariable();
  }

  std::string argument2;
  if (node->getArgument2() != nullptr) {
    node->getArgument2()->accept(this);
    argument2 = ctx->getLastTempVariable();
  }

  switch (node->getFunctionName()) {
    case ast::SpecialExpressionNode::VARIABLE: {
      ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(node->getArgument1().get());
      currentBasicBlock_.addInstruction(std::make_unique<BBMoveVV>(
          variable->getName(), ctx->generateTempVariable(), BBMoveVV::SourceType::VARIABLE, BBMoveVV::DestinationType::VARIABLE));
      break;
    }
    case ast::SpecialExpressionNode::CALL: {
      ast::IdentifierNode* function = dynamic_cast<ast::IdentifierNode*>(node->getArgument1().get());
      ast::ArgumentsListNode* arguments = dynamic_cast<ast::ArgumentsListNode*>(node->getArgument2().get());

      std::vector<std::string> args{};
      for (auto* arg : arguments->getArguments()) {
        if (arg->getInferredType() == "string") {
          ast::StringConstantNode* constant = dynamic_cast<ast::StringConstantNode*>(arg);
          args.emplace_back(constant->getValue());
        }
        else {
          arg->accept(this);
          args.emplace_back(ctx->getLastTempVariable());
        }
      }
      currentBasicBlock_.addInstruction(std::make_unique<BBCall>(function->getName(), args));
      break;
    }
    case ast::SpecialExpressionNode::ARRAY_ACCESS: {
      break;
    }
    case ast::SpecialExpressionNode::CONST: {
      ast::ConstantNode* constant = dynamic_cast<ast::ConstantNode*>(node->getArgument1().get());
      switch (constant->getConstantType()) {
        case ast::ConstantNode::UNSPECIFIED:
          throw std::runtime_error("Type error");
        case ast::ConstantNode::INTEGER: {
          ast::IntegerConstantNode* integerConstant = dynamic_cast<ast::IntegerConstantNode*>(constant);
          currentBasicBlock_.addInstruction(std::make_unique<BBMoveNV>(integerConstant->getValue(), ctx->generateTempVariable(),
                                                                       BBMoveNV::SourceType::NUMERIC,
                                                                       BBMoveNV::DestinationType::VARIABLE));
          break;
        }
        case ast::ConstantNode::CHAR: {
          ast::CharConstantNode* charConstant = dynamic_cast<ast::CharConstantNode*>(constant);
          currentBasicBlock_.addInstruction(std::make_unique<BBMoveNV>(charConstant->getValue(), ctx->generateTempVariable(),
                                                                       BBMoveNV::SourceType::NUMERIC,
                                                                       BBMoveNV::DestinationType::VARIABLE));
          break;
        }
        case ast::ConstantNode::BOOLEAN: {
          ast::BooleanConstantNode* boolConstant = dynamic_cast<ast::BooleanConstantNode*>(constant);
          currentBasicBlock_.addInstruction(std::make_unique<BBMoveNV>(boolConstant->getValue(), ctx->generateTempVariable(),
                                                                       BBMoveNV::SourceType::NUMERIC,
                                                                       BBMoveNV::DestinationType::VARIABLE));
          break;
        }
        case ast::ConstantNode::STRING:
          break;
      }
      break;
    }
    case ast::SpecialExpressionNode::RECORD_ACCESS:
      break;
    case ast::SpecialExpressionNode::ENUM_ELEMENT:
      break;
    case ast::SpecialExpressionNode::ABS: {
      node->getArgument1()->accept(this);
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(
          ctx->getLastTempVariable(), ctx->generateTempVariable(), BBUnaryOperationVV::OperationType::SHL,
          BBUnaryOperationVV::DestinationType::VARIABLE));
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(
          ctx->getLastTempVariable(), ctx->generateTempVariable(), BBUnaryOperationVV::OperationType::SHR,
          BBUnaryOperationVV::DestinationType::VARIABLE));
    }
    case ast::SpecialExpressionNode::ODD: {
      const std::vector<std::string> nextLabels = ctx->getNextBBlockLabels(4);
      node->getArgument1()->accept(this);
      currentBasicBlock_.addInstruction(std::make_unique<BBBranchV>(ctx->getLastTempVariable(), BBBranchV::Condition::ODD,
                                                                    nextLabels.at(1), nextLabels.at(2)));
      saveBasicBlock();
      currentControlFlowGraph_.addBlocksLink(nextLabels.at(0), nextLabels.at(1));
      currentControlFlowGraph_.addBlocksLink(nextLabels.at(0), nextLabels.at(2));

      currentBasicBlock_.addInstruction(std::make_unique<BBMoveNV>(1, ctx->generateTempVariable(), BBMoveNV::SourceType::NUMERIC,
                                                                   BBMoveNV::DestinationType::VARIABLE));
      saveBasicBlock();

      currentBasicBlock_.addInstruction(std::make_unique<BBMoveNV>(0, ctx->generateTempVariable(), BBMoveNV::SourceType::NUMERIC,
                                                                   BBMoveNV::DestinationType::VARIABLE));
      saveBasicBlock();

      currentControlFlowGraph_.addBlocksLink(nextLabels.at(1), nextLabels.at(3));
      currentControlFlowGraph_.addBlocksLink(nextLabels.at(2), nextLabels.at(3));
      break;
    }
    case ast::SpecialExpressionNode::PRED: {
      node->getArgument1()->accept(this);
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(
          ctx->getLastTempVariable(), ctx->generateTempVariable(), BBUnaryOperationVV::OperationType::DEC,
          BBUnaryOperationVV::DestinationType::VARIABLE));
      break;
    }
    case ast::SpecialExpressionNode::SUCC: {
      node->getArgument1()->accept(this);
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(
          ctx->getLastTempVariable(), ctx->generateTempVariable(), BBUnaryOperationVV::OperationType::INC,
          BBUnaryOperationVV::DestinationType::VARIABLE));
      break;
    }
    case ast::SpecialExpressionNode::PARENTHESIS:
    case ast::SpecialExpressionNode::CHR:
    case ast::SpecialExpressionNode::ORD:
    case ast::SpecialExpressionNode::TOINT:
    case ast::SpecialExpressionNode::TOCHAR:
    case ast::SpecialExpressionNode::TOBOOL: {
      node->getArgument1()->accept(this);
      break;
    }
  }
}

void BbCfgGenerator::visit(const ast::BreakNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::ContinueNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::ForNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::GotoNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::IdentifierNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::IfNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::ParamsGroupNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::ParamsNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::ProgramNode* node) {
  currentScope_ += ".program";
  node->getRoutine()->accept(this);
}

void BbCfgGenerator::visit(const ast::RecordTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::RepeatNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::RoutineBodyNode* node) {
  node->getStatements()->accept(this);
}

void BbCfgGenerator::visit(const ast::RoutineDeclarationNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::RoutineHeadNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::RoutineNode* node) {
  node->getHead()->accept(this);
  node->getBody()->accept(this);

  saveBasicBlock();

  controlFlowGraphs_.insert({"program", currentControlFlowGraph_});
}

void BbCfgGenerator::visit(const ast::ConstRangeTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::EnumerationTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::RenameTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::BasicTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::VarRangeTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::WhileNode* /*node*/) {}

std::map<std::string, BBControlFlowGraph> BbCfgGenerator::generate(const std::unique_ptr<ast::ProgramNode>& program) {
  currentScope_ = "";
  visit(program.get());

  return controlFlowGraphs_;
}

void BbCfgGenerator::saveBasicBlock() {
  currentControlFlowGraph_.addBBlock(ctx->generateBBlockLabel(), std::move(currentBasicBlock_));
  currentBasicBlock_ = BasicBlock{};
}

void BbCfgGenerator::generateVariableMove(ast::ExpressionNode* dest, const std::string& src) {
  if (dest->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
    throw std::runtime_error("Type error");
  }

  ast::SpecialExpressionNode* varArrRec = dynamic_cast<ast::SpecialExpressionNode*>(dest);
  if (varArrRec->getFunctionName() == ast::SpecialExpressionNode::FunctionName::VARIABLE) {
    ast::IdentifierNode* var = dynamic_cast<ast::IdentifierNode*>(varArrRec->getArgument1().get());
    currentBasicBlock_.addInstruction(
        std::make_unique<BBMoveVV>(src, var->getName(), BBMoveVV::SourceType::VARIABLE, BBMoveVV::DestinationType::VARIABLE));
  }
  else if (varArrRec->getFunctionName() == ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS) {}
  else if (varArrRec->getFunctionName() == ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS) {}
  else {
    throw std::runtime_error("Type error");
  }
}
}  // namespace bblocks
