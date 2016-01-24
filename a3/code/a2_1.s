.pos 0x100

  ld 0x204, r0 # *c
  ld $0x5, r1 # 5
  st r0, (r1) # c = 5;

  ld $0x10, r1 # 10
  ld (r0), r2 # c
  add r2, r1 # c + 10
  ld 0x200, r3 # *b
  st r1, (r3) # b = c + 10

  ld $0x208, r4 # *a
  ld $0x8, r5 # 8
  st r5, (r4, r5, 4) # a[8] = 8

  ld $0x4, r5 # 4
  ld (r4, r5, 4), r6 # a[4]
  add r5, r6 # a[4] + 4
  st r6, (r4, r5, 4) # a[4] = a[4] + 4

  ld $0x8, r5 # 8
  ld (r4, r5, 4), r6 # a[8]
  ld (r3), r7 # b
  add r7, r6 # a[8] + b
  ld (r0), r8 # c
  ld $0x7, r1 # 7
  and r1, r7 # b & 0x7
  ld (r4, r7, 4), r1 # a[b & 0x7]
  add r1, r6 # + ^
  st r6, (r4, r8, 4) # a[c] = ^

  halt

.pos 0x200
# Data

b: .long 0 # int b;
c: .long 0 # int c;
a: .long 0 # int a[10];
   .long 0
   .long 0
   .long 0
   .long 0
   .long 0
   .long 0
   .long 0
   .long 0
   .long 0
