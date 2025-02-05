program Types;

type
  TDay = (Mon, Tue, Wed, Thu, Fri, Sat, Sun);

  TPerson = record
    Name, Surname: Char;
    Age: Integer;
    IsHired: Boolean;
    WorkHours: array[TDay] of Integer;
  end;

  TFamily = record
    Father: TPerson;
    Mother: TPerson;
    Children: array[1..10] of TPerson;
  end;

  DaysArray = array[Wed..Sun] of TDay;

  FamiliesArray = array[TDay] of TFamily;

  XInt = Integer;

  IntIndexArray = array[Integer] of XInt;
  CharIndexArray = array[Char] of XInt;
  BoolIndexArray = array[Boolean] of XInt;
  BoolRangeIndexArray = array[false..true] of XInt;

begin

end.