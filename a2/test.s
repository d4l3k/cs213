ld $0x1000, r1        # Loads 0x1000 into r1
ld $0x2000, r2        # Loads 0x2000 into r2
ld $0x0009, r3        # Loads 9 into r3
st r1, 8(r1)          # should load 0x1000 into 0x1020
st r1, (r2,r3,4)      # should load 0x2000 into 0x1024
ld 8(r1), r4          # should load 0x1000 into r4
ld (r1, r3, 4), r5    # should load 0x2000 into r5
halt

