label bb0
mov immediate to A 0b00000000
mov A to absolute zero page memory 0b10000101
mov immediate to A 0b00000000
mov A to absolute zero page memory 0b10000110
mov immediate to A 0b00000111
mov A to absolute zero page memory 0b10000100
mov immediate to A 0b00001001
mov A to absolute zero page memory 0b10000111
label bb2
mov absolute zero page to A 0b10000101
mov immediate to B 0b00000101
mov A-B to A
mov A to absolute zero page memory 0b10000010
mov absolute zero page to A 0b10000010
mov 0 to B
save flags of A-B
jump to immediate if zero flag not set bb7
jump to immediate bb18
label bb7
mov absolute zero page to A 0b10000111
mov immediate to B 0b00001001
mov A-B to A
mov A to absolute zero page memory 0b10000011
mov absolute zero page to A 0b10000011
mov 0 to B
save flags of A-B
jump to immediate if zero flag not set bb10
jump to immediate bb2
label bb18
halt
label bb10
mov immediate to A 0b00000000
mov A to absolute zero page memory 0b10000110
label bb12
mov absolute zero page to A 0b10000110
mov immediate to B 0b00000011
mov A-B to A
mov A to absolute zero page memory 0b10000001
mov absolute zero page to A 0b10000001
mov 0 to B
save flags of A-B
jump to immediate if zero flag not set bb14
jump to immediate bb9
label bb14
mov absolute zero page to A 0b10000110
mov immediate to B 0b00000010
mov A+B to A
mov A to absolute zero page memory 0b10000110
label bb9
mov absolute zero page to A 0b10000110
mov A to absolute zero page memory 0b10000100
mov absolute zero page to A 0b10000101
mov absolute zero page to B 0b10000100
mov A+B to A
mov A to absolute zero page memory 0b10000101
mov absolute zero page to A 0b10000111
mov immediate to B 0b00000001
mov A+B to A
mov A to absolute zero page memory 0b10000111
