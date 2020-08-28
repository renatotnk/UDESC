#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PilhaGenerica.h"
#include "ex3.h"

void inicializa_fila(FilaNova *p,int c){
  inicializa_pilha(&p->pI,c);
  inicializa_pilha(&p->pO,c);
}

int inserir(FilaNova *p,void *info){
  if(pilha_cheia(p->pI))
    return ERRO_PILHA_CHEIA;
}
