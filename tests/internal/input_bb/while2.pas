program WhileTest

var
  i, j: Integer;
begin
  i := 1;
  j := 2;
  while i < 5 do
  begin
      i := i+1;
      j := 0;
      while j < 3 do
        j := j+2;
  end;
end.