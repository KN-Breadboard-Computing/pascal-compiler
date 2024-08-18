program ForIndexReassignment;

var
  a, b: integer;
begin
  for i := 1 to 10 do
  begin
    a := i;
    while a < 10 do
    begin
      a := a + 1;
      i := a;
    end;
  end;
end.