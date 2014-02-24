	.file	"isOddBetter.c"
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
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	cmpl	$2, %edi
	je	.L8
	movq	(%rsi), %rsi
	movl	$.LC2, %edi
	xorl	%eax, %eax
	call	printf
	movl	$1, %eax
.L4:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L8:
	.cfi_restore_state
	movq	8(%rsi), %rdi
	xorl	%eax, %eax
	call	atoi
	movl	$.LC0, %edi
	testb	$1, %al
	movl	$.LC1, %eax
	cmove	%rax, %rdi
	call	puts
	xorl	%eax, %eax
	jmp	.L4
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
	andl	$1, %eax
	ret
	.cfi_endproc
.LFE12:
	.size	isOdd, .-isOdd
	.ident	"GCC: (GNU) 4.8.2 20131219 (prerelease)"
	.section	.note.GNU-stack,"",@progbits
