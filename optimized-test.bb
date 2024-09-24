program:
-> bb0 -> bb2 {
  i := 1
  j := 1
  k := 0
}

bb0 bb11 bb9 -> bb2 -> bb7 bb14 {
  #t5 := j - 100
  br nonzero #t5 ? bb7 : bb14
}

bb2 -> bb7 -> bb9 bb11 {
  #t8 := j - 20
  br nonzero #t8 ? bb9 : bb11
}

bb2 -> bb14 -> {
  res := j
  res := k
  res := i
  halt
}

bb7 -> bb9 -> bb2 {
  k := k + 1
  j := i
}

bb7 -> bb11 -> bb2 {
  k := k + 2
  j := k
}


