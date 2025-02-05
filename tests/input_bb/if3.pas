program IfTest;

var
  num: Integer;
  res1, res2: Integer;

begin
  num := 0;
  if num > 0 then
    begin
        res1 := 1;
        res2 := 2;
    end
    else if num < 0 then
    begin
        res1 := 2;
        res2 := 1;
    end
    else
    begin
        res1 := 3;
        res2 := 3;
    end;
end.