program ArrayDeclaration;

type
  TDays = (Mon, Tue, Wed, Thu, Fri, Sat, Sun);

  TArr1 = array[-1..10] of Char;
  TArr2 = array['A'..'z'] of Integer;
  TArr3 = array[False..True] of Integer;
  TArr4 = array[(Mon, Tue, Wed, Thu, Fri, Sat, Sun)] of Integer;
  TArr5 = array[-MAXINT..MAXINT] of Char;
  TArr6 = array[Integer] of Integer;
  TArr8 = array[Char] of Char;
  TArr9 = array[Boolean] of Boolean;
  TArr10 = array[Mon..Fri] of Char;
  TArr11 = array[TDays] of Integer;

var
  arr1: TArr1;
  arr2: TArr2;
  arr3: TArr3;
  arr4: TArr4;
  arr5: TArr5;
  arr6: TArr6;
  arr8: TArr8;
  arr9: TArr9;
  arr10: TArr10;
  arr11: TArr11;

begin
  Read(arr1[0]);
  Read(arr2['o']);
  Read(arr3[False]);
  Read(arr4[Fri]);
  Read(arr5[MAXINT]);
  Read(arr6[5]);
  Read(arr6[-3]);
  Read(arr8['*']);
  Read(arr9[False]);
  Read(arr10[Wed]);
  Read(arr11[Sun]);
end.