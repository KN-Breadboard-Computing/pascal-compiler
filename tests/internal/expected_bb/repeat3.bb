program:
.program.entry -> bb0 {
}

bb0 -> bb1 {
}

bb1 -> bb3 {
}

bb10 -> bb1 bb11 {
  #t9 := j
  #t10 := 5
  #t11 := #t9 > #t10
  br nonzero #t11 ? bb1 : bb11
}

bb11 -> bb12 {
}

bb12{
  #t12 := 0
  j := #t12
  halt
}

bb2 -> bb9 {
  #t6 := j
  #t7 := 1
  #t8 := #t6 + #t7
  j := #t8
}

bb3 -> bb4 {
}

bb4 -> bb5 {
}

bb5 -> bb6 {
  #t0 := i
  #t1 := 2
  #t2 := #t0 + #t1
  i := #t2
}

bb6 -> bb7 {
}

bb7 -> bb4 bb8 {
  #t3 := j
  #t4 := 10
  #t5 := #t3 > #t4
  br nonzero #t5 ? bb4 : bb8
}

bb8 -> bb2 {
}

bb9 -> bb10 {
}


