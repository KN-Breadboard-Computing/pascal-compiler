# Pascal Compiler For Our 8-bit Computer
This is compiler which can translate Pascal code to instruction set of 8-bit computer.

# Compile And Run
This project can run on Linux, make sure you have flex and bison. If you do not have them, install them.

Then compile the project with the `make` command.

# Supported Pascal Syntax
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
procedure Name (FormalParameterList);

const
  (* Constants *)

var
  (* Variables *)

begin
  (* Statements *)
end;
```
```
function Name (FormalParameterList) : ReturnType;

const
  (* Constants *)

var
  (* Variables *)

begin
  (* Statements *)
end;
```
```
FormalParameterList = ParameterGroup1; ... ; ParameterGroupn
```
```
ParameterGroupk = Identifier1, ... Identifiern : DataType 
```

### Forward Referencing
```
procedure Later (parameter list); forward;

procedure Sooner (parameter list);
begin
  ...
  Later (parameter list);
end;

...

procedure Later;
begin
  ...
  Sooner (parameter list);
end;
```


## Statements
### Assignment
```
VariableName := Expression;
```

### If
```
if BooleanExpression then
  StatementIfTrue;
```
```
if BooleanExpression then
  StatementIfTrue
else
  StatementIfFalse;
```
```
if BooleanExpression then
begin
  Statement1;
  Statement2;
end;
```
```
if BooleanExpression then
begin
  Statement1;
  Statement2;
end
else
begin
  Statement3;
  Statement4;
end;
```

### Case 
```
case selector of
  List1:    Statement1;
  List2:    Statement2;
  ...
  Listn:    Statementn;
  otherwise Statement   // optional
end;
```

### For Loop
Index cannot be changed inside the loop. 
A loop can be interrupted using the `break` statement.
```
for Index := StartingLow to EndingHigh do
  Statement;
```
```
for Index := StartingHigh downto EndingLow do
  Statement;
```
```
for Index := StartingLow to EndingHigh do
begin
  Statement1;
  Statement2;
end;
```
```
for Index := StartingHigh downto EndingLow d
begin
  Statement1;
  Statement2;
end;
```

### While Loop
A loop can be interrupted using the `break` statement.
```
while BooleanExpression do
  Statement;
```
```
while BooleanExpression do
begin
  Statement1;
  Statement2;
end;
```

### Repeat Until Loop
A loop can be interrupted using the `break` statement.
```
repeat
  Statement1;
  Statement2;
until BooleanExpression;
```

## Comments
```
(* Comment *)
```
```
{ Comment }
```

## Data Types
### Declaring Custom Data Type
```
type
 DataTypeIdentifier = TypeSpecification;
```

### Enumeration Type
```
type
 DataTypeIdentifier = (Identifier1, ... Identifiern);
```
You can assign value to enumeration. For example:
```
type
 DataTypeIdentifier = (Identifier1=4, Identifier2, Identifier3=7);
```

### 1-Dimensional Array
```
type
  typename = array [EnumeratedType] of DataType;
```

For example - two equivalent definitions:
```
type
  EnumType = 1..50;
  ArrayType = array [EnumType] of char;

type
  ArrayType = array [1..50] of char;
```

### Multidimensional Array
```
type
  ArrayType = array [EnumType1, EnumType2] of DataType;
```

### Record
```
type
  TypeName = record
    IdentifierList1 : DataType1;
    ...
    IdentifierListn : DataTypen;
  end;
```

### Pointer
#### Type Creating
```
type
	PointerType = ^DataType;
```
#### Allocating Memory For Variable
```
New(PointerVariable);
```

#### Accessing Variable
```
PointerVariable^ := 5;
```

#### Deallocating Memory
```
Dispose(PointerVariable);
```

## Identifiers
+ Pascal is case insensitive.
+ must begin with letter(a-zA-z) or underscore(_).
+ following chars can be letters(a-zA-Z), digits(0-9) or underscore(_) in any combination.

## Basic data types
+ Bool $\in$ {TRUE, FALSE}
+ Char $\in$ [0, 255] (represent ASCII codes)
+ Short $\in$ [-128, 127]
+ Byte $\in$ [0, 255]

## Math Operators
+ \+ - addition / unary positive
+ \- - subtraction / unary negative
+ \* - multiplication
+ / - integer division
+ \% - modulo

## Boolean Operators
+ not - logical negation
+ and - logical conjunction
+ or - logical alternation
+ xor - exclusive alternation
+ < -	less than
+ \>	- greater than
+ =	- equal to
+ <= - less than or equal to
+ \>= - greater than or equal to
+ <> - not equal to