program ForTest;

var
  sum: Integer;

begin
  sum := 0;

  for i := 1 to 5 do
    begin
      sum := sum + i;
      for j := 1 downto 5 do
        sum := sum + i * j;
    end;
end.