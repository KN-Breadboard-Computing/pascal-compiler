#include "record_type_node.hpp"

namespace ast {
std::string RecordTypeNode::flat() const {
  std::string mergedRecord = "record$$";
  for (const auto* field : *fields_) {
    for (const auto* ident : *field->first) {
      mergedRecord += ident->getName() + "#(" + field->second->flat() + ")$";
    }
  }

  return mergedRecord + "$";
}

void RecordTypeNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

[[nodiscard]] std::unique_ptr<AstNode> RecordTypeNode::clone() const {
  auto clone = std::make_unique<RecordTypeNode>();

  std::vector<std::pair<std::vector<IdentifierNode*>*, TypeNode*>*> fields;
  for (const auto& field : *fields_) {
    std::vector<IdentifierNode*> identifiers;
    for (const auto& identifier : *field->first) {
      identifiers.push_back(dynamic_cast<IdentifierNode*>(identifier->clone().release()));
    }
    fields.push_back(new std::pair<std::vector<IdentifierNode*>*, TypeNode*>{&identifiers, dynamic_cast<TypeNode*>(field->second->clone().release())});
  }
  clone->setFields(std::make_unique<std::vector<std::pair<std::vector<IdentifierNode*>*, TypeNode*>*>>(std::move(fields)));

  return clone;
}

void RecordTypeNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "RecordTypeNode:\n";
  for (const auto& field : *fields_) {
    out << std::string(tab + 2, ' ') << "Field:\n";
    for (const auto& identifier : *field->first) {
      identifier->print(out, tab + 4);
    }
    field->second->print(out, tab + 4);
  }
}
}  // namespace ast
