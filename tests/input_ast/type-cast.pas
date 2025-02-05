program TypeCast;

var
  i: Integer;
  c: Char;
  b: Boolean;

begin
  i := 65;
  c := 'A';
  b := True;

  i := ToInt(i);
  i := ToInt(c);
  i := ToInt(b);

  c := ToChar(i);
  c := ToChar(c);
  c := ToChar(b);

  b := ToBool(i);
  b := ToBool(c);
  b := ToBool(b);
end.