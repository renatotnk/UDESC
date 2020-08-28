#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaGenerica.h"

void mostra_float(void *x){
float *p = x; // isso eh igual a " *(float*)x "
printf("%.1f\n",*p);
}

int main(){
  FilaGenerica f1;
  inicializa_fila(&f1,10,sizeof(float));
  float x = 2,y;
  inserir(&f1,&x);
  x = 4;
  inserir(&f1,&x);
  x = 8;
  inserir(&f1,&x);
  mostra_fila(f1,mostra_float);
  remover(&f1,&y);
  printf("Valor Removido: %.1f\n",y); /*FIRST IN FIRST OUT*/
  desaloca_fila(&f1);

}
