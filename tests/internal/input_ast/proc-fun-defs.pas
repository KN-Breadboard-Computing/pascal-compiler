program ProcFunDefs;

const
  UpperToLower = 32;

type
  Str = array[1..20] of Char;

  TPerson = record
    Name, Surname: Str;
    Age: Integer;
  end;

var
  family: array[1..3] of TPerson;

procedure ReadPerson(var p: TPerson);
  procedure ToLower(var s: Str);
    function Add(a, b: Integer): Integer;
    begin
      Add := a + b;
    end;
  begin
    for i := 1 to 20 do
      s[i] := Chr(Add(Ord(s[i]) + UpperToLower));
  end;
begin
  writeln('Enter name: ');
  for i := 1 to 20 do
    read(p.Name[i]);
  ToLower(p.Name);
  writeln('Enter surname: ');
  for i := 1 to 20 do
    read(p.Surname[i]);
  ToLower(p.Surname);
  writeln('Enter age: ');
  read(p.Age);
end;

procedure UpdatePerson(var p: TPerson);
  function Add(a, b: Integer): Integer;
  begin
    Add := a + b;
  end;
begin
  p.Age := Add(p.Age, 1);
end;

function GetPersonName(var p: TPerson): Str;
begin
  GetPersonName := p.Name;
end;

procedure PrintPerson(p: TPerson);
begin
  writeln('Name First Letter: ', p.Name[0]);
  writeln('Surname First Letter: ', p.Surname[0]);
  writeln('Age: ', p.Age);
end;

begin
  for i := 1 to 3 do
  begin
    ReadPerson(family[i]);
    UpdatePerson(family[i]);
  end;

  for i := 1 to 3 do
    PrintPerson(family[i]);
end.