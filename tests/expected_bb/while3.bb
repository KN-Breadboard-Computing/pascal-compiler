program:
-> .program.entry -> bb0 {
}

.program.entry -> bb0 -> bb1 {
  i := 0
  j := 0
}

bb0 bb4 -> bb1 -> bb2 {
}

bb1 -> bb2 -> bb3 bb11 {
  #t0 := i
  #t1 := 5
  #t2 := #t0 - #t1
  br nonzero #t2 ? bb3 : bb11
}

bb2 -> bb3 -> bb5 {
}

bb2 -> bb11 -> bb12 {
}

bb3 -> bb5 -> bb6 {
  #t3 := 0
  j := #t3
}

bb11 -> bb12 -> {
  halt
}

bb5 bb9 -> bb6 -> bb7 {
}

bb6 -> bb7 -> bb8 bb10 {
  #t4 := j
  #t5 := 3
  #t6 := #t4 - #t5
  br nonzero #t6 ? bb8 : bb10
}

bb7 -> bb8 -> bb9 {
}

bb7 -> bb10 -> bb4 {
}

bb8 -> bb9 -> bb6 {
  #t7 := j
  #t8 := 2
  #t9 := #t7 + #t8
  j := #t9
}

bb10 -> bb4 -> bb1 {
  #t10 := i
  #t11 := 1
  #t12 := #t10 + #t11
  i := #t12
}


