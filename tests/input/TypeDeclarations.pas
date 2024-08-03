program TypeDeclarations;

type
(* Simple type redeclaration *)
  TMyInt = Integer;
  TMyUInt = Unsigned;
  TMyChar = Char;
  TMyString = String;
  TMyBool = Boolean;
  TMyReBool = TMyBool;

(* Enumeration list and enum range *)
  TDay = (Mon, Tue, Wed, Thu, Fri, Sat, Sun);
  TWorkDay = Mon..Fri;

(* Subrange type *)
  TNumeric1 = 1..111;
  TNumeric2 = -17..17;
  TNumeric3 = -10..-5;
  TNumeric4 = 0..MaxInt;
  TNumeric5 = -MaxInt..0;
  TNumeric5 = -MaxInt..MaxInt;
  TBools = False..True;
  TLetters = 'a'..'z';

(* Array type *)
  TMyIntArray = array[1..10] of Integer;
  TMyIntMatrix = array[1..10] of TMyIntArray;
  TMyCharMatrix = array[1..10] of array[1..10] of Char;

  TMyStringArrayBoolIndex = array[Boolean] of String;
  TMyStringArrayCharIndex = array[Char] of String;
  TMyStringArrayIntIndex = array[Integer] of String;
  TMyStringArrayUIntIndex = array[Unsigned] of String;

  TMyStringArrayCharRange = array['a'..'z'] of String;
  TMyStringArrayBoolsRange = array[TBools] of String;

  TMyWeekDayArray = array[TDay] of Char;

(* Record type *)
  TPerson = record
    Name: String;
    Age: Integer;
    WorkHours: array[TDay] of Integer;
  end;

  TFamiliy = record
    Father: TPerson;
    Mother: TPerson;
    Children: array[1..10] of TPerson;
  end;
begin

end.