program RepeatTest;

var
  i, j: Integer;
begin
  j := 0;
  repeat
    j := j + 1;
    i := i * 3;
  until j > 5;

  j := 0;
end.