program RepeatTest;

var
  i, j: Integer;
begin
  repeat
    repeat
      i := i + 2;
    until j > 10;
    j := j + 1;
  until j > 5;

  j := 0;
end.