#ifndef AST_RECORD_TYPE_NODE_HPP
#define AST_RECORD_TYPE_NODE_HPP

#include <memory>
#include <vector>

#include "identifier_node.hpp"
#include "type_node.hpp"

namespace ast {
class RecordTypeNode : public TypeNode {
 public:
  RecordTypeNode() : TypeNode{TypeType::RECORD} {}
  explicit RecordTypeNode(std::vector<std::pair<std::vector<IdentifierNode*>*, TypeNode*>*>* fields)
      : TypeNode{TypeType::RECORD}, fields_{fields} {}

  RecordTypeNode(const RecordTypeNode&) = delete;
  RecordTypeNode(RecordTypeNode&&) = default;

  RecordTypeNode& operator=(const RecordTypeNode&) = delete;
  RecordTypeNode& operator=(RecordTypeNode&&) = default;

  ~RecordTypeNode() override = default;

  [[nodiscard]] const std::unique_ptr<std::vector<std::pair<std::vector<IdentifierNode*>*, TypeNode*>*>>& getFields() const {
    return fields_;
  }

  void setFields(std::unique_ptr<std::vector<std::pair<std::vector<IdentifierNode*>*, TypeNode*>*>> fields) {
    fields_ = std::move(fields);
  }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    auto clone = std::make_unique<RecordTypeNode>();

    std::vector<std::pair<std::vector<IdentifierNode*>*, TypeNode*>*> fields;
    for (const auto& field : *fields_) {
      std::vector<IdentifierNode*> identifiers;
      for (const auto& identifier : *field->first) {
        identifiers.push_back(dynamic_cast<IdentifierNode*>(identifier->clone().release()));
      }
      fields.push_back(new std::pair<std::vector<IdentifierNode*>*, TypeNode*>{
          &identifiers, dynamic_cast<TypeNode*>(field->second->clone().release())});
    }
    clone->setFields(std::make_unique<std::vector<std::pair<std::vector<IdentifierNode*>*, TypeNode*>*>>(std::move(fields)));

    return clone;
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "RecordTypeNode:\n";
    for (const auto& field : *fields_) {
      out << std::string(tab + 2, ' ') << "Field:\n";
      for (const auto& identifier : *field->first) {
        identifier->print(out, tab + 4);
      }
      field->second->print(out, tab + 4);
    }
  }

 private:
  std::unique_ptr<std::vector<std::pair<std::vector<IdentifierNode*>*, TypeNode*>*>> fields_;
};
}  // namespace ast

#endif  // AST_RECORD_TYPE_NODE_HPP
