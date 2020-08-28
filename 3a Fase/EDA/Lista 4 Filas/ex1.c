#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "PilhaGenerica.h"
#include "FilaGenerica.h"

void mostra_int(void *x){
int *p = x; // isso eh igual a " *(float*)x "
printf("%.d\n",*p);
}

int main(){
FilaGenerica f1;
int c,x,y;
srand(time(NULL));
printf("Qual o tamanho da fila?\n");
scanf("%d",&c);
inicializa_fila(&f1,c,sizeof(int));
while(!fila_cheia(f1)){
  x = rand()%100;
  inserir(&f1,&x);
}
mostra_fila(f1,mostra_int);
PilhaGenerica p1;
inicializa_pilha(&p1,c,sizeof(int));
while(!fila_vazia(f1)){
  remover(&f1,&x);
  empilha(&p1,&x);
}
mostra_pilha(p1,mostra_int);
while(desempilha(&p1,&y) != ERRO_PILHA_VAZIA){
  inserir(&f1,&y);
}
mostra_fila(f1,mostra_int);
desaloca_fila(&f1);
desaloca_pilha(&p1);
}
