    .text
    .globl fatorial
    .type fatorial, @function
fatorial:
    pushq %rbp
    movq %rsp, %rbp

    movl $1, %eax

loop:
    cmpl $1, %edi
    jle endLoop
    mull %edi
    decl %edi
    jmp loop

endLoop:
    movq %rbp, %rsp
    popq %rbp
    ret