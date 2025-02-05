program RepeatTest;

var
  i, j: Integer;
begin
  j := 0;
  repeat
    j := j * 3;
    i := 0;
    repeat
      i := i + 2;
    until j > 10;
  until j > 5;

  j := 0;
end.