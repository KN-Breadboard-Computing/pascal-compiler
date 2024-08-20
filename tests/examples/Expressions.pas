program Expressions;

type
  TLogicResult = record
    r1, r2: Boolean;
  end;
var
    a, b, c, d, e, f: Integer;
    g, h, i, j, k, l: Boolean;
    lr: TLogicResult;
    specialInts: array[1..5] of Integer;
    m: Char;
begin
    read(a);
    read(b);
    read(c);
    read(d);
    read(e);

    read(g);
    read(h);
    read(i);
    read(j);

    f := 7 - (a + b * -c * a - d / e) % 2;
    lr.r1 := g and (h) or i and (j or not g);
    lr.r2 := (a > b) and (b < c) or (c = d) and (d <> e) or (e <= a) and (a >= b);
    k := lr.r1 and lr.r2;
    specialInts[1] := Abs(a);
    specialInts[2] := Ord('a');
    specialInts[3] := Pred(b);
    specialInts[4] := Succ(specialInts[1]);
    l := Odd(c);
    m := Chr(specialInts[4]);
end.