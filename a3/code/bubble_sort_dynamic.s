.pos 0x100
  ld $0x200, r0
  ld (r0), r0
  ld $0x204, r1
  ld (r1), r1
  ld $0x208, r2
  ld (r2), r2
  ld (r2, r0, 4), r3
  ld (r2, r1, 4), r4
  st r3, (r2, r1, 4)
  st r4, (r2, r0, 4)


  halt

.pos 0x200
# Data area

i:   .long 0
j:   .long 0
val: .long 0x300

.pos 0x300
      .long 1
      .long 2
      .long 3
      .long 4
