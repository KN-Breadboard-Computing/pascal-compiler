program GotoStrLabel;

begin
  goto 'label';

  writeln('Hello');

  'label': writeln('World');
end.