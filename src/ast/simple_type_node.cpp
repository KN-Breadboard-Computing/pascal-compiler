#include "simple_type_node.hpp"

#include "../context/context.hpp"

namespace ast {
// BasicTypeNode
std::string BasicTypeNode::flat() const {
  switch (basicType_) {
    case ast::BasicTypeNode::BasicType::INTEGER:
      return "integer";
    case ast::BasicTypeNode::BasicType::BOOLEAN:
      return "boolean";
    case ast::BasicTypeNode::BasicType::CHAR:
      return "char";
    case ast::BasicTypeNode::BasicType::STRING:
      return "string";
  }
}

void BasicTypeNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

[[nodiscard]] std::unique_ptr<AstNode> BasicTypeNode::clone() const {
  return std::make_unique<BasicTypeNode>(basicType_);
}

void BasicTypeNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "BasicTypeNode ";
  switch (basicType_) {
    case BasicType::INTEGER:
      out << "INTEGER\n";
      break;
    case BasicType::BOOLEAN:
      out << "BOOLEAN\n";
      break;
    case BasicType::CHAR:
      out << "CHAR\n";
      break;
    case BasicType::STRING:
      out << "STRING\n";
      break;
  }
}

// RenameTypeNode
std::string RenameTypeNode::flat() const {
  auto* const ctx = Context::getInstance();
  return ctx->getLookupTable().getType(identifier_->getName(), ctx->getCurrentScope()).type;
}

void RenameTypeNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
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
std::string EnumerationTypeNode::flat() const {
  std::string mergedEnum = "enum%";
  for (auto& identifier : *identifiers_) {
    mergedEnum += identifier->getName() + "%";
  }
  return mergedEnum;
}

void EnumerationTypeNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
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
std::string ConstRangeTypeNode::flat() const {
  return "constrange%" + lowerBound_->flat() + ".." + upperBound_->flat();
}

void ConstRangeTypeNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
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
std::string VarRangeTypeNode::flat() const {
  auto* const ctx = Context::getInstance();

  const std::string lowBound = lowerBound_->getName();
  const std::string upBound = upperBound_->getName();

  auto properEnums = ctx->getLookupTable().getTypes(
      [&](const std::string&, const LookupTable::TypeInfo& tf) { return tf.alive && tf.type.find("enum%") == 0 && tf.type.find("%" + lowBound + "%") != std::string::npos && tf.type.find("%" + upBound + "%") != std::string::npos; },
      ctx->getCurrentScope());

  if (properEnums.empty()) {
    throw std::runtime_error(lowBound + " and " + upBound + " are not in any enum");
  }

  if (properEnums.size() > 1) {
    throw std::runtime_error(lowBound + " and " + upBound + " are in more than one enum");
  }

  return "enumrange%" + properEnums.front().name + "%" + lowBound + ".." + upBound;
}

void VarRangeTypeNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
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
