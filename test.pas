program SsaTest;

var
  i,j,k,res: Integer;
begin
  i := 1;
  j := 1;
  k := 0;

  while j < 100 do
  begin
    if j < 20 then
    begin
      k := k + 1;
      j := i;
    end
    else
    begin
      k := k + 2;
      j := k;
    end;
  end;

  res := j;
  res := k;
  res := i;
end.