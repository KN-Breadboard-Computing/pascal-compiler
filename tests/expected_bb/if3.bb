program:
-> .program.entry -> bb0 {
}

.program.entry -> bb0 -> bb1 {
  num := 0
  res1 := 0
  res2 := 0
  call read( &#t0 )
  res1 := #t0
  call read( &#t1 )
  res2 := #t1
  call read( &#t2 )
  num := #t2
}

bb0 -> bb1 -> bb2 {
}

bb1 -> bb2 -> bb3 bb13 {
  #t3 := num
  #t4 := 0
  #t5 := #t3 - #t4
  br nonzero #t5 ? bb3 : bb13
}

bb2 -> bb3 -> bb5 {
}

bb2 -> bb13 -> bb15 {
}

bb3 -> bb5 -> bb6 {
  #t6 := 1
  res1 := #t6
  #t7 := 2
  res2 := #t7
}

bb13 -> bb15 -> bb16 {
}

bb5 -> bb6 -> bb7 {
}

bb15 -> bb16 -> bb17 {
}

bb6 -> bb7 -> bb8 bb10 {
  #t8 := res1
  #t9 := 1
  #t10 := #t8 - #t9
  br nonzero #t10 ? bb8 : bb10
}

bb16 -> bb17 -> bb18 bb20 {
  #t13 := num
  #t14 := 0
  #t15 := #t13 - #t14
  br nonzero #t15 ? bb18 : bb20
}

bb7 -> bb8 -> bb9 {
}

bb7 -> bb10 -> bb11 {
}

bb17 -> bb18 -> bb19 {
}

bb17 -> bb20 -> bb21 {
}

bb8 -> bb9 -> bb12 {
  #t11 := 2
  res1 := #t11
}

bb10 -> bb11 -> bb12 {
  #t12 := 3
  res1 := #t12
}

bb18 -> bb19 -> bb22 {
  #t16 := 2
  res1 := #t16
  #t17 := 1
  res2 := #t17
}

bb20 -> bb21 -> bb22 {
  #t18 := 3
  res1 := #t18
  #t19 := 3
  res2 := #t19
}

bb11 bb9 -> bb12 -> bb4 {
}

bb19 bb21 -> bb22 -> bb14 {
}

bb12 -> bb4 -> bb23 {
}

bb22 -> bb14 -> bb23 {
}

bb4 bb14 -> bb23 -> bb24 {
}

bb23 -> bb24 -> {
  #t20 := res1
  call write( #t20 )
  #t21 := res2
  call write( #t21 )
  halt
}


