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

bb4 -> bb7 {
  #t4 := 1
  res := #t4
}

bb5 -> bb6 {
}

bb6 -> bb7 {
  #t5 := 2
  res := #t5
}

bb7 -> bb8 {
}

bb8{
  halt
}


