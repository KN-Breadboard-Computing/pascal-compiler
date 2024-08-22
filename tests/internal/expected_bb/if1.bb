program:
.program.entry -> bb0 {
}

bb0 -> bb1 {
  #t0 := 0
  num := #t0
}

bb1 -> bb2 {
}

bb2 -> bb3 bb5 {
  #t1 := num
  #t2 := 0
  #t3 := #t1 > #t2
  br nonzero #t3 ? bb3 : bb5
}

bb3 -> bb4 {
}

bb4 -> bb5 {
  #t4 := 1
  res := #t4
}

bb5 -> bb6 {
}

bb6{
  halt
}


