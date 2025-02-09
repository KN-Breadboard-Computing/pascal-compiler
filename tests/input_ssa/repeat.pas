program RepeatSsaTest;

var
  i, j, k: Integer;
begin
  repeat
    repeat
      repeat
        i := i + 1;
        k := k + 1;
      until k > 5;
    until i > 10;
    j := j + 1;
  until j > 5;
end.