program:
.program.entry -> bb0 {
}

bb0 -> bb1 {
  #t0 := 0
  sum := #t0
}

bb1 -> bb2 {
}

bb10 -> bb11 {
  #t4 := 5
  j := #t4
}

bb11 -> bb12 {
}

bb12 -> bb13 {
  #t5 := 1
}

bb13 -> bb14 bb28 {
  #t6 := j - #t5
  br negative #t6 ? bb14 : bb28
}

bb14 -> bb16 {
}

bb15 -> bb13 {
  j := j - 1
}

bb16 -> bb17 {
  #t7 := sum
  #t8 := j
  #t9 := #t7 + #t8
  sum := #t9
}

bb17 -> bb18 {
}

bb18 -> bb19 bb21 {
  #t10 := j
  #t11 := 2
  #t12 := #t10 == #t11
  br nonzero #t12 ? bb19 : bb21
}

bb19 -> bb20 {
}

bb2 -> bb3 {
  #t1 := 1
  i := #t1
}

bb20 -> bb21 {
}

bb21 -> bb22 {
}

bb22 -> bb23 {
}

bb23 -> bb24 {
}

bb24 -> bb25 bb27 {
  #t13 := sum
  #t14 := 34
  #t15 := #t13 == #t14
  br nonzero #t15 ? bb25 : bb27
}

bb25 -> bb26 {
}

bb26 -> bb27 {
}

bb27 -> bb15 {
}

bb28 -> bb7 {
}

bb29 -> bb30 {
}

bb3 -> bb4 {
}

bb30{
  halt
}

bb4 -> bb5 {
  #t2 := 5
}

bb5 -> bb6 bb29 {
  #t3 := i - #t2
  br positive #t3 ? bb6 : bb29
}

bb6 -> bb8 {
}

bb7 -> bb5 {
  #t16 := sum
  #t17 := i
  #t18 := #t16 + #t17
  sum := #t18
  i := i + 1
}

bb8 -> bb9 {
}

bb9 -> bb10 {
}


