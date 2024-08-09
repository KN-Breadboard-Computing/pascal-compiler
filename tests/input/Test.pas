program Test;

type
  TArray = array[1..10] of Integer;
  TMatrix = array[1..10] of array[1..10] of Integer;

  TDay = (Mon, Tue, Wed, Thu, Fri, Sat, Sun);

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

var
  IntVar: Integer;
  UIntVar: Integer;
  CharVar: Char;
  BoolVar: Boolean;

  IndexVar: Integer;

  ArrayVar: TArray;
  MatrixVar: TMatrix;
  DayVar: TDay;
  PersonVar: TPerson;
  FamilyVar: TFamily;

begin
  ReadLn;

  Read(IntVar);
  Read(UIntVar);
  Read(CharVar);
  Read(BoolVar);
  Read(UndefVar);

  IndexVar := 5;

  Read(ArrayVar[0]);
  Read(ArrayVar[IndexVar]);
  Read(MatrixVar[3][IndexVar]);
  Read(MatrixVar[9-7][IndexVar + 1]);
end.