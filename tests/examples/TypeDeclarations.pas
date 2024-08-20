program TypeDeclarations;

type
(* Simple type redeclaration *)
  TMyInt = Integer;
  TMyUInt = Unsigned;
  TMyChar = Char;
  TMyChar = Char;
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

  TMyCharArrayBoolIndex = array[Boolean] of Char;
  TMyCharArrayCharIndex = array[Char] of Char;
  TMyCharArrayIntIndex = array[Integer] of Char;
  TMyCharArrayUIntIndex = array[Unsigned] of Char;

  TMyCharArrayCharRange = array['a'..'z'] of Char;
  TMyCharArrayBoolsRange = array[TBools] of Char;

  TMyWeekDayArray = array[TDay] of Char;

(* Record type *)
  TPerson = record
    Name: Char;
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