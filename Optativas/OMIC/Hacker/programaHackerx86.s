	.file	"programaHackerx86.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"Digite ni para calcular fib(n) ou -1 para sair: "
.LC1:
	.string	"%hd"
.LC2:
	.string	"fib(%hd) = %u\n"
.LC3:
	.string	"Valor invalido!"
.LC4:
	.string	"Fim!"
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
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, %eax
	call	validarSenha
	testl	%eax, %eax
	jne	.L2
	movl	$0, %eax
	jmp	.L6
.L2:
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-10(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movzwl	-10(%rbp), %eax
	testw	%ax, %ax
	js	.L4
	movzwl	-10(%rbp), %eax
	movzwl	%ax, %eax
	movl	%eax, %edi
	call	fibonacci
	movl	%eax, %edx
	movzwl	-10(%rbp), %eax
	cwtl
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L5
.L4:
	movzwl	-10(%rbp), %eax
	cmpw	$-1, %ax
	jge	.L5
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
.L5:
	movzwl	-10(%rbp), %eax
	cmpw	$-1, %ax
	jne	.L2
	leaq	.LC4(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
.L6:
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L7
	call	__stack_chk_fail@PLT
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata

.LC5:
	.string	"Digite a senha do programa: "
.LC6:
	.string	"%d"
.LC7:
	.string	"%d\n\n"
.LC8:
	.string	"Senha correta!"
	.align 8
.LC9:
	.string	"Senha incorreta!  Tentativa %d de %d.\n"
	.text
	.globl	validarSenha
	.type	validarSenha, @function
validarSenha:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -20(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L9
.L15:
	movl	$0, -16(%rbp)
	movl	$0, -12(%rbp)
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	
	leaq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC6(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	jmp	.L10
.L12:
	addl	$1, -12(%rbp)
	movl	-24(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	addl	%edx, -16(%rbp)
	movl	-24(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -24(%rbp)
.L10:
	movl	-24(%rbp), %eax
	testl	%eax, %eax
	je	.L11
	cmpl	$8, -12(%rbp)
	jle	.L12
.L11:
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC7(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-16(%rbp), %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$5, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	imull	$100, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax

	#cmpl	$42, %eax
	#jne	.L13
	#cmpl	$8, -12(%rbp)
	#jne	.L13
	#movl	-24(%rbp), %eax
	#testl	%eax, %eax
	#jne	.L13
	
	leaq	.LC8(%rip), %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L16
.L13:
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	$5, %edx
	movl	%eax, %esi
	leaq	.LC9(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -20(%rbp)
.L9:
	cmpl	$4, -20(%rbp)
	jle	.L15
	movl	$0, %eax
.L16:
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L17
	call	__stack_chk_fail@PLT
.L17:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	validarSenha, .-validarSenha
	.globl	fibonacci
	.type	fibonacci, @function
fibonacci:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movw	%ax, -20(%rbp)
	cmpw	$1, -20(%rbp)
	ja	.L19
	movl	$1, %eax
	jmp	.L20
.L19:
	movl	$1, -8(%rbp)
	movl	$1, -12(%rbp)
	movzwl	-20(%rbp), %eax
	subl	$1, %eax
	movw	%ax, -20(%rbp)
	jmp	.L21
.L22:
	movl	-12(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	addl	%eax, -12(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, -8(%rbp)
	movzwl	-20(%rbp), %eax
	subl	$1, %eax
	movw	%ax, -20(%rbp)
.L21:
	cmpw	$0, -20(%rbp)
	jne	.L22
	movl	-12(%rbp), %eax
.L20:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	fibonacci, .-fibonacci
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
