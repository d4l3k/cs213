.pos 0x100
start:
    ld $sb, r5
    inca    r5
    gpc $6, r6
    j main
    halt

f:
    deca r5
    ld $0, r0
    ld 4(r5), r1
    ld $0x80000000, r2
f_loop:
    beq r1, f_end
    mov r1, r3
    and r2, r3
    beq r3, f_if1
    inc r0
f_if1:
    shl $1, r1
    br f_loop
f_end:
    inca r5
    j(r6)

main:
    deca r5
    deca r5
    st r6, 4(r5)
    ld $8, r4
main_loop:
    beq r4, main_end
    dec r4
    ld $x, r0
    ld (r0,r4,4), r0
    deca r5
    st r0, (r5)
    gpc $6, r6
    j f
    inca r5
    ld $y, r1
    st r0, (r1,r4,4)
    br main_loop
main_end:
    ld 4(r5), r6
    inca r5
    inca r5
    j (r6)

.pos 0x2000
x:
    .long 1
    .long 2
    .long 3
    .long 0xffffffff
    .long 0xfffffffe
    .long 0
    .long 184
    .long 340057058

y:
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0

.pos 0x8000
# These are here so you can see (some of) the stack contents.
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
sb: .long 0

