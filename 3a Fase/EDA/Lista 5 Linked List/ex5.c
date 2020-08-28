#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Lista.h"


/*item b*/
void mostra_invertido_b(Lista l,void (*mostra)(void *)){
  if(lista_vazia(l)){
    printf("Lista Vazia!\n");
  }else{
    percorre(l.cabeca,mostra);
  }
}

void percorre_b(Elemento *p,void (*mostra)(void *)){
  if(p != NULL){
    mostra(p->info);
    percorre(p->proximo,mostra);
  }
}

void percorre_invertido_b(Elemento *p,void (*mostra)(void *)){
  if(p != NULL){
    percorre(p->proximo, mostra);
    mostra(p->info);
  }
}

/*memória é uma stack, por isso percorre invertido funciona,quando chegar a NULL, a funcao irá retornar os comandos, e chenado assim na função mostra*/

void verifica_ponteiros_lista(LDE *l){
printf("Endereço: %p \t Conteudo: %d \t Prev: %p \t Next: %p\n"
,l, l->info, l->ant, l->suc);
}

/*item c*/
