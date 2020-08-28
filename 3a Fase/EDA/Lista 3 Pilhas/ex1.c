#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex1.h"

int main(){
PilhaDupla q;
int capacidade;
printf("Digite a capacidade da pilha dupla\n");
scanf("%d",&capacidade);
inicializa(&q,capacidade,sizeof(int));
int x = 3,y,z;
empilha1(&q,&x);
x = 6;
empilha2(&q,&x);
x = 9;
empilha1(&q,&x);
desempilha1(&q,&y);
desempilha2(&q,&z);
printf("Valor removido da pilha 1 : %d\n",y);
printf("Valor removido da pilha 2 : %d\n",z);

}
