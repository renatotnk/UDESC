#constantes
	.equ STDIN, 0
	.equ STDOUT, 1
	.equ WRITE, 1
	.equ READ, 0
	.equ EXIT, 60
#posições na STACK
	.equ aLetter, -16
	.equ localSize, -16

	.section .rodata
prompt:
	.string "Entre com o caractere: "
	#o tamamho da mensagem é o tamanho da string -1
	.equ promptSz,.-prompt-1
msg:
	.string "Voce entrou: "
	.equ msgSz,.-msg-1

	.text
	.globl __start
	.type __start, @function
__start:
	pushq %rbp				#salvar o frame pointer do caller
	movq %rsp, %rbp			#setar o frame pointer do main
	addq $localSize, %rsp	#ajustar a pilha
	
	movl $promptSz, %edx	#tamanho da string em edx
	movl $prompt, %esi		#endereço da string em esi
	movl $STDOUT, %edi		#stdout em edi
	movq $WRITE, %rax
	syscall

	movl $2, %edx		#ler 1 caractere + \n
	leaq aLetter(%rbp), %rsi	#calcular o endr de aLetter e armazenar em rsi
	movl $STDIN, %edi	#stdin
	movq $READ, %rax
	syscall
	
	movl $msgSz, %edx
	movl $msg, %esi
	movl $STDOUT, %edi
	movq $WRITE, %rax
	syscall

	movl $2, %edx
	leaq aLetter(%rbp), %rsi
	movl $STDOUT, %edi
	movq $WRITE, %rax
	syscall

	movq %rbp, %rsp	#remover as variáveis locais
	popq %rbp		#restaurar o frame pointer
	movq $EXIT, %rax
	movq $0, %rdi
	syscall
	
