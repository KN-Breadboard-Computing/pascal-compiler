program LValuesTypes;

type
    TArray = array[boolean] of integer;
    TMatrix = array[1..10] of array[1..10] of integer;

    TDay = (Mon, Tue, Wed, Thu, Fri, Sat, Sun);
    TWeekend = Sat..Sun;

    TPerson = record
        Name, Surname: Char;
        Age: Integer;
        WorkHours: array[TDay] of Integer;
        FamilyTime: array[TWeekend] of Integer;
      end;

      TFamily = record
        Father: TPerson;
        Mother: TPerson;
        Children: array[1..10] of TPerson;
      end;
var
    x: integer;
    arr: TArray;
    mat: TMatrix;
    per: TPerson;
    fam: TFamily;
begin
    Read(x);
    Read(arr[true or false]);
    Read(mat[4][2]);
    Read(mat[x][3]);
    Read(per.Age);
    Read(per.WorkHours[Sun]);
    Read(fam.Mother.Name);
    Read(fam.Children[0].Surname);
    Read(fam.Children[0].WorkHours[Mon]);
    Read(mat[fam.Children[0].WorkHours[Fri]][1]);
    Read(fam.Children[0].FamilyTime[Sat]);
end.