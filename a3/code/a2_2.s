
.pos 0x100
  # a[i] = a[i+1] + b[i+2];
  ld $0x260, r0      # *i
  ld (r0), r0        # i
  mov r0, r1         # i
  mov r0, r2         # i
  ld $0x1, r3        # 1
  add r3, r1         # i+1
  ld $0x2, r3        # 2
  add r3, r2         # i+2
  ld $0x200, r4      # *a
  ld (r4, r1, 4), r5 # a[i+1]
  ld $0x220, r6      # *b
  ld (r6, r2, 4), r7 # b[i+2]
  add r7, r5         # a[i+1] + b[i+2]
  st r5, (r4, r0, 4) # a[i] = a[i+1] + b[i+2];

  # d[i] = a[i] + b[i];
  ld (r4, r0, 4), r1 # a[i]
  ld (r6, r0, 4), r2 # b[i]
  add r2, r1         # a[i] + b[i]
  ld $0x264, r3      # *d
  ld (r3), r3        # d
  st r1, (r3, r0, 4) # d[i] = a[i] + b[i]

  # d[i] = a[b[i]] + b[a[i]];
  ld (r4, r0, 4), r1 # a[i]
  ld (r6, r0, 4), r2 # b[i]
  ld (r4, r2, 4), r2 # a[b[i]]
  ld (r6, r1, 4), r1 # b[a[i]]
  add r2, r1         # a[b[i]] + b[a[i]]
  st r1, (r3, r0, 4) # d[i] = a[b[i]] + b[a[i]];

  # d[b[i]] = b[a[i & 3] & 3] - a[b[i & 3] & 3] + d[i];
  mov r0, r1         # i
  ld $0x3, r2        # 3
  and r2, r1         # i & 3
  ld (r4, r1, 4), r5 # a[i & 3]
  and r2, r5         # a[i & 3] & 3
  ld (r6, r5, 4), r5 # b[a[i & 3] & 3]
  ld (r6, r1, 4), r7 # b[i & 3]
  and r2, r7         # b[i & 3] & 3
  ld (r4, r7, 4), r7 # a[b[i & 3] & 3]
  ld $0x1, r2        # 1
  not r7             # two's complement -a[b[i & 3] & 3]: negate
  add r2, r7         # add 1
  add r5, r7         # b[a[i & 3] & 3] - a[b[i & 3] & 3]
  ld (r3, r0, 4), r2 # d[i]
  add r2, r7         # b[a[i & 3] & 3] - a[b[i & 3] & 3] + d[i];
  ld (r6, r0, 4), r2 # b[i]
  st r7, (r3, r2, 4) # d[b[i]] = b[a[i & 3] & 3] - a[b[i & 3] & 3] + d[i];

  halt

.pos 0x200
  a: .long	0 # 0x200
     .long	11
     .long	2
     .long	0
     .long	1
     .long	2
     .long	0
     .long	1
  b: .long	2 #0x220
     .long	12
     .long	0
     .long	2
     .long	1
     .long	0
     .long	2
     .long	1
  c: .long	99 #0x240
     .long	6
     .long	2
     .long	1
     .long	0
     .long	2
     .long	1
     .long	0
  i: .long	5 # 0x260
  d: .long 0x240 # 0x264
