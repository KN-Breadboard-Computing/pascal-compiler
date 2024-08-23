# Pascal Compiler For Our 8-bit Computer
This is compiler which can translate Pascal code to instruction set of 8-bit computer.

# Compile And Run
This project can run on Linux, make sure you have flex and bison. If you do not have them, install them.

Then compile the project with the `make` command.

# Supported Pascal Syntax
The `tests/examples` directory contains examples showing the syntax described below.

## Identifiers
+ Pascal is case insensitive.
+ must begin with letter(a-zA-z) or underscore(_).
+ following chars can be letters(a-zA-Z), digits(0-9) or underscore(_) in any combination.

## Math Operators
+ \+ - addition
+ \- - subtraction / unary negative
+ \* - multiplication
+ / - integer division
+ \% - modulo

## Boolean Operators
+ NOT - logical negation
+ AND - logical conjunction
+ OR - logical alternation
+ < -	less than
+ \>	- greater than
+ =	- equal to
+ <= - less than or equal to
+ \>= - greater than or equal to
+ <> - not equal to

## Built-in Functions
```
Read(Variable);
Readln;
```

```
Write(Expression, ..., Expression);
Writeln(Expression, ..., Expression);
Writeln;
```

```
AbsoluteValue := Abs(Value);
```

```
IntValue := Ord('A');
CharValue := Chr(65);
```

```
NplusOne := Succ(N);
NminusOne := Pred(N);
```

```
BooleanValue := Odd(IntValue);
```

```
MemoryRead(AddressHigh, AddressLow, DestinationVariable);
MemoryWrite(AddressHigh, AddressLow, SourceVariable);

StackRead(AddressHigh, AddressLow, DestinationVariable);
StackWrite(AddressHigh, AddressLow, SourceVariable);
```

```
IntValue = ToInt(BasicTypeValue);
CharValue = ToChar(BasicTypeValue);
BooleanValue = ToBool(BasicTypeValue);
```

## Program Structure
```
PROGRAM ProgramName;

CONST
  (* Constant declarations *)

TYPE
  (* Type declarations *)

VAR
  (* Global variable declarations *)

(* Procedure/function definitions *)

BEGIN
  (* Executable statements *)
END.
```

## Procedures & Functions
```
PROCEDURE Name (FormalParameterList);

CONST
  (* Constants *)

TYPE
  (* Types *)

VAR
  (* Variables *)

(* SubProcedure/SubFunction definitions *)


BEGIN
  (* Statements *)
END;
```
```
FUNCTION Name (FormalParameterList) : ReturnType;

CONST
  (* Constants *)

TYPE
  (* Types *)

VAR
  (* Variables *)

(* SubProcedure/SubFunction definitions *)

BEGIN
  (* Statements *)

  Name := (* Function result *)
END;
```
```
FormalParameterList = ParameterGroup1; ... ; ParameterGroupn
```
```
ParameterGroupk = Identifier1, ... Identifiern : DataType         (* pass arguments by value *)
ParameterGroupk = VAR Identifier1, ... Identifiern : DataType     (* pass arguments by reference *)
```


## Statements
### Assignment
```
VariableName := Expression;
```

### If
```
IF BooleanExpression THEN
  StatementIfTrue;
```
```
IF BooleanExpression THEN
  StatementIfTrue
ELSE
  StatementIfFalse;
```
```
IF BooleanExpression THEN
BEGIN
  StatementIfTrue1;
  StatementIfTrue2;
END;
```
```
IF BooleanExpression THEN
BEGIN
  StatementIfTrue1;
  StatementIfTrue2;
END
ELSE
BEGIN
  StatementIfFalse1;
  StatementIfFalse2;
EBD;
```

### Case 
```
CASE Selector OF
  Value1:     Statement1;
  Value2:     Statement2;
  ...
  Valuen:     Statementn;
  OTHERWISE   OtherwiseStatement;   (* optional *)
END;
```

### For Loop
`Index` cannot be changed inside the loop. 
A loop can be interrupted using the `break` statement. Iteration can be skipped using `continue`.
```
FOR Index := StartingLow TO EndingHigh DO
  Statement;
```
```
FOR Index := StartingHigh DOWNTO EndingLow DO
  Statement;
```
```
FOR Index := StartingLow TO EndingHigh DO
BEGIN
  Statement1;
  Statement2;
END;
```
```
FOR Index := StartingHigh DOWNTO EndingLow DO
BEGIN
  Statement1;
  Statement2;
END;
```

### While Loop
A loop can be interrupted using the `break` statement. Iteration can be skipped using `continue`.
```
WHILE BooleanExpression DO
  Statement;
```
```
WHILE BooleanExpression DO
BEGIN
  Statement1;
  Statement2;
END;
```

### Repeat Until Loop
A loop can be interrupted using the `break` statement. Iteration can be skipped using `continue`.
```
repeat
  Statement1;
  Statement2;
until BooleanExpression;
```

### Goto - disabled
```
GOTO Label;
.
.
.
Label: Statement
```

## Comments
Each of these comments is multiline.
```
(* Comment *)
```
```
{ Comment }
```

## Data Types

### Basic Data Types
+ Bool $\in$ {TRUE, FALSE}
+ Char $\in$ [0, 255] (represent ASCII codes)
+ Integer $\in$ [-128, 127] / [0, 255] (2's complement)

### Constants
```
  ConstInt = -19;
  ConstUInt = 28;
  ConstChar = 'P';
  ConstString = 'Hello, World!';
  ConstTrue = TRUE;
  ConstFalse = FALSE;
  ConstMaxInt = MAXINT;
```

### Type Renaming
```
TIntTypeRename = Integer;
```

### Enumeration
```
TDay = (Mon, Tue, Wed, Thu, Fri, Sat, Sun);
```

### Enumeration Range
```
TWorkDay = Mon..Fri;
```

### Subranges
```
TNumeric1 = 1..111;
TNumeric2 = -17..19;
TNumeric3 = 0..MaxInt;
TBools = False..True;
TLetters = 'a'..'z';
```

### Arrays
```
TIntArray = array[1..10] of Integer;
TIntMatrix = array[1..10] of TIntArray;
TCharMatrix = array[1..10] of array[1..10] of Char;

TCharArrayBoolIndex = array[Boolean] of Char;
TCharArrayCharIndex = array[Char] of Char;
TCharArrayIntIndex = array[Integer] of Char;
TCharArrayUIntIndex = array[Unsigned] of Char;

TCharArrayCharRange = array['a'..'z'] of Char;
TCharArrayBoolsRange = array[TBools] of Char;

TIntLettersIndex = array['hello'] of Integer;

TWeekDayArray = array[TDay] of Integer;
```

### Array Access
```
ArrayElement := ArrayName[IndexExppression];
```

### Char Array Assign
```
CharsArray = array[1..5] of Char;
CharsArray = 'Hello';
```

### Record
```
  TPerson = record
    Name, Surname: Char;
    Age: Integer;
    WorkHours: array[TDay] of Integer;
  end;

  TFamily = record
    Father: TPerson;
    Mother: TPerson;
    Children: array[1..10] of TPerson;
  end;
```

### Record Access
```
RecordField := RecordName.FieldName;
```