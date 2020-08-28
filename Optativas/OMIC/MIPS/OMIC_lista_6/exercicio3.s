	.section .rodata
ola_mundo:
	.string "Ola Mundo Cruel\n"
	.equ ola_size, .-ola_mundo-1 	#endereco de memoria onde a string termina - endereco onde comeca
	
format:	.ascii "%s\0"

	.text
	.globl main
	.type main, @function

main:
	pushq %rbp
	movq %rsp, %rbp	

	movl $format, %edi
	movq $ola_mundo, %rsi
	call printf

	movl $0, %eax
	movq %rbp, %rsp
	popq %rbp
	ret
