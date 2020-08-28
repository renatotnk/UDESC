#include <stdio.h>
#include <stdlib.h>
#include "PilhaGenerica.h"

int main(){
PilhaGenerica p1;
inicializa_pilha(&p1,6,sizeof(float));
float x = 3,y;
empilha(&p1,&x);
x = 6;
empilha(&p1,&x);
x = 9;
empilha(&p1,&x);
desempilha(&p1,&y);
printf("Valor removido : %f\n",y); 
mostra_pilha(p1,mostra_float);
desempilha(&p1,&y);
desaloca_pilha(&p1);

}
