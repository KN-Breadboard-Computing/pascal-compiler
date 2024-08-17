program FunNoReturnType;
  function Fun(d: Integer);
  var
    c: integer;
  begin
    c := d + 3;
    writeln(c);
    Fun := c;
  end;
begin

end.