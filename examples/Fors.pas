program Fors;

var
  sum: Integer;

begin

  for i := 1 to 5 do
  begin
    for j := 1 to 5 do
    begin
      writeln(i, ' * ', j, ' = ', i * j);
    end;
    writeln;
  end;

  writeln('Multiplication table is complete.');

  sum := 0;
  for count := 1 to 100 do
    sum := sum + count;

  sum := 0;
  for count := 1 to 100 do
  begin
    sum := sum + count;
    if count = 2 then continue;
    if sum = 34 then break;
  end;

end.