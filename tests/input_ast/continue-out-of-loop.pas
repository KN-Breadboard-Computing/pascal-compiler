program ContinueOutOfLoop;

var
  x: Integer;

begin
  for i := 1 to 10 do
    begin
      WriteLn(i);
      if i = 5 then
        x := i
      else
        Continue;
    end;

  for i := 1 to 10 do
    begin
      case x of
      1:
      begin
        WriteLn('x is 1');
      end;
      otherwise
      begin
        WriteLn('x is not 1');
        Continue;
      end;
      end;
    end;

  Continue;
end.