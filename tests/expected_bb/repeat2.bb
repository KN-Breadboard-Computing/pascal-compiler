program:
-> .program.entry -> bb0 {
}

.program.entry -> bb0 -> bb1 {
  i := 0
  j := 0
  #t0 := 0
  j := #t0
}

bb0 bb10 -> bb1 -> bb3 {
}

bb1 -> bb3 -> bb4 {
  #t1 := j
  #t2 := 3
  #t3 := #t1 * #t2
  j := #t3
  #t4 := 0
  i := #t4
}

bb3 bb7 -> bb4 -> bb5 {
}

bb4 -> bb5 -> bb6 {
  #t5 := i
  #t6 := 2
  #t7 := #t5 + #t6
  i := #t7
}

bb5 -> bb6 -> bb7 {
}

bb6 -> bb7 -> bb4 bb8 {
  #t8 := j
  #t9 := 10
  #t10 := #t8 - #t9
  br nonzero #t10 ? bb4 : bb8
}

bb7 -> bb8 -> bb2 {
}

bb8 -> bb2 -> bb9 {
}

bb2 -> bb9 -> bb10 {
}

bb9 -> bb10 -> bb1 bb11 {
  #t11 := j
  #t12 := 5
  #t13 := #t11 - #t12
  br nonzero #t13 ? bb1 : bb11
}

bb10 -> bb11 -> bb12 {
}

bb11 -> bb12 -> {
  #t14 := 0
  j := #t14
  halt
}


