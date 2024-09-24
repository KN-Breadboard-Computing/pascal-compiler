program:
-> .program.entry -> bb0 {
}

.program.entry -> bb0 -> bb1 {
  #t0 := 1
  i := #t0
  #t1 := 1
  j := #t1
  #t2 := 0
  k := #t2
}

bb0 bb4 -> bb1 -> bb2 {
}

bb1 -> bb2 -> bb3 bb13 {
  #t3 := j
  #t4 := 100
  #t5 := #t3 - #t4
  br nonzero #t5 ? bb3 : bb13
}

bb2 -> bb3 -> bb5 {
}

bb2 -> bb13 -> bb14 {
}

bb3 -> bb5 -> bb6 {
}

bb13 -> bb14 -> {
  #t17 := j
  res := #t17
  #t18 := k
  res := #t18
  #t19 := i
  res := #t19
  halt
}

bb5 -> bb6 -> bb7 {
}

bb6 -> bb7 -> bb8 bb10 {
  #t6 := j
  #t7 := 20
  #t8 := #t6 - #t7
  br nonzero #t8 ? bb8 : bb10
}

bb7 -> bb8 -> bb9 {
}

bb7 -> bb10 -> bb11 {
}

bb8 -> bb9 -> bb12 {
  #t9 := k
  #t10 := 1
  #t11 := #t9 + #t10
  k := #t11
  #t12 := i
  j := #t12
}

bb10 -> bb11 -> bb12 {
  #t13 := k
  #t14 := 2
  #t15 := #t13 + #t14
  k := #t15
  #t16 := k
  j := #t16
}

bb11 bb9 -> bb12 -> bb4 {
}

bb12 -> bb4 -> bb1 {
}


