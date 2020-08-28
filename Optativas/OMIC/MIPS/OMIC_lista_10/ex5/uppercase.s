    .equ TAM_PILHA, -80
    .equ PTR_PILHA, -80
.text
    .globl upper
    .type upper, @function
upper:
    pushq %rbp
    movq %rsp, %rbp
    addq TAM_PILHA, %rsp
    
    addq %rdi, %rsp
#rdi, rsi, edx, ecx, r8, r9
loop:
    cmpq $0, %rdi
    je fim

    cmpb $97, (%rsp)    # 'a' = 97     #compara tabela ascii 
    jl avanca
    cmpb $122, (%rsp)   # 'z' = 122    
    jg avanca
    addq $-32, (%rsp)  # 'a' - 'A' = 32

    jmp avanca

avanca:
  addq $1, %rsp
  jmp loop

fim:
    movq %rbp, %rsp
    popq %rbp
    ret
