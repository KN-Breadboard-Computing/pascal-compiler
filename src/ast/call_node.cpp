#include "call_node.hpp"

namespace ast {
// UserDefineCallNode
virtual void UserDefineCallNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> UserDefineCallNode::clone() const override {
  IdentifierNode* newName = dynamic_cast<IdentifierNode*>(name_->clone().release());
  ArgumentsListNode* newArguments = dynamic_cast<ArgumentsListNode*>(arguments_->clone().release());

  return std::make_unique<UserDefineCallNode>(newName, newArguments);
}

virtual void UserDefineCallNode::print(std::ostream& out, int tab) const override {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "UserDefineCallNode with label: " << getLabel().value() << '\n';
  }
  else {
    out << std::string(tab, ' ') << "UserDefineCallNode\n";
  }

  name_->print(out, tab + 2);
  arguments_->print(out, tab + 2);
}


// BuiltinCallNode
virtual void BuiltinCallNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> BuiltinCallNode::clone() const override {
  ArgumentsListNode* newArguments = dynamic_cast<ArgumentsListNode*>(arguments_->clone().release());

  return std::make_unique<BuiltinCallNode>(name_, newArguments);
}

virtual void BuiltinCallNode::print(std::ostream& out, int tab) const override {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "BuiltinCallNode with label: " << getLabel().value() << ": ";
  }
  else {
    out << std::string(tab, ' ') << "BuiltinCallNode: ";
  }

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
    case MEMORY_READ:
      out << "MEMORY_READ\n";
      break;
    case MEMORY_WRITE:
      out << "MEMORY_WRITE\n";
      break;
    case STACK_READ:
      out << "STACK_READ\n";
      break;
    case STACK_WRITE:
      out << "STACK_WRITE\n";
      break;
  }
  if (arguments_ != nullptr) {
    arguments_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "Arguments: nullptr\n";
  }
}
}  // namespace ast