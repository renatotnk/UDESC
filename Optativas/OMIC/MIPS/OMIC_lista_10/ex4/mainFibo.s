    .equ localSize, -16
    .equ inteiro1, -16
    .equ QUEBRA, -1
    .section .rodata
formatoPrintInteiro:
    .string "%d"
formatoPrintFibo:
    .string "fibo : %d\n"
.text
	.globl main
	.type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    addq $localSize, %rsp
    jmp loop_scanf
loop_scanf:
    movq $formatoPrintInteiro, %rdi
    leaq inteiro1(%rbp), %rsi
    movq $0, %rax
    call scanf

    movl inteiro1(%rbp), %edi

    cmpl $-1, %edi
    je fim

    movl $0, %esi
    movl $1, %edx
    movl $1, %ecx 
    call fibo

    jmp print_fibo
print_fibo:
    movq $formatoPrintFibo, %rdi
    movq %rax, %rsi	
	movq $0, %rax		#0 em rax para ausencia de argumentos em ponto flutuante
	call printf

    jmp loop_scanf
fim:
    movq $0, %rax
    movq %rbp, %rsp
    popq %rbp
    ret