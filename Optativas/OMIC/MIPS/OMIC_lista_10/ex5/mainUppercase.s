    .equ localSize, -80
    .equ POS_STR, -80
    .section .rodata

solicita:
    .string "Digite uma string: "

formatoString:
    .string "%s"

.text
	.globl main
	.type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    addq $localSize, %rsp

    movq $solicita, %rdi	#endereco de string em edi
	movq $0, %rax		#0 em rax para ausencia de argumentos em ponto flutuante
	call printf

    movq $formatoString, %rdi	#movendo %s para argumento 1
	leaq POS_STR(%rbp), %rsi	#movendo posicao da pilha para armazenar a string para o registrador
	movq $0, %rax			    #nao e ponto flutuante, passando 0 em rax
	call scanf

    movq POS_STR(%rbp), %rsi
    call upper

    movq $formatoString, %rdi	#endereco de string em edi
    movq POS_STR(%rbp), %rsi
	movq $0, %rax		#0 em rax para ausencia de argumentos em ponto flutuante
	call printf

    movq $0, %rax
    movq %rbp, %rsp
    popq %rbp
    ret