program Cases;

type
  Day = (Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday);
var
  MyDay: Day;
  MyChar: Char;

begin
  MyDay := Sunday;

  case MyDay of
    Sunday: writeln('Sunday');
    Monday: writeln('Monday');
    Tuesday: writeln('Tuesday');
    Wednesday: writeln('Wednesday');
    Thursday: writeln('Thursday');
    Friday: writeln('Friday');
    Saturday: writeln('Saturday');
  end;

  MyChar := 'A';
  case MyChar of
    'A': writeln('A');
    'B': writeln('B');
    'C': writeln('C');
  otherwise
    writeln('Not A, B, or C');
  end;
end.