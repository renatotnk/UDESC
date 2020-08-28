    .text
    .globl divisao
    .type divisao, @function
divisao:
    pushq %rbp
    movq %rsp, %rbp

    movq %rdx, %r9
    movl %edi, %eax
    cdq
    idivl %esi
    movl %edx, (%r9)

    movq %rbp, %rsp
    popq %rbp
    ret