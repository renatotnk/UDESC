#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

void selection_sort_lista(Lista *l,int (*compara)(void *, void *)){
  if(!lista_vazia(*l)){
    Elemento *i;
    for(i = l->cabeca; i->proximo != NULL; i = i->proximo){
      Elemento *i_menor;
      Elemento *j;
      for(j = i->proximo; j != NULL; j = j->proximo){
        if(compara(j->info,i_menor->info) < 0){
          i_menor = j;
        }
      }
      void *temp = i->info;
      i->info = i_menor->info;
      i_menor->info = temp;
    }
  }
}
