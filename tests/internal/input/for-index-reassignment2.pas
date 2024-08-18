program ForIndexReassignment;

var
  a, b: integer;

procedure Fun1(x: integer; i: integer);
begin
  WriteLn(i);
end;

function Fun2(x: integer; var i: integer; var y: integer): boolean;
begin
  i := i * 2;
  Fun2 := i > 10;
end;
begin
  for i := 1 to 10 do
  begin
    if Fun2(2, i, 3) then
    begin
      WriteLn('Fun2 returned true');
    end;
  end;
end.