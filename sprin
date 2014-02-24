	.file	"isOdd.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"true"
.LC1:
	.string	"false"
.LC2:
	.string	"Usage: '%s <number>'\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	cmpl	$2, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	%edi, %ebx
	je	.L8
	movq	(%rsi), %rsi
	movl	$.LC2, %edi
	xorl	%eax, %eax
	call	printf
	movl	$1, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L8:
	.cfi_restore_state
	movq	8(%rsi), %rdi
	xorl	%eax, %eax
	call	atoi
	cltd
	movl	$.LC0, %edi
	idivl	%ebx
	movl	$.LC1, %eax
	testl	%edx, %edx
	cmove	%rax, %rdi
	call	puts
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.text
	.p2align 4,,15
	.globl	isOdd
	.type	isOdd, @function
isOdd:
.LFB12:
	.cfi_startproc
	movl	%edi, %eax
	shrl	$31, %eax
	addl	%eax, %edi
	andl	$1, %edi
	cmpl	%eax, %edi
	setne	%al
	ret
	.cfi_endproc
.LFE12:
	.size	isOdd, .-isOdd
	.ident	"GCC: (GNU) 4.8.2 20131219 (prerelease)"
	.section	.note.GNU-stack,"",@progbits
