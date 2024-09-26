program:
-> bb0 -> bb2 {
  a := 0
  b := 1
  d := a
  a := 1
}

bb0 bb4 -> bb2 -> bb4 bb8 {
  #t6 := a - 100
  br nonzero #t6 ? bb4 : bb8
}

bb2 -> bb4 -> bb2 {
  a := 5 + 1
  a := a + 2
  d := d + 1
}

bb2 -> bb8 -> bb10 bb12 {
  #t18 := a - b
  br nonzero #t18 ? bb10 : bb12
}

bb8 -> bb10 -> bb14 {
  c := 6 - b
}

bb8 -> bb12 -> bb14 {
  c := a + b
}

bb10 bb12 -> bb14 -> {
  d := c
  e := d + 1
  halt
}


