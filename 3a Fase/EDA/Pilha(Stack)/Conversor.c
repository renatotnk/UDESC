#include <stdio.h>
#include "PilhaGenerica.h"
int main(){
  int x;
  printf("digite o numero para conversao\n");
  scanf("%d",&x);
  inicializa_pilha(&p1,32,sizeof(int));
  int resto;
  do{
    resto = (x % 2);
    empilha(&p1,&resto);
    x = x / 2;
  }while (x > 0);
  while(!pilha_vazia(p1)){ /* while(desempilha(&p1,&x) != ERRO_PILHA_VAZIA) */
  desempilha(&p1,&x);
  prinf("%d",x);
  }
  printf("\n");
  desaloca_pilha(&p1);
}
