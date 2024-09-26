program:
-> .program.entry -> bb0 {
}

.program.entry -> bb0 -> bb1 {
  #t0 := 0
  a := #t0
  #t1 := 1
  b := #t1
  #t2 := a
  d := #t2
  #t3 := 1
  a := #t3
}

bb0 bb4 -> bb1 -> bb2 {
}

bb1 -> bb2 -> bb3 bb5 {
  #t4 := a
  #t5 := 100
  #t6 := #t4 - #t5
  br nonzero #t6 ? bb3 : bb5
}

bb2 -> bb3 -> bb4 {
}

bb2 -> bb5 -> bb6 {
}

bb3 -> bb4 -> bb1 {
  #t7 := 5
  #t8 := 1
  #t9 := #t7 + #t8
  a := #t9
  #t10 := a
  #t11 := 2
  #t12 := #t10 + #t11
  a := #t12
  #t13 := d
  #t14 := 1
  #t15 := #t13 + #t14
  d := #t15
}

bb5 -> bb6 -> bb7 {
}

bb6 -> bb7 -> bb8 {
}

bb7 -> bb8 -> bb9 bb11 {
  #t16 := a
  #t17 := b
  #t18 := #t16 - #t17
  br nonzero #t18 ? bb9 : bb11
}

bb8 -> bb9 -> bb10 {
}

bb8 -> bb11 -> bb12 {
}

bb9 -> bb10 -> bb13 {
  #t19 := 6
  #t20 := b
  #t21 := #t19 - #t20
  c := #t21
}

bb11 -> bb12 -> bb13 {
  #t22 := a
  #t23 := b
  #t24 := #t22 + #t23
  c := #t24
}

bb10 bb12 -> bb13 -> bb14 {
}

bb13 -> bb14 -> {
  #t25 := c
  d := #t25
  #t26 := d
  #t27 := 1
  #t28 := #t26 + #t27
  e := #t28
  halt
}


