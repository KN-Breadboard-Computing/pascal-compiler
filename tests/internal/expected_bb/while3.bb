program:
.program.entry -> bb0 {
}

bb0 -> bb1 {
}

bb1 -> bb2 {
}

bb10 -> bb4 {
}

bb11 -> bb12 {
}

bb12{
  halt
}

bb2 -> bb3 bb11 {
  #t0 := i
  #t1 := 5
  #t2 := #t0 < #t1
  br nonzero #t2 ? bb3 : bb11
}

bb3 -> bb5 {
}

bb4 -> bb1 {
  #t10 := i
  #t11 := 1
  #t12 := #t10 + #t11
  i := #t12
}

bb5 -> bb6 {
  #t3 := 0
  j := #t3
}

bb6 -> bb7 {
}

bb7 -> bb8 bb10 {
  #t4 := j
  #t5 := 3
  #t6 := #t4 < #t5
  br nonzero #t6 ? bb8 : bb10
}

bb8 -> bb9 {
}

bb9 -> bb6 {
  #t7 := j
  #t8 := 2
  #t9 := #t7 + #t8
  j := #t9
}


