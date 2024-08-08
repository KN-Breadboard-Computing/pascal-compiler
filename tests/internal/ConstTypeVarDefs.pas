program ConstTypeVarDefs;

const
  c1 = 11;
  c2 = -7;
  c3 = 'A';
  c4 = TRUE;
  c5 = FALSE;
  c6 = MAXINT;
  c7 = -MAXINT;
  c8 = 'Hello';
  c3 = 5;

type
  IntRenamed = integer;
  IntRenamed2 = IntRenamed;
  IntRenamed3 = IntRenamed2;

  TNumeric1 = 1..111;
  TNumeric2 = -17..19;
  TNumeric3 = 0..MaxInt;
  TBools = False..True;
  TLetters = 'a'..'z';

  TDay = (Mon, Tue, Wed, Thu, Fri, Sat, Sun);
  TDay2 = (Mon, Tue, Wed, Thu, Fri);
  TWorkDay = Mon..Fri;
  TWeekend = Sat..Sum;

  TArray = array[1..10] of integer;
  TMatrix = array[1..10] of array[1..10] of integer;
  TMatrix2 = array[1..10] of TArray;

  TArrayIntIndex = array[integer] of integer;
  TArrayLetterIndex = array['a'..'z'] of integer;
  TArrayBoolIndex = array[TBools] of integer;
  TArrayDayIndex = array[TWeekend] of integer;

  TRenamedArray = TArray;

  TPerson = record
    Name, Surname: Char;
    Age: Integer;
    WorkHours: array[TDay] of Integer;
  end;

  TFamiliy = record
    Father: TPerson;
    Mother: TPerson;
    Children: array[1..10] of TPerson;
  end;

  TFamilyRenamed = TFamiliy;

  TDay = record
    x: integer;
  end;
var
  x,y,z: integer;
  a: boolean;
  c,d: char;
  b: unsigned;
  y,c8: integer;
  family: TFamiliy;

begin

end.