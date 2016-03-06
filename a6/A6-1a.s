.pos 0x100

	ld $0, r0 # r0 = i
	ld $5, r1
	ld $s, r3
	ld (r3), r3 # r3 = s
	ld $a, r5 # &a

cond:
	mov r0, r2
	not r2
	inc r2
	add r1, r2
	bgt r2, loop # jump to loop if (i < 5)
	br end

	loop:
	ld (r5, r0, 4), r6 # a[i]
	bgt r6, if # if (a[i] > 0)
	br endif
	if:
	add r6, r3 # s+=a[i]

	endif:
	inc r0
	br cond

	end:
	ld $i, r7 # &i
	st r0, (r7) # i = r0

	ld $s, r7 # &s
	st r3, (r7) # s = r3
	halt




.pos 0x500
i: .long 10 # i
a: .long 10 # a[0]
   .long 0xFFFFFFE2 # a[1] = -30
	 .long 0xFFFFFFF4 # a[2] = -12
	 .long 4 # a[3]
	 .long 8 # a[4]
s: .long 0
