program CaseInvalidExpressionType;

var
  MyCharArray: array[0..9] of Char;

begin
  case MyCharArray of
  otherwise
    writeln('Otherwise');
  end;
end.