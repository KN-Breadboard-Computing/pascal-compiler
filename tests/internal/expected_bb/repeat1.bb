program:
.program.entry -> bb0 {
}

bb0 -> bb1 {
  #t0 := 0
  j := #t0
}

bb1 -> bb2 {
}

bb2 -> bb3 {
  #t1 := j
  #t2 := 1
  #t3 := #t1 + #t2
  j := #t3
  #t4 := i
  #t5 := 3
  #t6 := #t4 * #t5
  i := #t6
}

bb3 -> bb4 {
}

bb4 -> bb1 bb5 {
  #t7 := j
  #t8 := 5
  #t9 := #t7 > #t8
  br nonzero #t9 ? bb1 : bb5
}

bb5 -> bb6 {
}

bb6{
  #t10 := 0
  j := #t10
  halt
}


