program Whiles;

var
  counter: integer;
  i, j: integer;

begin
  counter := 0;
  while counter <= 5 do
    counter := counter + 1;

  counter := 0;
  while count <= 5 do
  begin
    writeln('Count is: ', count);
    count := count + 1;
  end;

  i := 1;

  while i <= 3 do
  begin
    j := 1;
    while j <= 3 do
    begin
      writeln(i, ' * ', j, ' = ', i * j);
      j := j + 1;
    end;
    writeln;  {Print a blank line for better readability}
    i := i + 1;
  end;

  writeln('Multiplication table is complete.');
  readln;

end.