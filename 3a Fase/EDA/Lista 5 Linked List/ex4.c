#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ListaDupla.h"

void mostra_invertido(LDE l,void (*mostra)(void *)){
  if(lista_vazia(l)){
    printf("Lista Vazia!\n");
  }else{
    ElementoDuplo *p = l.cabeca;
    int cont = 0;
    while(p->suc != NULL){
      p = p->suc;
    }
    while(p->ant != NULL){
      mostra(p->info);
      p = p->ant;
    }
  }
}
