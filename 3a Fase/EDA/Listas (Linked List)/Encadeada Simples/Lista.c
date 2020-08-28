#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

void inicializa_lista(Lista *p,int t){
  p->tamInfo = t;
  p->cabeca = NULL;
}

Elemento *aloca_elemento(void *x, int t){
  Elemento *novo = malloc(sizeof(Elemento));
  if(novo == NULL){
    return NULL;
  }
  novo->info = malloc(t);
    if(novo->info == NULL){
      free(novo);
     return NULL;
  }
  memcpy(novo->info,x,t);
  return novo;
}

int insereNoInicio(Lista *p, void *info){

  Elemento *novo = aloca_elemento(info, p->tamInfo);
  if(novo == NULL){
    return 0;  //Erro na alocacao
  }

  novo->proximo = p->cabeca;
  p->cabeca = novo;
  return 1;
}

int insereNoFim(Lista *l, void *info){

  if(lista_vazia(*l))
    return insereNoInicio(l,info);

  Elemento *p = l->cabeca;
  Elemento *novo = aloca_elemento(info, l->tamInfo);
  if(novo == NULL){
    return 0;  //Erro na alocacao
  }
  while(p->proximo != NULL){
     p = p->proximo;
  }
  novo->proximo = NULL;
  p->proximo = novo;

  return 1;
}

void mostraLista(Lista l, void (*mostra)(void *)){
  if(lista_vazia(l)){
    printf("Lista Vazia!\n");
  }else{
    printf("Dados da lista\n");
    Elemento *p = l.cabeca;
    while(p != NULL){
      mostra(p->info);
      p = p->proximo;
    }
  }
}

int removeDoInicio(Lista *l,void *info){
  if(lista_vazia(*l))
    return ERRO_LISTA_VAZIA;
  Elemento *p = l->cabeca;
  memcpy(info,p->info,l->tamInfo);
  l->cabeca = p->proximo;
  free(p->info);
  free(p);
  return 1;   //sucesso
}


int removeDofim(Lista *l, void *info){
  if(lista_vazia(*l))
    return ERRO_LISTA_VAZIA;
  if(l->cabeca->proximo == NULL)            //Só um elemento
    return removeDoInicio(l,info);
  Elemento *p = l->cabeca;
  while(p->proximo->proximo != NULL){      //parar no penultimo
    p = p->proximo;
  }
  memcpy(info, p->proximo->info,l->tamInfo);
  free(p->proximo->info);
  free(p->proximo);
  p->proximo = NULL;
  return 1;           //sucesso!
}

int insereNaPos(Lista *l,void *info,int pos){
  if(pos < 0){
    return ERRO_POSICAO_INVALIDA;
  }if(pos == 0){
    return insereNoInicio(l,info);
  }if(lista_vazia(*l)){
    return ERRO_POSICAO_INVALIDA;     //posicao > 0 e lista vazia
  }
  Elemento *p = l->cabeca;
  int cont = 0;
  while((cont < pos - 1) && (p->proximo != NULL)){
    p = p->proximo;
    cont++;
  }
  if(cont != pos - 1){
    return ERRO_POSICAO_INVALIDA;
  }
  Elemento *novo = aloca_elemento(info, l->tamInfo);
  if(novo == NULL){
    return 0;  //Erro na alocacao
  }
  novo->proximo = p->proximo;
  p->proximo = novo;
  return 1;
}

int removeDaPos(Lista *l,void *info,int pos){
  if(lista_vazia(*l)){
    return ERRO_LISTA_VAZIA;
  }if(pos < 0){
    return ERRO_POSICAO_INVALIDA;
  }if(pos == 0){
    return removeDoInicio(l,info);
  }
  Elemento *p = l->cabeca;
  int cont = 0;
  while((cont < pos - 1) && (p->proximo != NULL)){
    p = p->proximo;
    cont++;
  }
  if(p->proximo == NULL){
    return ERRO_POSICAO_INVALIDA;
  }
  Elemento *x = p->proximo;
  p->proximo = x->proximo;
  memcpy(info,x->info,l->tamInfo);
  free(x->info);
  free(x);
  return 1;   //sucesso
}

int leNaPosicao(Lista *l,void *info, int pos){
  if(lista_vazia(*l)){
    return ERRO_LISTA_VAZIA;
  }if(pos < 0){
    return ERRO_POSICAO_INVALIDA;
  }
  Elemento *p = l->cabeca;
  int cont = 0;
  while((cont < pos) && (p->proximo != NULL)){
    p = p->proximo;
    cont++;
  }
  if(cont != pos)
    return ERRO_POSICAO_INVALIDA;
  memcpy(info,p->info,l->tamInfo);
  return 1;  //sucesso
}

int modificaNaPos(Lista *l, void *info, int pos){
  if(lista_vazia(*l)){
    return ERRO_LISTA_VAZIA;
  }if(pos < 0){
    return ERRO_POSICAO_INVALIDA;
  }
  Elemento *p = l->cabeca;
  int cont = 0;
  while((cont < pos) && (p->proximo != NULL)){
    p = p->proximo;
    cont++;
  }
  if(pos != cont)
    return ERRO_POSICAO_INVALIDA;
  memcpy(p->info,info,l->tamInfo);
  return 1;  //sucesso
}

int insereEmOrdem(Lista *l,void *info,int (*compara)(void *a,void *b)){
  Elemento *p = l->cabeca;
  int cont = 0;
  while((p->proximo != NULL) && ((compara(info,p->info)) > 0)){
    p = p->proximo;
    cont++;
  }
  return insereNaPos(l,info,cont);

}

Elemento lista_vazia(Lista l){
  return l->cabeca = NULL;
}
