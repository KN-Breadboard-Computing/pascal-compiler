program RoutineScoping;

procedure Test;
var
  a, b: integer;

  procedure SubTest(d: Integer);
  var
    c: integer;
  begin
    c := d + 3;
    writeln(c);
  end;

  function SubTest2: integer;
  var
    d: integer;
  begin
    d := 4;
    writeln(d);
    SubTest(d);
    SubTest2 := d;
  end;
begin
  a := 1;
  b := 2;
  writeln(a);
  writeln(b);
  SubTest2;
end;

begin
  Test;
end.