ProgramNode HelloWorld:
  RoutineNode of type MAIN:
    RoutineHeadNode:
      Constants:
      Types:
      Variables:
        Identifiers:
          IdentifierNode: name
          IdentifierNode: surname
        Type:         TypeNode:
          TypeType: 1
      Routines:
    RoutineBodyNode:
      CompoundStatementNode:
        BuiltinCallNode
          Name: WRITE
          ArgumentsListNode:
            SpecialExpressionNode: 3
              ConstantString<Hello, World! >
        BuiltinCallNode
          Name: WRITELN
          Arguments: nullptr
        BuiltinCallNode
          Name: WRITELN
          ArgumentsListNode:
            SpecialExpressionNode: 3
              ConstantString<What is your name?>
        BuiltinCallNode
          Name: READ
          ArgumentsListNode:
            SpecialExpressionNode: 0
              IdentifierNode: name
        BuiltinCallNode
          Name: WRITELN
          ArgumentsListNode:
            SpecialExpressionNode: 3
              ConstantString<What is your surname?>
        BuiltinCallNode
          Name: READ
          ArgumentsListNode:
            SpecialExpressionNode: 0
              IdentifierNode: surname
        BuiltinCallNode
          Name: WRITELN
          ArgumentsListNode:
            SpecialExpressionNode: 3
              ConstantString<Hello, >
            SpecialExpressionNode: 0
              IdentifierNode: name
            SpecialExpressionNode: 3
              ConstantChar< >
            SpecialExpressionNode: 0
              IdentifierNode: surname
            SpecialExpressionNode: 3
              ConstantChar<!>
        BuiltinCallNode
          Name: READLN
          Arguments: nullptr
