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
  explicit RecordTypeNode(std::vector<std::pair<std::vector<ast::IdentifierNode *>*, TypeNode *> *> *fields)
	  : TypeNode{TypeType::RECORD}, fields_{fields} {}

  RecordTypeNode(const RecordTypeNode &) = delete;
  RecordTypeNode(RecordTypeNode &&) = default;

  RecordTypeNode &operator=(const RecordTypeNode &) = delete;
  RecordTypeNode &operator=(RecordTypeNode &&) = default;

  ~RecordTypeNode() override = default;

  [[nodiscard]] const std::unique_ptr<std::vector<std::pair<std::vector<ast::IdentifierNode *>*,
															TypeNode *> *>> &getFields() const {
	return fields_;
  }

  void setFields(std::unique_ptr<std::vector<std::pair<std::vector<ast::IdentifierNode *>*, TypeNode *> *>> fields) {
	fields_ = std::move(fields);
  }

 private:
  std::unique_ptr<std::vector<std::pair<std::vector<ast::IdentifierNode *>*, TypeNode *> *>> fields_;
};
} // namespace ast

#endif // AST_RECORD_TYPE_NODE_HPP
