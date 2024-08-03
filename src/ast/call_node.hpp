#ifndef AST_CALL_NODE_HPP
#define AST_CALL_NODE_HPP

#include <memory>

#include "arguments_list_node.hpp"
#include "expression_node.hpp"
#include "identifier_node.hpp"
#include "statement_node.hpp"

namespace ast {
class CallNode : public StatementNode {
 public:
  enum CallObjectType { USER_DEFINED, BUILTIN };

  CallNode() : StatementNode{} { type_ = Type::CALL; }
  explicit CallNode(CallObjectType callObjectType) : StatementNode{}, callObjectType_{callObjectType} {}

  CallNode(const CallNode&) = delete;
  CallNode(CallNode&&) = default;

  CallNode& operator=(const CallNode&) = delete;
  CallNode& operator=(CallNode&&) = default;

  ~CallNode() override = default;

  [[nodiscard]] CallObjectType getCallObjectType() const { return callObjectType_; }

  void setCallObjectType(CallObjectType callObjectType) { callObjectType_ = callObjectType; }

 private:
  CallObjectType callObjectType_;
};

class UserDefineCallNode : public CallNode {
 public:
  UserDefineCallNode() : CallNode{USER_DEFINED} {}
  UserDefineCallNode(IdentifierNode* name, ArgumentsListNode* arguments)
      : CallNode{USER_DEFINED}, name_{name}, arguments_{std::move(arguments)} {}

  UserDefineCallNode(const UserDefineCallNode&) = delete;
  UserDefineCallNode(UserDefineCallNode&&) = default;

  UserDefineCallNode& operator=(const UserDefineCallNode&) = delete;
  UserDefineCallNode& operator=(UserDefineCallNode&&) = default;

  ~UserDefineCallNode() override = default;

  [[nodiscard]] const std::unique_ptr<IdentifierNode>& getName() const { return name_; }
  [[nodiscard]] const std::unique_ptr<ArgumentsListNode>& getArguments() const { return arguments_; }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    IdentifierNode* newName = dynamic_cast<IdentifierNode*>(name_->clone().release());
    ArgumentsListNode* newArguments = dynamic_cast<ArgumentsListNode*>(arguments_->clone().release());

    return std::make_unique<UserDefineCallNode>(newName, newArguments);
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "UserDefineCallNode\n";
    name_->print(out, tab + 2);
    arguments_->print(out, tab + 2);
  }

 private:
  std::unique_ptr<IdentifierNode> name_;
  std::unique_ptr<ArgumentsListNode> arguments_;
};

class BuiltinCallNode : public CallNode {
 public:
  enum FunctionName { READ, READLN, WRITE, WRITELN };

  BuiltinCallNode() : CallNode{BUILTIN} {}
  BuiltinCallNode(FunctionName name, ArgumentsListNode* arguments)
      : CallNode{BUILTIN}, name_{name}, arguments_{std::move(arguments)} {}

  BuiltinCallNode(const BuiltinCallNode&) = delete;
  BuiltinCallNode(BuiltinCallNode&&) = default;

  BuiltinCallNode& operator=(const BuiltinCallNode&) = delete;
  BuiltinCallNode& operator=(BuiltinCallNode&&) = default;

  ~BuiltinCallNode() override = default;

  [[nodiscard]] FunctionName getName() const { return name_; }
  [[nodiscard]] const std::unique_ptr<ArgumentsListNode>& getArguments() const { return arguments_; }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    ArgumentsListNode* newArguments = dynamic_cast<ArgumentsListNode*>(arguments_->clone().release());

    return std::make_unique<BuiltinCallNode>(name_, newArguments);
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "BuiltinCallNode ";
    switch (name_) {
      case READ:
        out << "READ\n";
        break;
      case READLN:
        out << "READLN\n";
        break;
      case WRITE:
        out << "WRITE\n";
        break;
      case WRITELN:
        out << "WRITELN\n";
        break;
    }
    if (arguments_ != nullptr) {
      arguments_->print(out, tab + 2);
    }
    else {
      out << std::string(tab + 2, ' ') << "Arguments: nullptr\n";
    }
  }

 private:
  FunctionName name_;
  std::unique_ptr<ArgumentsListNode> arguments_;
};
}  // namespace ast

#endif  // AST_CALL_NODE_HPP
