# Montando o programa: as exercicio4.s --gstabs -o exercicio4.o
# Linkedição/executar: gcc exercicio4.o -o exercicio4

    .text
    .globl main
    .type main, @function
main:
    pushl %rbp          # salvar o frame pointer na pilha
    movl %rsp, %rbp     # copiar o stack pointer para o frame pointer
    movl $0, %eax       # EAX = 32
    movl %rbp, %rsp     # voltar a pilha para a posição original
    popl %rbp           # carregar o valor salvo do frame pointer da pilha
    ret                    # retornar ao chamador

