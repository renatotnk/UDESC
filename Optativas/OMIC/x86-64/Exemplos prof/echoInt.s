#constantes
	.equ LOCAL_SIZE,-16
	.equ POS_LETRA,-4
	
	.section .rodata
solicita:
	.string "Digite um inteiro: "
format_scanf:
	.string "%d"
format_print:
	.string "Voce digitou %d\n"

	.text
	.globl main
	.type main, @function
main:
	pushq %rbp			#alocando pilha
	movq %rsp, %rbp		#ajustand frame pointer
	addq $LOCAL_SIZE, %rsp # alocando espaco na pilha para scanf
	
	movq $solicita, %rdi	#endereco de string em edi
	movq $0, %rax		#0 em rax para ausencia de argumentos em ponto flutuante
	call printf

	movq $format_scanf, %rdi	#movendo %d para argumento 1
	leaq POS_LETRA(%rbp), %rsi	#movendo posicao da pilha para armazenar o inteiro para o registrador
	movq $0, %rax			#nao e ponto flutuante, passando 0 em rax
	call scanf

	movq $format_print, %rdi
	movl POS_LETRA(%rbp), %esi
	movq $0, %rax
	call printf

	movl $0, %eax
	movq %rbp, %rsp		#reajustando frame pointer
	popq %rbp			#liberando pilha
	ret
