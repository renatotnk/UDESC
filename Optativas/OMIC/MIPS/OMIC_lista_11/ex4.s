    .section .rodata
fim10:
    .long 10
    
    .text
    .globl intToString
    .type intToString, @function
intToString:
    pushq %rbp
    movq %rsp, %rbp

    #intToString(int i, string* c)
    movl %edi, %ecx
    movq %rsi, %r9
    cmpl $0, %ecx   #verficiar se int = 0
    je zeroo
    jl negativo
    jmp inverter
zeroo:
    movb $48, (%r9) # 48 = 0 em asc
    incq %r9
    jmp inverter
negativo:
    negl %ecx
    movb $'-', (%r9)
    incq %r9
    incq %rsi
loop:
    movl $0, %edx
    divl fim10
    addb $48, %dl
    incq %rcx
    cmpl $0, %eax
    jne loop
inverter:  
    movb $0, (%r9)
    decq %r9
loopInverter:
    cmpq %rcx, %rsi
    jae fimFunc
    movb (%rsi), %al
    movb (%r9), %dl
    movb %al, (%r9)
    movb %dl, (%rsi)
    incq %rsi
    decq %r9
    jmp loopInverter
fimFunc:
    movq %rbp, %rsp
    popq %rbp
    ret


