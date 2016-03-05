.pos 0x1000

  br beq
	halt

	beq:
	ld $0, r0
	ld $1, r1
	beq r1, bad
	beq r0, bgt
	halt

	bgt:
	bgt r0, bad
	bgt r1, jump
	halt

	jump:
	j getpc
	halt

	getpc:
	gpc $2, r2
	j 2(r2)
	halt

	nop
	halt




	bad: halt
