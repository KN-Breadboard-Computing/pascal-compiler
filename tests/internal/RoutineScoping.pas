program RoutineScoping;

procedure Test;
var
  a, b, c: integer;

  procedure SubTest;
  var
    c: integer;
  begin
    c := 3;
    writeln(c);
  end;

  function SubTest: integer;
  var
    d: integer;
  begin
    d := 4;
    writeln(d);
    SubTest := d;
  end;
begin
  a := 1;
  b := 2;
  writeln(a);
  writeln(b);
  SubTest;
end;

begin
  Test;
end.