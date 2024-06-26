#ifndef AST_SIMPLE_TYPE_NODE_HPP
#define AST_SIMPLE_TYPE_NODE_HPP

#include "constant_node.hpp"
#include "type_node.hpp"
#include "identifier_node.hpp"

namespace ast {
class SimpleTypeNode : public TypeNode {
 public:
  enum Representation { UNSPECIFIED, INTEGER, BOOLEAN, CHAR, RENAMING, ENUMERATION, CONST_RANGE, VAR_RANGE };

  SimpleTypeNode() : TypeNode{TypeType::SIMPLE}, representation_{UNSPECIFIED} {}
  explicit SimpleTypeNode(Representation representation) : TypeNode{TypeType::SIMPLE},
														   representation_{representation} {}

  SimpleTypeNode(const SimpleTypeNode &) = delete;
  SimpleTypeNode(SimpleTypeNode &&) = default;

  SimpleTypeNode &operator=(const SimpleTypeNode &) = delete;
  SimpleTypeNode &operator=(SimpleTypeNode &&) = default;

  ~SimpleTypeNode() override = default;

  [[nodiscard]] Representation getRepresentation() const { return representation_; }

 private:
  Representation representation_;
};

class RenameTypeNode : public SimpleTypeNode {
 public:
  RenameTypeNode() : SimpleTypeNode{RENAMING} {}
  explicit RenameTypeNode(IdentifierNode *identifier) : SimpleTypeNode{RENAMING}, identifier_{identifier} {}

  RenameTypeNode(const RenameTypeNode &) = delete;
  RenameTypeNode(RenameTypeNode &&) = default;

  RenameTypeNode &operator=(const RenameTypeNode &) = delete;
  RenameTypeNode &operator=(RenameTypeNode &&) = default;

  ~RenameTypeNode() override = default;

  [[nodiscard]] const std::unique_ptr<IdentifierNode> &getIdentifier() const { return identifier_; }

  void setIdentifier(std::unique_ptr<IdentifierNode> identifier) { identifier_ = std::move(identifier); }

 private:
  std::unique_ptr<IdentifierNode> identifier_;
};

class EnumerationTypeNode : public SimpleTypeNode {
 public:
  EnumerationTypeNode() : SimpleTypeNode{ENUMERATION} {}
  explicit EnumerationTypeNode(std::vector<IdentifierNode*> *identifiers) : SimpleTypeNode{ENUMERATION},
																		   identifiers_{identifiers} {}

  EnumerationTypeNode(const EnumerationTypeNode &) = delete;
  EnumerationTypeNode(EnumerationTypeNode &&) = default;

  EnumerationTypeNode &operator=(const EnumerationTypeNode &) = delete;
  EnumerationTypeNode &operator=(EnumerationTypeNode &&) = default;

  ~EnumerationTypeNode() override = default;

  [[nodiscard]] const std::unique_ptr<std::vector<IdentifierNode*>> &getIdentifiers() const { return identifiers_; }

  void setIdentifiers(std::unique_ptr<std::vector<IdentifierNode*>> identifiers) {
	identifiers_ = std::move(identifiers);
  }

 private:
  std::unique_ptr<std::vector<IdentifierNode*>> identifiers_;
};

class ConstRangeTypeNode : public SimpleTypeNode {
 public:
  ConstRangeTypeNode() : SimpleTypeNode{CONST_RANGE} {}
  explicit ConstRangeTypeNode(ConstantNode *lowerBound, ConstantNode *upperBound) : SimpleTypeNode{CONST_RANGE},
																					lowerBound_{lowerBound},
																					upperBound_{upperBound} {}

  ConstRangeTypeNode(const ConstRangeTypeNode &) = delete;
  ConstRangeTypeNode(ConstRangeTypeNode &&) = default;

  ConstRangeTypeNode &operator=(const ConstRangeTypeNode &) = delete;
  ConstRangeTypeNode &operator=(ConstRangeTypeNode &&) = default;

  ~ConstRangeTypeNode() override = default;

  [[nodiscard]] const std::unique_ptr<ConstantNode> &getLowerBound() const { return lowerBound_; }
  [[nodiscard]] const std::unique_ptr<ConstantNode> &getUpperBound() const { return upperBound_; }

  void setLowerBound(std::unique_ptr<ConstantNode> lowerBound) { lowerBound_ = std::move(lowerBound); }
  void setUpperBound(std::unique_ptr<ConstantNode> upperBound) { upperBound_ = std::move(upperBound); }

 private:
  std::unique_ptr<ConstantNode> lowerBound_;
  std::unique_ptr<ConstantNode> upperBound_;
};

class VarRangeTypeNode : public SimpleTypeNode {
 public:
  VarRangeTypeNode() : SimpleTypeNode{VAR_RANGE} {}
  explicit VarRangeTypeNode(IdentifierNode *lowerBound, IdentifierNode *upperBound) : SimpleTypeNode{VAR_RANGE},
																					lowerBound_{lowerBound},
																					upperBound_{upperBound} {}

  VarRangeTypeNode(const VarRangeTypeNode &) = delete;
  VarRangeTypeNode(VarRangeTypeNode &&) = default;

  VarRangeTypeNode &operator=(const VarRangeTypeNode &) = delete;
  VarRangeTypeNode &operator=(VarRangeTypeNode &&) = default;

  ~VarRangeTypeNode() override = default;

  [[nodiscard]] const std::unique_ptr<IdentifierNode> &getLowerBound() const { return lowerBound_; }
  [[nodiscard]] const std::unique_ptr<IdentifierNode> &getUpperBound() const { return upperBound_; }

  void setLowerBound(std::unique_ptr<IdentifierNode> lowerBound) { lowerBound_ = std::move(lowerBound); }
  void setUpperBound(std::unique_ptr<IdentifierNode> upperBound) { upperBound_ = std::move(upperBound); }

 private:
  std::unique_ptr<IdentifierNode> lowerBound_;
  std::unique_ptr<IdentifierNode> upperBound_;
};
} // namespace ast

#endif // AST_SIMPLE_TYPE_NODE_HPP
