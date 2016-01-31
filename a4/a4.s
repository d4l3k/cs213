.pos 0x1000
  code:
  ld $heap0, r0 # r0 = &heap0
  ld $y, r1     # r1 = &s.y
  st r0, (r1)   # s.y = &heap0

  ld $heap1, r0 # r0 = &heap1
  ld $z, r1     # r1 = &s.z
  st r0, (r1)   # s.z = &ds

  halt

.pos 0x2000
  static:
  i: .long 0
  v: .long 0
  s: .long 0 # int x[0]
     .long 0 # int x[1]
  y: .long 0 # int *y
  z: .long 0 # struct S *z

.pos 0x3000
  heap0: .long 0 # int y[0]
         .long 0 # int y[1]

  heap1: .long 0 # int x[0]
         .long 0 # int x[1]
         .long 0 # int *y
         .long 0 # struct S *z

