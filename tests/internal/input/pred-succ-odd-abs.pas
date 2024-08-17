program PredSuccOddAbs;
var
  n, m: Integer;
  b: Boolean;
  c1, c2: Char;

begin
  n := 0;
  m := Succ(n);
  n := Pred(m);
  b := Odd(n);

  c1 := 'k';
  c2 := Succ(c1);
  c1 := Pred(c2);

  m := -5;
  n := Abs(m);
end.