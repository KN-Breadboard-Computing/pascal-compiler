program:
-> .program.entry -> bb0 {
}

.program.entry -> bb0 -> bb1 {
  i := 0
  j := 0
  k := 0
  a := 0
  #t0 := 7
  a := #t0
  #t1 := 9
  k := #t1
}

bb0 bb4 -> bb1 -> bb2 {
}

bb1 -> bb2 -> bb3 bb17 {
  #t2 := i
  #t3 := 5
  #t4 := #t2 - #t3
  br nonzero #t4 ? bb3 : bb17
}

bb2 -> bb3 -> bb5 {
}

bb2 -> bb17 -> bb18 {
}

bb3 -> bb5 -> bb6 {
}

bb17 -> bb18 -> {
  halt
}

bb5 bb9 -> bb6 -> bb7 {
}

bb6 -> bb7 -> bb8 bb16 {
  #t5 := k
  #t6 := 9
  #t7 := #t5 - #t6
  br nonzero #t7 ? bb8 : bb16
}

bb7 -> bb8 -> bb10 {
}

bb7 -> bb16 -> bb4 {
}

bb8 -> bb10 -> bb11 {
  #t8 := 0
  j := #t8
}

bb16 -> bb4 -> bb1 {
}

bb10 bb14 -> bb11 -> bb12 {
}

bb11 -> bb12 -> bb13 bb15 {
  #t9 := j
  #t10 := 3
  #t11 := #t9 - #t10
  br nonzero #t11 ? bb13 : bb15
}

bb12 -> bb13 -> bb14 {
}

bb12 -> bb15 -> bb9 {
}

bb13 -> bb14 -> bb11 {
  #t12 := j
  #t13 := 2
  #t14 := #t12 + #t13
  j := #t14
}

bb15 -> bb9 -> bb6 {
  #t15 := j
  a := #t15
  #t16 := i
  #t17 := a
  #t18 := #t16 + #t17
  i := #t18
  #t19 := k
  #t20 := 1
  #t21 := #t19 + #t20
  k := #t21
}


