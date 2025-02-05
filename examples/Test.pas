program Test;

type
    TArray = array[1..10] of integer;
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
    Read(arr[2]);
    Read(mat[4][x]);
    Read(per.Age);
    Read(per.WorkHours[Wed]);
    Read(fam.Name.Ndame);
    Read(fam.Children[0].Surname);
    Read(fam.Children[0].WorkHours[Mon]);
    Read(fam.Children[0].FamilyTime[Sun]);
end.