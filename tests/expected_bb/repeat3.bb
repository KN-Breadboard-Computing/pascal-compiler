program:
-> .program.entry -> bb0 {
}

.program.entry -> bb0 -> bb1 {
  i := 0
  j := 0
}

bb0 bb10 -> bb1 -> bb3 {
}

bb1 -> bb3 -> bb4 {
}

bb3 bb7 -> bb4 -> bb5 {
}

bb4 -> bb5 -> bb6 {
  #t0 := i
  #t1 := 2
  #t2 := #t0 + #t1
  i := #t2
}

bb5 -> bb6 -> bb7 {
}

bb6 -> bb7 -> bb4 bb8 {
  #t3 := j
  #t4 := 10
  #t5 := #t3 - #t4
  br nonzero #t5 ? bb4 : bb8
}

bb7 -> bb8 -> bb2 {
}

bb8 -> bb2 -> bb9 {
  #t6 := j
  #t7 := 1
  #t8 := #t6 + #t7
  j := #t8
}

bb2 -> bb9 -> bb10 {
}

bb9 -> bb10 -> bb1 bb11 {
  #t9 := j
  #t10 := 5
  #t11 := #t9 - #t10
  br nonzero #t11 ? bb1 : bb11
}

bb10 -> bb11 -> bb12 {
}

bb11 -> bb12 -> {
  #t12 := 0
  j := #t12
  halt
}


