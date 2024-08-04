program RepeatsUntil;

var
  i, j: integer;

begin
  i := 1;

  repeat
    j := 1;
    repeat
      writeln(i, ' * ', j, ' = ', i * j);
      j := j + 1;
    until j > 5;

    writeln;
    i := i + 1;
  until i > 5;

  readln;  {Wait for the user to press Enter}
end.