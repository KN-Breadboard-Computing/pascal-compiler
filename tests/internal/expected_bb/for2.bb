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
  #t7 := 1
  j := #t7
}

bb11 -> bb12 {
}

bb12 -> bb13 {
  #t8 := 5
}

bb13 -> bb14 bb16 {
  #t9 := j - #t8
  br negative #t9 ? bb14 : bb16
}

bb14 -> bb15 {
}

bb15 -> bb13 {
  #t10 := sum
  #t11 := i
  #t12 := j
  #t13 := #t11 * #t12
  #t14 := #t10 + #t13
  sum := #t14
  j := j - 1
}

bb16 -> bb7 {
}

bb17 -> bb18 {
}

bb18{
  halt
}

bb2 -> bb3 {
  #t1 := 1
  i := #t1
}

bb3 -> bb4 {
}

bb4 -> bb5 {
  #t2 := 5
}

bb5 -> bb6 bb17 {
  #t3 := i - #t2
  br positive #t3 ? bb6 : bb17
}

bb6 -> bb8 {
}

bb7 -> bb5 {
  i := i + 1
}

bb8 -> bb9 {
  #t4 := sum
  #t5 := i
  #t6 := #t4 + #t5
  sum := #t6
}

bb9 -> bb10 {
}


