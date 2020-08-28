    .equ localSize, -16
    .equ inteiro1, -16
    .section .rodata
formatoPrintInteiro:
    .string "%d\n"

formatoPrintString:
    .string "%s\n"


s_overflow:
    .string "Overflow\n"
.text
	.globl main
	.type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    addq $localSize, %rsp

    movl $42, %edi
    movl $10, %esi
    leaq inteiro1(%rbp), %rdx
    call sumInts

    cmpq $1, %rax
    je print_overflow

    jmp print_inteiro
    

print_inteiro:
    movl inteiro1(%rbp), %esi	
    movq $formatoPrintInteiro, %rdi
	movq $0, %rax		#0 em rax para ausencia de argumentos em ponto flutuante
	call printf
    jmp fim

print_overflow:
    movl s_overflow, %esi	
    movq $formatoPrintString, %rdi
	movq $0, %rax		#0 em rax para ausencia de argumentos em ponto flutuante
	call printf
    jmp fim

fim:
    movq %rbp, %rsp
    popq %rbp
    ret