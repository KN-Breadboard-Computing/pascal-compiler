program:
.program.entry -> bb0 {
}

bb0 -> bb1 {
  #t0 := 1
  i := #t0
}

bb1 -> bb2 {
}

bb2 -> bb3 bb5 {
  #t1 := i
  #t2 := 5
  #t3 := #t1 < #t2
  br nonzero #t3 ? bb3 : bb5
}

bb3 -> bb4 {
}

bb4 -> bb1 {
  #t4 := i
  #t5 := 1
  #t6 := #t4 + #t5
  i := #t6
}

bb5 -> bb6 {
}

bb6{
  halt
}

