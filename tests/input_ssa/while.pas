program WhileSsaTest;

var
  i, j, k, a: Integer;
begin
  a := 7;
  k := 9;
  while i < 5 do
  begin
      while k < 9 do
      begin
          j := 0;
          while j < 3 do
            j := j+2;
          a := j;
          i := i+a;
          k := k+1;
      end;
  end;
end.