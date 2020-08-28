#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaGenerica.h"

void inicializa_fila(FilaGenerica *p, int c,int t){
  p->dados = malloc(sizeof(void *)*c);
  p->inicio = 0;
  p->fim = 0;
  p->capacidade = c;
  p->quantidade = 0;
  p->tam_info = t;
}

int inserir(FilaGenerica *p,void *info){
  if(fila_cheia(*p)){
    return ERRO_FILA_CHEIA;
  }
  p->quantidade++;
  p->dados[p->fim] = malloc(sizeof(p->tam_info));
  memcpy(p->dados[p->fim],info,p->tam_info);
  if(p->fim == p->capacidade-1){
    p->fim = 0;
  }else{
    p->fim++;
  }
return 1;  //sucesso!
}

int remover(FilaGenerica *p,void *info){
  if(fila_vazia(*p)){
    return ERRO_FILA_VAZIA;
  }
  p->quantidade--;
  memcpy(info,p->dados[p->inicio],p->tam_info);
  free(p->dados[p->inicio]);
  if (p->inicio == p->capacidade - 1){
    p->inicio = 0;
  }else{
    p->inicio++;
  }
return 1;  //sucesso!
}

int fila_vazia(FilaGenerica f){
  return f.quantidade == 0;
}

int fila_cheia(FilaGenerica f){
  return f.quantidade == f.capacidade;
}

void mostra_fila(FilaGenerica f,void (*mostra)(void *)){
  if(fila_vazia(f)){
    printf("Fila vazia!\n");
  }else{
    printf("Dados da fila:\n");
    processa_fila(&f,mostra);
  }
}

void desaloca_fila(FilaGenerica *f){
  processa_fila(f,free);
  free(f->dados);
}

void processa_fila(FilaGenerica *f,void(*processa)(void *)){
      int i;
      if(f->inicio < f->fim){
        for(i = f->inicio; i < f->fim; i++){
            processa(f->dados[i]);
          }
      }else{
        for(i = f->inicio; i < f->capacidade;i++){
          processa(f->dados[i]);
        }
        for(i = 0; i < f->fim; i++){
          processa(f->dados[i]);
        }
      }
}
