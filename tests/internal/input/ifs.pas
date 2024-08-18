program Ifs;

var
  num: Integer;

begin
  writeln('Enter an integer: ');
  read(num);

  if num > 0 then
    writeln('The number is positive.');

  if num < 0 then
    writeln('The number is negative.')
  else
    writeln('The number is zero or positive.');

  if num > 0 then
    writeln('The number is positive.')
  else if num < 0 then
    writeln('The number is negative.')
  else
    writeln('The number is zero.');

  if num > 0 then
  begin
    writeln('The number is positive.');
    if num % 2 = 0 then
      writeln('It is also an even number.')
    else
      writeln('It is also an odd number.');
  end
  else if num < 0 then
  begin
    writeln('The number is negative.');
    if num % 2 = 0 then
      writeln('It is also an even number.')
    else
      writeln('It is also an odd number.');
  end
  else
    writeln('The number is zero.');

  writeln;
end.