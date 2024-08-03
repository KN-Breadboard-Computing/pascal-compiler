#ifndef AST_SIMPLE_TYPE_NODE_HPP
#define AST_SIMPLE_TYPE_NODE_HPP

#include "constant_node.hpp"
#include "identifier_node.hpp"
#include "type_node.hpp"

namespace ast {
class SimpleTypeNode : public TypeNode {
 public:
  enum Representation { UNSPECIFIED, INTEGER, UNSIGNED, BOOLEAN, CHAR, STRING, RENAMING, ENUMERATION, CONST_RANGE, VAR_RANGE };

  SimpleTypeNode() : TypeNode{TypeType::SIMPLE}, representation_{UNSPECIFIED} {}
  explicit SimpleTypeNode(Representation representation) : TypeNode{TypeType::SIMPLE}, representation_{representation} {}

  SimpleTypeNode(const SimpleTypeNode&) = delete;
  SimpleTypeNode(SimpleTypeNode&&) = default;

  SimpleTypeNode& operator=(const SimpleTypeNode&) = delete;
  SimpleTypeNode& operator=(SimpleTypeNode&&) = default;

  ~SimpleTypeNode() override = default;

  [[nodiscard]] Representation getRepresentation() const { return representation_; }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    return std::make_unique<SimpleTypeNode>(representation_);
  }

  virtual void print(std::ostream& out, int tab) const override {
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

 private:
  Representation representation_;
};

class RenameTypeNode : public SimpleTypeNode {
 public:
  RenameTypeNode() : SimpleTypeNode{RENAMING} {}
  explicit RenameTypeNode(IdentifierNode* identifier) : SimpleTypeNode{RENAMING}, identifier_{identifier} {}

  RenameTypeNode(const RenameTypeNode&) = delete;
  RenameTypeNode(RenameTypeNode&&) = default;

  RenameTypeNode& operator=(const RenameTypeNode&) = delete;
  RenameTypeNode& operator=(RenameTypeNode&&) = default;

  ~RenameTypeNode() override = default;

  [[nodiscard]] const std::unique_ptr<IdentifierNode>& getIdentifier() const { return identifier_; }

  void setIdentifier(std::unique_ptr<IdentifierNode> identifier) { identifier_ = std::move(identifier); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    IdentifierNode* newIdentifier = dynamic_cast<IdentifierNode*>(identifier_->clone().release());
    return std::make_unique<RenameTypeNode>(newIdentifier);
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "RenameTypeNode:\n";
    identifier_->print(out, tab + 2);
  }

 private:
  std::unique_ptr<IdentifierNode> identifier_;
};

class EnumerationTypeNode : public SimpleTypeNode {
 public:
  EnumerationTypeNode() : SimpleTypeNode{ENUMERATION} {}
  explicit EnumerationTypeNode(std::vector<IdentifierNode*>* identifiers)
      : SimpleTypeNode{ENUMERATION}, identifiers_{identifiers} {}

  EnumerationTypeNode(const EnumerationTypeNode&) = delete;
  EnumerationTypeNode(EnumerationTypeNode&&) = default;

  EnumerationTypeNode& operator=(const EnumerationTypeNode&) = delete;
  EnumerationTypeNode& operator=(EnumerationTypeNode&&) = default;

  ~EnumerationTypeNode() override = default;

  [[nodiscard]] const std::unique_ptr<std::vector<IdentifierNode*>>& getIdentifiers() const { return identifiers_; }

  void setIdentifiers(std::unique_ptr<std::vector<IdentifierNode*>> identifiers) { identifiers_ = std::move(identifiers); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    auto newIdentifiers = std::make_unique<std::vector<IdentifierNode*>>();
    for (const auto& identifier : *identifiers_) {
      newIdentifiers->push_back(dynamic_cast<IdentifierNode*>(identifier->clone().release()));
    }
    return std::make_unique<EnumerationTypeNode>(newIdentifiers.get());
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "EnumerationTypeNode:\n";
    for (const auto& identifier : *identifiers_) {
      identifier->print(out, tab + 2);
    }
  }

 private:
  std::unique_ptr<std::vector<IdentifierNode*>> identifiers_;
};

class ConstRangeTypeNode : public SimpleTypeNode {
 public:
  ConstRangeTypeNode() : SimpleTypeNode{CONST_RANGE} {}
  explicit ConstRangeTypeNode(ConstantNode* lowerBound, ConstantNode* upperBound)
      : SimpleTypeNode{CONST_RANGE}, lowerBound_{lowerBound}, upperBound_{upperBound} {}

  ConstRangeTypeNode(const ConstRangeTypeNode&) = delete;
  ConstRangeTypeNode(ConstRangeTypeNode&&) = default;

  ConstRangeTypeNode& operator=(const ConstRangeTypeNode&) = delete;
  ConstRangeTypeNode& operator=(ConstRangeTypeNode&&) = default;

  ~ConstRangeTypeNode() override = default;

  [[nodiscard]] const std::unique_ptr<ConstantNode>& getLowerBound() const { return lowerBound_; }
  [[nodiscard]] const std::unique_ptr<ConstantNode>& getUpperBound() const { return upperBound_; }

  void setLowerBound(std::unique_ptr<ConstantNode> lowerBound) { lowerBound_ = std::move(lowerBound); }
  void setUpperBound(std::unique_ptr<ConstantNode> upperBound) { upperBound_ = std::move(upperBound); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    ConstantNode* newLowerBound = dynamic_cast<ConstantNode*>(lowerBound_->clone().release());
    ConstantNode* newUpperBound = dynamic_cast<ConstantNode*>(upperBound_->clone().release());
    return std::make_unique<ConstRangeTypeNode>(newLowerBound, newUpperBound);
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "ConstRangeTypeNode:\n";
    lowerBound_->print(out, tab + 2);
    upperBound_->print(out, tab + 2);
  }

 private:
  std::unique_ptr<ConstantNode> lowerBound_;
  std::unique_ptr<ConstantNode> upperBound_;
};

class VarRangeTypeNode : public SimpleTypeNode {
 public:
  VarRangeTypeNode() : SimpleTypeNode{VAR_RANGE} {}
  explicit VarRangeTypeNode(IdentifierNode* lowerBound, IdentifierNode* upperBound)
      : SimpleTypeNode{VAR_RANGE}, lowerBound_{lowerBound}, upperBound_{upperBound} {}

  VarRangeTypeNode(const VarRangeTypeNode&) = delete;
  VarRangeTypeNode(VarRangeTypeNode&&) = default;

  VarRangeTypeNode& operator=(const VarRangeTypeNode&) = delete;
  VarRangeTypeNode& operator=(VarRangeTypeNode&&) = default;

  ~VarRangeTypeNode() override = default;

  [[nodiscard]] const std::unique_ptr<IdentifierNode>& getLowerBound() const { return lowerBound_; }
  [[nodiscard]] const std::unique_ptr<IdentifierNode>& getUpperBound() const { return upperBound_; }

  void setLowerBound(std::unique_ptr<IdentifierNode> lowerBound) { lowerBound_ = std::move(lowerBound); }
  void setUpperBound(std::unique_ptr<IdentifierNode> upperBound) { upperBound_ = std::move(upperBound); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    IdentifierNode* newLowerBound = dynamic_cast<IdentifierNode*>(lowerBound_->clone().release());
    IdentifierNode* newUpperBound = dynamic_cast<IdentifierNode*>(upperBound_->clone().release());
    return std::make_unique<VarRangeTypeNode>(newLowerBound, newUpperBound);
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "VarRangeTypeNode:\n";
    lowerBound_->print(out, tab + 2);
    upperBound_->print(out, tab + 2);
  }

 private:
  std::unique_ptr<IdentifierNode> lowerBound_;
  std::unique_ptr<IdentifierNode> upperBound_;
};
}  // namespace ast

#endif  // AST_SIMPLE_TYPE_NODE_HPP
