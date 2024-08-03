program HelloWorld;

var
  name, surname: string;
begin
  write('Hello, World! ');
  writeln;

  writeln('What is your name?');
  read(name);

  writeln('What is your surname?');
  read(surname);

  writeln('Hello, ', name, ' ', surname, '!');
  readln;
end.