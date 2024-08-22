program PassConstantAsReferenceArgument;

var
  r: record r: Integer; end;

procedure Fun1(x: Integer);
begin
  x := 10;
end;

procedure Fun2(var x: Integer);
begin
  x := 10;
end;

begin
  Fun1(r.r);
  Fun1(10);
  Fun2(r.r);
  Fun2(10);
end.