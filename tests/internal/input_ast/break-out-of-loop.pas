program BreakOutOfLoop;

var
  x: Integer;

begin
  for i := 1 to 10 do
    begin
      WriteLn(i);
      if i = 5 then
        Break;
    end;

  for i := 1 to 10 do
    begin
      case x of
      1:
      begin
        WriteLn('x is 1');
        Break;
      end;
      otherwise
      begin
        WriteLn('x is not 1');
      end;
      end;
    end;

  Break;
end.