program Recursion;
  function F(n: Integer): Integer;
  begin
    F := n * F(n - 1);
  end;

  procedure G(n: Integer);
  begin
    writeln(n);
    G(n - 1);
  end;
begin
  writeln(F(5));
  G(5);
end.
