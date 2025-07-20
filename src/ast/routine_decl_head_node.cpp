#include "routine_decl_head_node.hpp"

namespace ast {
// RoutineHeadNode
[[nodiscard]] std::unique_ptr<AstNode> RoutineHeadNode::clone() const {
  auto clone = std::make_unique<RoutineHeadNode>();
  if (constantsPart_ != nullptr) {
    auto constantsPart = std::make_unique<std::vector<std::pair<IdentifierNode*, ConstantNode*>*>>();
    for (const auto& constant : *constantsPart_) {
      constantsPart->push_back(new std::pair<IdentifierNode*, ConstantNode*>(dynamic_cast<IdentifierNode*>(constant->first->clone().release()), dynamic_cast<ConstantNode*>(constant->second->clone().release())));
    }
    clone->setConstantsPart(constantsPart);
  }
  if (typesPart_ != nullptr) {
    auto typesPart = std::make_unique<std::vector<std::pair<IdentifierNode*, TypeNode*>*>>();
    for (const auto& type : *typesPart_) {
      typesPart->push_back(new std::pair<IdentifierNode*, TypeNode*>(dynamic_cast<IdentifierNode*>(type->first->clone().release()), dynamic_cast<TypeNode*>(type->second->clone().release())));
    }
    clone->setTypesPart(typesPart);
  }
  if (variablesPart_ != nullptr) {
    auto variablesPart = std::make_unique<std::vector<std::pair<std::vector<IdentifierNode*>*, TypeNode*>*>>();
    for (const auto& variable : *variablesPart_) {
      auto identifiers = new std::vector<IdentifierNode*>();
      for (const auto& identifier : *variable->first) {
        identifiers->push_back(dynamic_cast<IdentifierNode*>(identifier->clone().release()));
      }
      variablesPart->push_back(new std::pair<std::vector<IdentifierNode*>*, TypeNode*>(identifiers, dynamic_cast<TypeNode*>(variable->second->clone().release())));
    }
    clone->setVariablesPart(variablesPart);
  }
  if (routinePart_ != nullptr) {
    auto routinePart = std::make_unique<std::vector<RoutineDeclarationNode*>>();
    for (const auto& routine : *routinePart_) {
      routinePart->push_back(dynamic_cast<RoutineDeclarationNode*>(routine->clone().release()));
    }
    clone->setRoutinePart(routinePart);
  }

  return clone;
}

void RoutineHeadNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "RoutineHeadNode:\n";
  if (constantsPart_ != nullptr) {
    out << std::string(tab + 2, ' ') << "Constants:\n";
    std::size_t index{0};
    for (const auto& constant : *constantsPart_) {
      out << std::string(tab + 4, ' ') << "Constant " << index++ << ":\n";
      constant->first->print(out, tab + 6);
      constant->second->print(out, tab + 6);
    }
  }
  if (typesPart_ != nullptr) {
    out << std::string(tab + 2, ' ') << "Types:\n";
    std::size_t index{0};
    for (const auto& type : *typesPart_) {
      out << std::string(tab + 4, ' ') << "Type " << index++ << ":\n";
      type->first->print(out, tab + 6);
      type->second->print(out, tab + 6);
    }
  }
  if (variablesPart_ != nullptr) {
    out << std::string(tab + 2, ' ') << "Variables:\n";
    std::size_t index{0};
    for (const auto& variable : *variablesPart_) {
      out << std::string(tab + 4, ' ') << "Group " << index++ << ":\n";
      variable->second->print(out, tab + 6);
      out << std::string(tab + 6, ' ') << "Identifiers:\n";
      for (const auto& identifier : *variable->first) {
        identifier->print(out, tab + 8);
      }
    }
  }
  if (routinePart_ != nullptr) {
    out << std::string(tab + 2, ' ') << "Routines:\n";
    for (const auto& routine : *routinePart_) {
      routine->print(out, tab + 4);
    }
  }
}

void RoutineHeadNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

// RoutineDeclarationNode
[[nodiscard]] std::unique_ptr<AstNode> RoutineDeclarationNode::clone() const {
  auto clone = std::make_unique<RoutineDeclarationNode>(routineType_, name_, nullptr, nullptr, nullptr);
  if (params_ != nullptr) {
    clone->setParams(std::unique_ptr<ParamsNode>(dynamic_cast<ParamsNode*>(params_->clone().release())));
  }
  if (returnType_ != nullptr) {
    clone->setReturnType(std::unique_ptr<SimpleTypeNode>(dynamic_cast<SimpleTypeNode*>(returnType_->clone().release())));
  }
  if (routine_ != nullptr) {
    clone->setRoutine(std::unique_ptr<RoutineNode>(dynamic_cast<RoutineNode*>(routine_->clone().release())));
  }

  return clone;
}

void RoutineDeclarationNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "RoutineDeclarationNode:\n";
  out << std::string(tab + 2, ' ') << "Name: " << name_ << '\n';
  if (params_ != nullptr) {
    params_->print(out, tab + 2);
  }
  if (returnType_ != nullptr) {
    returnType_->print(out, tab + 2);
  }
  if (routine_ != nullptr) {
    routine_->print(out, tab + 2);
  }
}

void RoutineDeclarationNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

// RoutineNode
[[nodiscard]] std::unique_ptr<AstNode> RoutineNode::clone() const {
  RoutineHeadNode* newHead = dynamic_cast<RoutineHeadNode*>(head_->clone().release());
  RoutineBodyNode* newBody = dynamic_cast<RoutineBodyNode*>(body_->clone().release());
  return std::make_unique<RoutineNode>(subType_, newHead, newBody);
}

void RoutineNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "RoutineNode of type ";
  switch (subType_) {
    case SubType::MAIN:
      out << "MAIN:\n";
      break;
    case SubType::FUNCTION:
      out << "FUNCTION:\n";
      break;
    case SubType::PROCEDURE:
      out << "PROCEDURE:\n";
      break;
    default:
      out << "UNSPECIFIED:\n";
      break;
  }
  head_->print(out, tab + 2);
  body_->print(out, tab + 2);
}

void RoutineNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}
}  // namespace ast
