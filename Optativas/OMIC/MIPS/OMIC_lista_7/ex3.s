#constantes
	.equ STDOUT,1
	.equ STDIN, 0
	.equ localSize, -16
	.equ twoLetters, -16
	.equ threeLetters, -13
	.equ allLetters, -16

	.section .rodata #dados somente leitura
str_entre1: 
	.string "Entre com os 2 caracteres: " #string terminada com \0
	.equ str_entre1Sz, .-str_entre1-1

str_entre2: 
	.string "Entre com os 3 caracteres: " #string terminada com \0
	.equ str_entre2Sz, .-str_entre2-1

	.text #seção de texto
	.globl main 
	.type main, @function
main: #inicio do main
	pushq %rbp 					#salva stack frame na pilha
	movq %rsp, %rbp 			#define novo stack frame
	addq $localSize, %rsp		#alocando espaco

	movl $str_entre1Sz, %edx 	#terceiro argumento
	movq $str_entre2, %rsi 		#segundo argumento
	movl $STDOUT, %edi 			#primeiro argumento
	call write 					#chama a função write

	movl $STDIN, %edi			#primeiro argumento
	leaq threeLetters(%rbp), %rsi	#ler tres caracteres
	movl $4, %edx				#contador de caracteres
	call read

	movl $str_entre2Sz, %edx 	#terceiro argumento
	movq $str_entre1, %rsi 		#segundo argumento
	movl $STDOUT, %edi 			#primeiro argumento
	call write 					#chama a função write

	movl $STDIN, %edi			#primeiro argumento
	leaq twoLetters(%rbp), %rsi	#ler dois caracteres
	movl $3, %edx				#contador de caracteres
	call read

	movl $STDOUT, %edi			#Primeiro argumento
	leaq allLetters(%rbp), %rsi	#Segundo argumento (todos os itens na pilha)
	movl $7, %edx				#Terceiro argumento
	call write

	movl $0, %eax 				#return 0
	movq %rbp, %rsp 			#restaura a pilha
	popq %rbp 					#restaura o stack frame
	ret 						#retorna ao chamador

