program Routines;

type
  TPerson = record
    Name: array[1..50] of String;
    Age: Integer;
  end;

var
  num1, num2, result: Integer;
  person: TPerson;

function Add(a, b: Integer): Integer;

  function Increment(x: Integer): Integer;
  begin
    Increment := x + 1;
  end;

begin
  Add := Increment(a) + Increment(b);
end;

procedure Increment(var a: Integer);
begin
  a := a + 1;
end;

function GetFullName(person: TPerson): string;
begin
  GetFullName := 'Full Name: ' + person.Name;
end;

procedure SetPersonAge(var person: TPerson; newAge: Integer);

  procedure ValidateAge(var age: Integer);
  begin
    if age < 0 then
      age := 0;
  end;

begin
  ValidateAge(newAge);
  person.Age := newAge;
end;

begin
  num1 := 5;
  num2 := 10;
  result := Add(num1, num2);
  WriteLn('Add(', num1, ', ', num2, ') = ', result);

  Increment(num1);
  WriteLn('After Increment, num1 = ', num1);

  person.Name := 'Alice';
  person.Age := 25;

  WriteLn(GetFullName(person));

  SetPersonAge(person, 30);
  WriteLn('After SetAge, ', person.Name, ' is ', person.Age, ' years old.');
end.

