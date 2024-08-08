#include "simple_type_node.hpp"

namespace ast {
// SimpleTypeNode
void SimpleTypeNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> SimpleTypeNode::clone() const {
  return std::make_unique<SimpleTypeNode>(representation_);
}

void SimpleTypeNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "SimpleTypeNode ";
  switch (representation_) {
    case INTEGER:
      out << "INTEGER";
      break;
    case UNSIGNED:
      out << "UNSIGNED";
      break;
    case BOOLEAN:
      out << "BOOLEAN";
      break;
    case CHAR:
      out << "CHAR";
      break;
    case STRING:
      out << "STRING";
      break;
    case RENAMING:
      out << "RENAMING";
      break;
    case ENUMERATION:
      out << "ENUMERATION";
      break;
    case CONST_RANGE:
      out << "CONST_RANGE";
      break;
    case VAR_RANGE:
      out << "VAR_RANGE";
      break;
    default:
      out << "UNSPECIFIED";
      break;
  }
  out << '\n';
}

// RenameTypeNode
void RenameTypeNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> RenameTypeNode::clone() const {
  IdentifierNode* newIdentifier = dynamic_cast<IdentifierNode*>(identifier_->clone().release());
  return std::make_unique<RenameTypeNode>(newIdentifier);
}

void RenameTypeNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "RenameTypeNode:\n";
  identifier_->print(out, tab + 2);
}

// EnumerationTypeNode
void EnumerationTypeNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> EnumerationTypeNode::clone() const {
  auto newIdentifiers = std::make_unique<std::vector<IdentifierNode*>>();
  for (const auto& identifier : *identifiers_) {
    newIdentifiers->push_back(dynamic_cast<IdentifierNode*>(identifier->clone().release()));
  }
  return std::make_unique<EnumerationTypeNode>(newIdentifiers.get());
}

void EnumerationTypeNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "EnumerationTypeNode:\n";
  for (const auto& identifier : *identifiers_) {
    identifier->print(out, tab + 2);
  }
}

// ConstRangeTypeNode
void ConstRangeTypeNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> ConstRangeTypeNode::clone() const {
  ConstantNode* newLowerBound = dynamic_cast<ConstantNode*>(lowerBound_->clone().release());
  ConstantNode* newUpperBound = dynamic_cast<ConstantNode*>(upperBound_->clone().release());
  return std::make_unique<ConstRangeTypeNode>(newLowerBound, newUpperBound);
}

void ConstRangeTypeNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ConstRangeTypeNode:\n";
  lowerBound_->print(out, tab + 2);
  upperBound_->print(out, tab + 2);
}

// VarRangeTypeNode
void VarRangeTypeNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> VarRangeTypeNode::clone() const {
  IdentifierNode* newLowerBound = dynamic_cast<IdentifierNode*>(lowerBound_->clone().release());
  IdentifierNode* newUpperBound = dynamic_cast<IdentifierNode*>(upperBound_->clone().release());
  return std::make_unique<VarRangeTypeNode>(newLowerBound, newUpperBound);
}

void VarRangeTypeNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "VarRangeTypeNode:\n";
  lowerBound_->print(out, tab + 2);
  upperBound_->print(out, tab + 2);
}
}  // namespace ast
