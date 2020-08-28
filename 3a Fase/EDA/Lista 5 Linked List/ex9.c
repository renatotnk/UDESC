#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDupla.h"

void inverte_lista(LDE l){
  if(!lista_vazia(l)){
    ElementoDuplo *p1 = l.cabeca;
    ElementoDuplo *p2 = l.cabeca;
    while(p2->suc != NULL){
      p2 = p2->suc;
    }
    while( (p1 != p2) && (p1 != p2->suc) ){
      void *temp = p1->info;
      p1->info = p2->info;
      p2->info = temp;
      p1 = p1->suc;
      p2= p2->ant;
    }
  }
}
