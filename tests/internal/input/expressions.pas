program Expressions;

type
  TArrInt = array[1..10] of Integer;
  TArrChar = array[1..10] of Char;
  TArrBool = array[1..10] of Boolean;

  TRecord = record
    i: Integer;
    c: Char;
    b: Boolean;
  end;

var
  i1, i2, i3: Integer;
  b1, b2, b3: Boolean;
  a1: TArrInt;
  a2: TArrBool;
  r: TRecord;
  c1, c2, c3: Boolean;

begin
  i1 := 11;
  i2 := 29;
  i3 := i1 + i2 * -i2;
  r.i := i2 / ((i1 + a1[1]) % 3);
  a1[1] := i1 % (r.i) - 8;

  r.c := Chr(i1 + i2);
  r.i := Ord(r.c) + 1;

  b1 := True;
  b2 := False;
  b3 := not b1 and r.b or b1 and True;
  r.b := b1 or a2[8] and b3;
  a2[8] := b1 and (b2 or False) or b3;

  c1 := (i1 > i2) and (i1 < i3) and (i2 <> i3) or (i1 = i2);
  c2 := (r.i >= i1) and (r.i <= i2) or (r.i < i3);
  c3 := (r.c <= 'a') and (r.c >= 'z');
  c1 := b1 <= b2;
end.