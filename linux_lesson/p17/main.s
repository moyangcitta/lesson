	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$64, %esp
	movl	$0, 60(%esp)
	movl	$1, 20(%esp)
	movl	$2, 24(%esp)
	movl	$3, 28(%esp)
	movl	$4, 32(%esp)
	movl	$5, 36(%esp)
	movl	$6, 40(%esp)
	movl	$7, 44(%esp)
	movl	$8, 48(%esp)
	movl	$9, 52(%esp)
	movl	$0, 56(%esp)
	jmp	.L2
.L3:
	movl	60(%esp), %eax
	movl	20(%esp,%eax,4), %edx
	movl	$.LC0, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	addl	$1, 60(%esp)
.L2:
	cmpl	$9, 60(%esp)
	jle	.L3
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.6 20120305 (Red Hat 4.4.6-4)"
	.section	.note.GNU-stack,"",@progbits
