#include "call_node.hpp"

namespace ast {
// UserDefineCallNode
void UserDefineCallNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

[[nodiscard]] std::unique_ptr<AstNode> UserDefineCallNode::clone() const {
  IdentifierNode* newName = dynamic_cast<IdentifierNode*>(name_->clone().release());
  ArgumentsListNode* newArguments = dynamic_cast<ArgumentsListNode*>(arguments_->clone().release());

  return std::make_unique<UserDefineCallNode>(newName, newArguments);
}

void UserDefineCallNode::print(std::ostream& out, int tab) const {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "UserDefineCallNode with label: " << getLabel().value() << '\n';
  }
  else {
    out << std::string(tab, ' ') << "UserDefineCallNode\n";
  }

  name_->print(out, tab + 2);
  if (arguments_ != nullptr) {
    arguments_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "Arguments: nullptr\n";
  }
}

// BuiltinCallNode
void BuiltinCallNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

[[nodiscard]] std::unique_ptr<AstNode> BuiltinCallNode::clone() const {
  ArgumentsListNode* newArguments = dynamic_cast<ArgumentsListNode*>(arguments_->clone().release());

  return std::make_unique<BuiltinCallNode>(name_, newArguments);
}

void BuiltinCallNode::print(std::ostream& out, int tab) const {
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