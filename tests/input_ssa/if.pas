program IfSsaTest;

var
  num: Integer;
  res1, res2: Integer;

begin
  Read(res1);
  Read(res2);
  Read(num);

  if num > 0 then
    begin
        res1 := 1;
        res2 := 2;
        if res1 = 1 then
            res1 := 2
        else
            res1 := 3;
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

    Write(res1);
    Write(res2);
end.