program SsaTest;

var
  a,b,c,d,e: Integer;
begin
  a := 0;
  b := 1;
  d := a;
  a := 1;

  while a < 100 do
  begin
    a := 5 + 1;
    a := a + 2;
    d := d + 1;
  end;

  if a > b then
    c := 6 - b
  else
    c := a + b;

  d := c;
  e := d + 1;
end.