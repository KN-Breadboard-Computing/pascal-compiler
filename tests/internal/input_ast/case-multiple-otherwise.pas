program CaseMultipleOtherwise;

var
  MyChar: Char;

begin
  MyChar := 'A';
  case MyChar of
    'A': writeln('A');
    'B': writeln('B');
    'C': writeln('C');
  otherwise
    writeln('Not A, B, or C');
  otherwise
    writeln('Not A, B, or C');
  end;
end.