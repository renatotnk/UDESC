#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

void mostra_float(void *x){
float *p = x; // isso eh igual a " *(float*)x "
printf("%.1f\n",*p);
}

int compara_float(float *a,float *b){
  if(*a == *b){
    return 0;
  }if(*a > *b){
    return 1;
  }return -1;
}

int main() {
  Lista l1;
  inicializa_lista(&l1,sizeof(float));
  float x = 7;
  insereNoInicio(&l1,&x);
  x = 11;
  insereNoInicio(&l1,&x);
  x = -1;
  insereNoInicio(&l1,&x);
  x = 9;
  insereNaPos(&l1,&x,1);
  leNaPosicao(&l1,&x,2);
  printf("%lf\n",x);
  x = 18;
  modificaNaPos(&l1,&x,2);
  mostraLista(l1,mostra_float);
}
