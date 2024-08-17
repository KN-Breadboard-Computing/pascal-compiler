program Io;

type
  TDay = (Mon, Tue, Wed, Thu, Fri, Sat, Sun);

var
  IntVar: Integer;
  CharVar: Char;
  BoolVar: Boolean;

  ArrayVar: array[1..10] of Integer;
  ArrayVar2: array[TDay] of Integer;

  RecordVar: record
    IntField: Integer;
  end;

begin
  ReadLn;

  Read(IntVar);
  Read(CharVar);
  Read(BoolVar);
  Read(ArrayVar[1]);
  Read(ArrayVar2[Mon]);
  Read(RecordVar.IntField);

  WriteLn;
  Write(IntVar);
  WriteLn(CharVar);
  Write(BoolVar);
  WriteLn(ArrayVar[1]);
  Write(ArrayVar2[Mon]);
  WriteLn(RecordVar.IntField);

  Write('Hello,', ' ', 'world!', ' ', 43, IntVar, CharVar, BoolVar, ArrayVar[1], ArrayVar2[Mon], RecordVar.IntField);
  WriteLn(IntVar * 8, Ord('A'),  MaxInt);

  MemoryRead(0, 1, IntVar);
  MemoryRead(IntVar, 1, CharVar);
  MemoryRead(2, 1, BoolVar);

  MemoryWrite(0, 1, IntVar);
  MemoryWrite(1, IntVar, CharVar);
  MemoryWrite(2, 1, BoolVar);

  StackRead(0, 1, IntVar);
  StackRead(IntVar, 1, CharVar);
  StackRead(2, 1, BoolVar);

  StackWrite(0, 1, IntVar);
  StackWrite(1, IntVar, CharVar);
  StackWrite(2, 1, BoolVar);
end.