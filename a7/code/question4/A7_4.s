.pos  0x0             // stack setup
ld    $0x1028, r5     // setup stack
ld    $0xfffffff4, r0 // alloc space on    stack
add   r0, r5          // ...
ld    $0x200, r0      // load 0x200
ld    0x0(r0), r0     // ...
st    r0, 0x0(r5)     // store 0x200 into stack
ld    $0x204, r0      // load 0x204
ld    0x0(r0), r0     // ..
st    r0, 0x4(r5)     // store 0x204 into stack
ld    $0x208, r0      // load 0x208
ld    0x0(r0), r0     // ..
st    r0, 0x8(r5)     // store 0x208 into stack
gpc   $6, r6          // save return pointer
j     0x300           // run 0x300
ld    $0x20c, r1      // store output of 0x300 into 0x20c
st    r0, 0x0(r1)     // ...
halt
.pos  0x200
.long 0x00000000
.long 0x00000000
.long 0x00000000
.long 0x00000000

.pos 0x300           // function foo
ld   0x0(r5), r0     // read arg0
ld   0x4(r5), r1     // read arg1
ld   0x8(r5), r2     // read arg 2
ld   $0xfffffff6, r3 // -10
add  r3, r0          // add -10 to r0 arg0-10
mov  r0, r3          // copy r0 to r3
not  r3              // !r3
inc  r3              // -r3
bgt  r3, L6          // -r3 > 0, 10 > arg0, jump to L6
mov  r0, r3          // copy r0 to r3
ld   $0xfffffff8, r4 // r4 = -8
add  r4, r3          // r3 = arg0-8-10
bgt  r3, L6          // arg0-18>0, arg0 > 18, jump to L6
ld   $0x400, r3      // r3 = 0x400
j    *(r3, r0, 4)    // jump to 0x400[arg0-10];

.pos 0x330
add  r1, r2
br   L7
not  r2
inc  r2
add  r1, r2
br   L7
not  r2       // 0x33C
inc  r2
add  r1, r2
bgt  r2, L0
ld   $0x0, r2
br   L1

L0:
	ld $0x1, r2

L1:
	br  L7
	not r1       // 0x354
	inc r1
	add r2, r1
	bgt r1, L2
	ld  $0x0, r2
	br  L3

L2:
	ld $0x1, r2

L3:
	br  L7       // 0x36C
	not r2
	inc r2
	add r1, r2
	beq r2, L4
	ld  $0x0, r2
	br  L5

L4:
	ld $0x1, r2

L5:
	br L7 // 0x384

L6:
	ld $0x0, r2 // return 0
	br L7       // jump done

L7:  // done
	mov r2, r0
	j   0x0(r6) // return r2

	.pos  0x400
	.long 0x00000330
	.long 0x00000384
	.long 0x00000334
	.long 0x00000384
	.long 0x0000033c
	.long 0x00000384
	.long 0x00000354
	.long 0x00000384
	.long 0x0000036c
	.pos  0x1000
	.long 0x00000000
	.long 0x00000000
	.long 0x00000000
	.long 0x00000000
	.long 0x00000000
	.long 0x00000000
	.long 0x00000000
	.long 0x00000000
	.long 0x00000000
	.long 0x00000000
