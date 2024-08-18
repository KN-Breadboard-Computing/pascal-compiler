program Repeats;

var
  i, j: Integer;

begin
  i := 1;

  repeat
    j := 1;
    repeat
      writeln(i, ' * ', j, ' = ', i * j);
      j := j + 1;

      if j > 5 then
        break;
      if j = 3 then
        continue;
    until j > 5;

    writeln;
    i := i + 1;
  until i > 5;

  readln;  {Wait for the user to press Enter}
end.