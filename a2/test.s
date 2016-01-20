ld $0x1000, r1        # Loads 0x1000 into r1
ld $0x2000, r2        # Loads 0x2000 into r2
ld $0x0009, r3        # Loads 9 into r3
st r1, 8(r1)          # should load 0x1000 into 0x1020
st r1, (r2,r3,4)      # should load 0x2000 into 0x1024
ld 8(r1), r4          # should load 0x1000 into r4
ld (r1, r3, 4), r5    # should load 0x2000 into r5

ld $0x1, r0
ld $0x2, r1
ld $0x3, r2
mov r0, r5 # r5 should be 1
add r2, r0 # r0 should be 4
and r1, r2 # r2 should be 2
inc r2 # r2 should be 3
inca r0 # r0 should be 8
dec r0 # r0 should be 7
deca r0 # r0 should be 3
shr $0x1, r0 # r0 should be 1
shl $0x2, r0 # r0 should be 4

ld $0x0, r4
not r4 # r4 should be -1

nop # should do nothing
halt
