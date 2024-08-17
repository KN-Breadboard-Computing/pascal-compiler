program FunMultipleReturn;
  function Fun(d: Integer): Integer;
  var
    c: integer;
  begin
    c := d + 3;
    Fun := c;
    writeln(c);
    Fun := c;
  end;
begin

end.