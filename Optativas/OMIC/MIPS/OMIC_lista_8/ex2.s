#posições na stack
	.equ inteiro1, -4
	.equ inteiro2, -8
	.equ localSize, -16
	.section .rodata 
prompt1:
	.string "Digite um inteiro: "
prompt2:
	.string "Digite outro inteiro: "
scanFormat:
	.string "%i"
printFormat:
	.string "Soma: %i\n"

	.text
	.globl main
	.type main, @function

main:
	pushq %rbp				#salvar rbp
	movq %rsp,%rbp			#estabelecer novo frame pointer
	addq $localSize, %rsp	#alocar espaço na pilha

	movq $prompt1, %rdi 	#endereço da string em edi
	movq $0, %rax			#0 em rax para ausência de argumentos em ponto flutuante
	call printf				#jump and link para printf

	leaq inteiro1(%rbp),%rsi #endereço do inteiro1 na pilha para rsi
	movq $scanFormat, %rdi 	#endereço da string em edi
	movq $0, %rax			#sem ponto flutuante
	call scanf				#jump and link para scanf

	movq $prompt2, %rdi 	#endereço da string em edi
	movq $0, %rax			#0 em rax para ausência de argumentos em ponto flutuante
	call printf				#jump and link para printf

	leaq inteiro2(%rbp),%rsi #endereço do inteiro2 na pilha para rsi
	movq $scanFormat, %rdi 	#endereço da string em edi
	movq $0, %rax			#sem ponto flutuante
	call scanf				#jump and link para scanf

	addq inteiro1(%rbp), %rsi
	addq inteiro2(%rbp), %rsi

	movq %rsi,%rsi #copia o inteiro da pilha para rsi
	movq $printFormat, %rdi	 #endereço da string de formatação em edi
	movq $0, %rax			 #sem ponto flutuante
	call printf

	movl $0, %eax
	movq %rbp, %rsp
	popq %rbp
	ret


