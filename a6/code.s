.pos 0x100
start:
	ld   $stackBtm, r5       # [01] sp = address of last word of stack
	inca r5                  # [02] sp = address of word after stack
	gpc  $0x6, r6            # [03] r6 = pc + 6
	j    copy                 # [04] call copy()
	halt

.pos 0x200
copy:
	deca r5 # allocate 12 bytes for stack
	st   r6, 0x0(r5)         # [06] save ra on stack
	deca r5 #
	deca r5 #
	mov r5, r1

	ld $src, r2

	ld $0, r0 # r0 = i

	cond:
	ld (r2, r0, 4), r3
	beq r3, end
	loop:
	st r3, (r1, r0, 4)
	inc r0
	br cond
	end:

	inca r5
	inca r5
	ld   0x0(r5), r6         # [17] load return address from stack
	inca r5                  # [18] deallocate callee part of copy's frame
	j    0x0(r6)             # [19] return


.pos 0x1000
src: .long 0x1
	.long 0x1
	.long 0x1010
	.long 0xff000000 # nop, load 0 into r0
	.long 0xffffffff # r0 = 0
	.long 0xff000100 # nop, load 0 into r0
	.long 0xffffffff # r0 = 0
	.long 0xff000200 # nop, load 0 into r0
	.long 0xffffffff # r0 = 0
	.long 0xff000300 # nop, load 0 into r0
	.long 0xffffffff # r0 = 0
	.long 0xff000400 # nop, load 0 into r0
	.long 0xffffffff # r0 = 0
	.long 0xff000500 # nop, load 0 into r0
	.long 0xffffffff # r0 = 0
	.long 0xff000600 # nop, load 0 into r0
	.long 0xffffffff # r0 = 0
	.long 0xff000700 # nop, load 0 into r0
	.long 0xffffffff # r0 = 0
	.long 0xff000000 # nop, load 0 into r0
	.long 0xffffffff # r0 = 0
	.long 0xf000f000

stackTop:
	.long 0x0
	.long 0x0
	.long 0x0
	.long 0x0
	.long 0x0
	.long 0x0
	.long 0x0
	.long 0x0
	.long 0x0
stackBtm:
	.long 0x0
