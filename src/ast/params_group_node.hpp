#ifndef AST_PARAMS_GROUP_NODE_HPP
#define AST_PARAMS_GROUP_NODE_HPP

#include <memory>

#include "ast_node.hpp"
#include "identifier_node.hpp"
#include "simple_type_node.hpp"

namespace ast {
class ParamsGroupNode : public AstNode {
 public:
  enum PassType { UNSPECIFIED, PASS_BY_VALUE, PASS_BY_REFERENCE };

  ParamsGroupNode() : AstNode(Type::PARAMS_GROUP), passType_{PassType::UNSPECIFIED} {}
  ParamsGroupNode(PassType passType, std::vector<IdentifierNode*>* params, SimpleTypeNode* paramsType)
      : AstNode{Type::PARAMS_GROUP}, passType_{passType}, params_{params}, paramsType_{paramsType} {}

  ParamsGroupNode(const ParamsGroupNode&) = delete;
  ParamsGroupNode(ParamsGroupNode&&) = default;

  ParamsGroupNode& operator=(const ParamsGroupNode&) = delete;
  ParamsGroupNode& operator=(ParamsGroupNode&&) = default;

  ~ParamsGroupNode() override = default;

  [[nodiscard]] PassType getPassType() const { return passType_; }
  [[nodiscard]] const std::unique_ptr<std::vector<IdentifierNode*>>& getParams() const { return params_; }
  [[nodiscard]] const std::unique_ptr<SimpleTypeNode>& getParamsType() const { return paramsType_; }

  void setPassType(PassType passType) { passType_ = passType; }
  void setParams(std::unique_ptr<std::vector<IdentifierNode*>> params) { params_ = std::move(params); }
  void setParamsType(std::unique_ptr<SimpleTypeNode> paramsType) { paramsType_ = std::move(paramsType); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    auto clone = std::make_unique<ParamsGroupNode>();
    clone->setPassType(passType_);
    clone->setParamsType(std::unique_ptr<SimpleTypeNode>(dynamic_cast<SimpleTypeNode*>(paramsType_->clone().release())));

    std::vector<IdentifierNode*> params;
    for (const auto& param : *params_) {
      params.push_back(dynamic_cast<IdentifierNode*>(param->clone().release()));
    }
    clone->setParams(std::make_unique<std::vector<IdentifierNode*>>(std::move(params)));

    return clone;
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "ParamsGroupNode:\n";
    out << std::string(tab + 2, ' ') << "PassType: ";
    switch (passType_) {
      case PassType::UNSPECIFIED:
        out << "UNSPECIFIED\n";
        break;
      case PassType::PASS_BY_VALUE:
        out << "PASS_BY_VALUE\n";
        break;
      case PassType::PASS_BY_REFERENCE:
        out << "PASS_BY_REFERENCE\n";
        break;
    }
    out << std::string(tab + 2, ' ') << "ParamsType: ";
    paramsType_->print(out, tab + 4);
    out << std::string(tab + 2, ' ') << "Params:\n";
    for (const auto& param : *params_) {
      param->print(out, tab + 4);
    }
  }

 private:
  PassType passType_;
  std::unique_ptr<std::vector<IdentifierNode*>> params_;
  std::unique_ptr<SimpleTypeNode> paramsType_;
};
}  // namespace ast

#endif  // AST_PARAMS_GROUP_NODE_HPP
