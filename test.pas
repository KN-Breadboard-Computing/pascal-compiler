program SsaTest;

var
  a,b,c,d,x,y,z,w,p: Integer;
begin
  x := 1;
  y := 2;
  z := 3;
  w := 4;
  a := x + y;
  p := z + w;
  d := a + p + w;
  b := a + x;
  a := b + 2;
  c := y + 1;
  a := c + a;
end.