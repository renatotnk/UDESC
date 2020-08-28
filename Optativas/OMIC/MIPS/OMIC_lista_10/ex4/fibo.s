.text
    .globl fibo
    .type fibo, @function
fibo:
    pushq %rbp
    movq %rsp, %rbp

    jmp fibo_loop
#rdi, rsi, edx, ecx, r8, r9

fibo_loop:
    cmpl $1, %edi       # while(n > 0)
    je fim_loop

    addl %esi, %ecx     # aux += a
    addl %edx, %ecx     # aux += b

    movl %edx, %esi     # a = b
    movl %ecx, %edx     # b = aux

    subq $1, %rdi       # n--
    jmp fibo_loop 
#Porque calcula valores errados???

fim_loop:
    movl %edx, %eax     # return aux
    movq %rbp, %rsp
    popq %rbp
    ret




#int result=1,term1=0,term2=1,;
#    while(n = 0)
#    {
#        result = term1 + term2;
#        term1 = term2;
#        term2 = result;
#        n--;
#    }
