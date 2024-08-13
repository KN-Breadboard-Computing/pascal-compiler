program LValuesTypes;

type
    TArray = array[1..10] of integer;
    TMatrix = array[1..10] of array[1..10] of integer;

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
    x: integer;
    arr: TArray;
    mat: TMatrix;
    per: TPerson;
    fam: TFamily;
begin
    Read(x);
    Read(arr[6]);
    Read(mat[4][2]);
    Read(per.Age);
    Read(per.WorkHours[3]);
    Read(fam.Mother.Name);
    Read(fam.Children[0].Surname);
    Read(fam.Children[0].WorkHours[1]);
end.