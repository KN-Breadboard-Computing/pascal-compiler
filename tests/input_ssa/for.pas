program ForSsaTest;

var
  sum: Integer;

begin
  sum := 0;

  for i := 1 to 5 do
    begin
      for j := 5 downto 1 do
        begin
          sum := sum + j;
          if j = 2 then continue;
          if sum = 34 then break;
        end;
      sum := sum + i;
    end;
end.