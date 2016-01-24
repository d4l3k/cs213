	.file	"a2_2.c"
	.globl	a
	.data
	.align 32
	.type	a, @object
	.size	a, 32
a:
	.long	0
	.long	11
	.long	2
	.long	0
	.long	1
	.long	2
	.long	0
	.long	1
	.globl	b
	.align 32
	.type	b, @object
	.size	b, 32
b:
	.long	2
	.long	12
	.long	0
	.long	2
	.long	1
	.long	0
	.long	2
	.long	1
	.globl	c
	.align 32
	.type	c, @object
	.size	c, 32
c:
	.long	99
	.long	6
	.long	2
	.long	1
	.long	0
	.long	2
	.long	1
	.long	0
	.globl	i
	.align 4
	.type	i, @object
	.size	i, 4
i:
	.long	5
	.globl	d
	.align 8
	.type	d, @object
	.size	d, 8
d:
	.quad	c
	.section	.rodata
.LC0:
	.string	"a[%d]==%d\n"
.LC1:
	.string	"b[%d]==%d\n"
.LC2:
	.string	"c[%d]==%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	i(%rip), %ecx
	movl	i(%rip), %eax
	addl	$1, %eax
	cltq
	movl	a(,%rax,4), %edx
	movl	i(%rip), %eax
	addl	$2, %eax
	cltq
	movl	b(,%rax,4), %eax
	addl	%eax, %edx
	movslq	%ecx, %rax
	movl	%edx, a(,%rax,4)
	movq	d(%rip), %rax
	movl	i(%rip), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	movl	i(%rip), %eax
	cltq
	movl	a(,%rax,4), %ecx
	movl	i(%rip), %eax
	cltq
	movl	b(,%rax,4), %eax
	addl	%ecx, %eax
	movl	%eax, (%rdx)
	movq	d(%rip), %rax
	movl	i(%rip), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	movl	i(%rip), %eax
	cltq
	movl	b(,%rax,4), %eax
	cltq
	movl	a(,%rax,4), %ecx
	movl	i(%rip), %eax
	cltq
	movl	a(,%rax,4), %eax
	cltq
	movl	b(,%rax,4), %eax
	addl	%ecx, %eax
	movl	%eax, (%rdx)
	movq	d(%rip), %rdx
	movl	i(%rip), %eax
	cltq
	movl	b(,%rax,4), %eax
	cltq
	salq	$2, %rax
	addq	%rax, %rdx
	movl	i(%rip), %eax
	andl	$3, %eax
	cltq
	movl	a(,%rax,4), %eax
	andl	$3, %eax
	cltq
	movl	b(,%rax,4), %ecx
	movl	i(%rip), %eax
	andl	$3, %eax
	cltq
	movl	b(,%rax,4), %eax
	andl	$3, %eax
	cltq
	movl	a(,%rax,4), %eax
	movl	%ecx, %esi
	subl	%eax, %esi
	movq	d(%rip), %rax
	movl	i(%rip), %ecx
	movslq	%ecx, %rcx
	salq	$2, %rcx
	addq	%rcx, %rax
	movl	(%rax), %eax
	addl	%esi, %eax
	movl	%eax, (%rdx)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	-4(%rbp), %eax
	cltq
	movl	a(,%rax,4), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -4(%rbp)
.L2:
	cmpl	$7, -4(%rbp)
	jle	.L3
	movl	$0, -8(%rbp)
	jmp	.L4
.L5:
	movl	-8(%rbp), %eax
	cltq
	movl	b(,%rax,4), %edx
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -8(%rbp)
.L4:
	cmpl	$7, -8(%rbp)
	jle	.L5
	movl	$0, -12(%rbp)
	jmp	.L6
.L7:
	movl	-12(%rbp), %eax
	cltq
	movl	c(,%rax,4), %edx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -12(%rbp)
.L6:
	cmpl	$7, -12(%rbp)
	jle	.L7
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 5.3.0"
	.section	.note.GNU-stack,"",@progbits
