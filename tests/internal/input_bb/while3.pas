program WhileTest;

var
  i, j: Integer;
begin
  while i < 5 do
  begin
      j := 0;
      while j < 3 do
        j := j+2;
     i := i+1;
  end;
end.