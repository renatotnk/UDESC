	#constantes
	.equ STDOUT, 1

	.section .rodata
ola_mundo:
	.string "Ola Mundo Cruel\n"
	.equ ola_size, .-ola_mundo-1 	#endereco de memoria onde a string termina - endereco onde comeca
	
	.text
	.globl main
	.type main, @function

main:
	pushq %rbp
	movq %rsp, %rbp	

	movl $STDOUT, %edi
	movq $ola_mundo, %rsi
	movl $ola_size, %edx
	call printf

	movl $0, %eax
	movq %rbp, %rsp
	popq %rbp
	ret
