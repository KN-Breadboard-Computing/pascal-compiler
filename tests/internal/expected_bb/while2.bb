program:
.program.entry -> bb0 {
}

bb0 -> bb1 {
  #t0 := 1
  i := #t0
  #t1 := 2
  j := #t1
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
  #t2 := i
  #t3 := 5
  #t4 := #t2 < #t3
  br nonzero #t4 ? bb3 : bb11
}

bb3 -> bb5 {
}

bb4 -> bb1 {
}

bb5 -> bb6 {
  #t5 := i
  #t6 := 1
  #t7 := #t5 + #t6
  i := #t7
  #t8 := 0
  j := #t8
}

bb6 -> bb7 {
}

bb7 -> bb8 bb10 {
  #t9 := j
  #t10 := 3
  #t11 := #t9 < #t10
  br nonzero #t11 ? bb8 : bb10
}

bb8 -> bb9 {
}

bb9 -> bb6 {
  #t12 := j
  #t13 := 2
  #t14 := #t12 + #t13
  j := #t14
}


