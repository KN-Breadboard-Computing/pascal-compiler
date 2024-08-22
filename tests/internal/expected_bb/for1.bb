program:
.program.entry -> bb0 {
}

bb0 -> bb1 {
  #t0 := 0
  sum := #t0
}

bb1 -> bb2 {
}

bb2 -> bb3 {
  #t1 := 1
  count := #t1
}

bb3 -> bb4 {
}

bb4 -> bb5 {
  #t2 := 100
}

bb5 -> bb6 bb8 {
  #t3 := count - #t2
  br positive #t3 ? bb6 : bb8
}

bb6 -> bb7 {
}

bb7 -> bb5 {
  #t4 := sum
  #t5 := count
  #t6 := #t4 + #t5
  sum := #t6
  count := count + 1
}

bb8 -> bb9 {
}

bb9{
  halt
}


