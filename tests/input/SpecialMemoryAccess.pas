program SpecialMemoryAccess;

type
  TMyRecord = record
    A: Integer;
    B: Integer;
  end;

var
  AddressHigh, AddressLow: Integer;
  MyChar: Char;
  MyArray: array[0..9] of Integer;
  MyRecord: TMyRecord;

begin
  read(AddressHigh);
  read(AddressLow);

  MemoryRead(AddressHigh, AddressLow, MyChar);
  MemoryRead(255, AddressLow, MyArray);
  StackRead(1000, 2, MyRecord);

  writeln(MyChar);
  writeln(MyArray[0]);
  writeln(MyRecord.A);

  MyRecord.A := 10;
  MyArray[0] := 20;
  MyChar := Chr(65);

  MemoryWrite(AddressHigh, AddressLow, MyChar);
  MemoryWrite(255, AddressLow, MyArray);
  StackWrite(1000, 2, MyRecord);
end.