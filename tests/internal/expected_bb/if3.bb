program:
.program.entry -> bb0 {
}

bb0 -> bb1 {
  #t0 := 0
  num := #t0
}

bb1 -> bb2 {
}

bb10 -> bb11 {
}

bb11 -> bb14 {
  #t9 := 2
  res1 := #t9
  #t10 := 1
  res2 := #t10
}

bb12 -> bb13 {
}

bb13 -> bb14 {
  #t11 := 3
  res1 := #t11
  #t12 := 3
  res2 := #t12
}

bb14 -> bb6 {
}

bb15 -> bb16 {
}

bb16{
  halt
}

bb2 -> bb3 bb5 {
  #t1 := num
  #t2 := 0
  #t3 := #t1 > #t2
  br nonzero #t3 ? bb3 : bb5
}

bb3 -> bb4 {
}

bb4 -> bb15 {
  #t4 := 1
  res1 := #t4
  #t5 := 2
  res2 := #t5
}

bb5 -> bb7 {
}

bb6 -> bb15 {
}

bb7 -> bb8 {
}

bb8 -> bb9 {
}

bb9 -> bb10 bb12 {
  #t6 := num
  #t7 := 0
  #t8 := #t6 < #t7
  br nonzero #t8 ? bb10 : bb12
}

