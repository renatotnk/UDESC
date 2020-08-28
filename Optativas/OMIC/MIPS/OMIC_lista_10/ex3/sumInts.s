.text
	.globl sumInts
	.type sumInts, @function
sumInts:
    pushq %rbp
    movq %rsp, %rbp

#rdi, rsi, edx, ecx, r8, r9
    addl %edi, %esi
    movl %esi, (%rdx)

    jo overflow

    movq $0, %rax
    jmp fim_funcao

overflow:
    movl $1, %eax
    jmp fim_funcao

fim_funcao:
    movq %rbp, %rsp
    popq %rbp
    ret