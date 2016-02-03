.pos 0x1000
  code:

  # init/malloc

  ld $heap0, r0 # r0 = &heap0
  ld $y, r1     # r1 = &s.y
  st r0, (r1)   # s.y = &heap0

  ld $heap1, r0 # r0 = &heap1
  ld $z, r1     # r1 = &s.z
  st r0, (r1)   # s.z = &ds

  # foo()

  ld $v, r0           # r0 = &v
  ld $i, r1           # r1 = &i
  ld (r1), r1         # r1 = i

  ld $x, r2           # r2 = &x
  ld (r2, r1, 4), r3  # r3 = x[i]
  st r3, (r0)         # v = x[i]

  ld $y, r2           # r2 = &y
  ld (r2), r2         # r2 = y
  ld (r2, r1, 4), r3  # r3 = y[i]
  st r3, (r0)         # v = y[i]

  ld $z, r2           # r2 = &z
  ld (r2), r2         # r2 = z
  ld (r2, r1, 4), r3  # r3 = z->x[0]
  st r3, (r0)         # v = z->x[0]

  halt

.pos 0x2000
  static:
  i: .long 0
  v: .long 0
  s:
  x: .long 0 # int x[0]
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

