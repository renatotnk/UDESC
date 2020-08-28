#constantes
	.equ STDOUT, 1
    .equ TAM_PILHA, -16
    .equ POS_PTR, -8
    .equ SYSCALL_WRITE, 1
    .equ SYSCALL_EXIT, 60

    .section .rodata
STR_OLA:
	.string "Ola\n"

    .text
	.globl __start
	.type __start, @function
__start:
    pushq %rbp
    movq %rsp, %rbp
    addq $TAM_PILHA, %rsp

    movq $STR_OLA, POS_PTR(%rbp)
loop:
    movq POS_PTR(%rbp), %rsi
    cmpb  $0, (%rsi)
    je fim_loop

    movl $1, %edx
    movq $STDOUT, %rdi
    movq $SYSCALL_WRITE, %rax
    syscall

    incq POS_PTR(%rbp)
    movq POS_PTR(%rbp), %rsi
    jmp loop
fim_loop:
    movq %rbp, %rsp
    popq %rbp
    movl $0, %eax
    movq $SYSCALL_EXIT, %rax
    syscall




