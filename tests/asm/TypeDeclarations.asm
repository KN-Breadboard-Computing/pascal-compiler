ProgramNode TypeDeclarations:
  RoutineNode of type MAIN:
    RoutineHeadNode:
      Constants:
      Types:
        Type 0:
          IdentifierNode: TMyInt
          SimpleTypeNode INTEGER
        Type 1:
          IdentifierNode: TMyUInt
          SimpleTypeNode UNSIGNED
        Type 2:
          IdentifierNode: TMyChar
          SimpleTypeNode CHAR
        Type 3:
          IdentifierNode: TMyString
          SimpleTypeNode STRING
        Type 4:
          IdentifierNode: TMyBool
          SimpleTypeNode BOOLEAN
        Type 5:
          IdentifierNode: TMyReBool
          RenameTypeNode:
            IdentifierNode: TMyBool
        Type 6:
          IdentifierNode: TDay
          EnumerationTypeNode:
            IdentifierNode: Mon
            IdentifierNode: Tue
            IdentifierNode: Wed
            IdentifierNode: Thu
            IdentifierNode: Fri
            IdentifierNode: Sat
            IdentifierNode: Sun
        Type 7:
          IdentifierNode: TWorkDay
          VarRangeTypeNode:
            IdentifierNode: Mon
            IdentifierNode: Fri
        Type 8:
          IdentifierNode: TNumeric1
          ConstRangeTypeNode:
            ConstantInteger<1>
            ConstantInteger<111>
        Type 9:
          IdentifierNode: TNumeric2
          ConstRangeTypeNode:
            ConstantInteger<-17>
            ConstantInteger<17>
        Type 10:
          IdentifierNode: TNumeric3
          ConstRangeTypeNode:
            ConstantInteger<-10>
            ConstantInteger<-5>
        Type 11:
          IdentifierNode: TNumeric4
          ConstRangeTypeNode:
            ConstantInteger<0>
            ConstantInteger<255>
        Type 12:
          IdentifierNode: TNumeric5
          ConstRangeTypeNode:
            ConstantInteger<-255>
            ConstantInteger<0>
        Type 13:
          IdentifierNode: TNumeric5
          ConstRangeTypeNode:
            ConstantInteger<-255>
            ConstantInteger<255>
        Type 14:
          IdentifierNode: TBools
          ConstRangeTypeNode:
            ConstantBoolean<0>
            ConstantBoolean<1>
        Type 15:
          IdentifierNode: TLetters
          ConstRangeTypeNode:
            ConstantChar<a>
            ConstantChar<z>
        Type 16:
          IdentifierNode: TMyIntArray
          ArrayTypeNode:
            Range:
              ConstRangeTypeNode:
                ConstantInteger<1>
                ConstantInteger<10>
            Element type:
              SimpleTypeNode INTEGER
      Variables:
      Routines:
    RoutineBodyNode:
      CompoundStatementNode:
