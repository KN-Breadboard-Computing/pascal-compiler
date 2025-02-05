program Types;

type
  PType = Integer;

  procedure ProcA(a: Char);
  type
    PAType = Char;
  var
    pa: PAType;
    funRes: PType;

    function Fun(arg: Integer) : PType;
    begin
      Fun := 3;
    end;
  begin
    funRes := Fun(0);
    pa := 'a';
  end;

  procedure ProcB(a: Boolean);
  type
    PBType = Boolean;
  var
    pb: PBType;
    funRes: PType;

    function Fun(arg: Integer) : PType;
    begin
      Fun := 3;
    end;
  begin
    funRes := Fun(0);
    pb := False;
  end;
begin
  ProcA('a');
  ProcB(True);
end.