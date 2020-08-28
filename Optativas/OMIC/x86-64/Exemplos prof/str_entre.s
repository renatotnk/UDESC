#constantes
	.equ STDOUT,1
	.equ STDIN, 0
	.equ localSize, -16
	.equ aLetter, -16

	.section .rodata #dados somente leitura
str_entre: 
	.string "Entre com o caractere: " #string terminada com \0
	.equ str_entreSz, .-str_entre-1
	.text #seção de texto
	.globl main #main visível globalmente
	.type main, @function
main: #inicio do main
	pushq %rbp #salva stack frame na pilha
	movq %rsp, %rbp #define novo stack frame

	movl $str_entreSz, %edx #terceiro argumento
	movq $str_entre, %rsi #segundo argumento
	movl $STDOUT, %edi #primeiro argumento
	call write #chama a função write

	movl $STDIN, %edi
	leaq aLetter(%rbp), %rsi
	movl $2, %edx
	call read

	movl $STDOUT, %edi
	leaq aLetter(%rbp), %rsi
	movl $2, %edx
	call write

	movl $0, %eax #return 0
	movq %rbp, %rsp #restaura a pilha
	popq %rbp #restaura o stack frame
	ret #retorna ao chamador

