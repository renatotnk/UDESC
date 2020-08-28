#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDupla.h"

void inicializa_lista_dupla(LDE *l,int t){
  l->tamInfo = t;
  l->cabeca = NULL;
}

ElementoDuplo lista_vazia(l){
  return p->cabeca = NULL;
}

ElementoDuplo *aloca_elemento(void *x, int t){
  ElementoDuplo *novo = malloc(sizeof(ElementoDuplo));
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

int insereNoInicio(LDE *l, void *info){
  ElementoDuplo *novo = aloca_elemento(info, p->tamInfo);
  if(novo == NULL){
    return 0;    //Erro na alocaçao
  }

  novo->ant = NULL;
  novo->suc = l->cabeca;
  l->cabeca = novo;
  if(novo->suc != NULL){
    novo->suc->ant = novo;
  }
  return 1;     //sucesso!
}

int insereNoFim(LDE *l, void *info){
  if(lista_vazia(*l)){
    return insereNoInicio(l,info);
  }
  ElementoDuplo *p = l->cabeca;
  ElementoDuplo *novo = aloca_elemento(info, l->tamInfo);
  if(novo == NULL){
    return 0;  //Erro na alocacao
  }
  while(p->suc != NULL){
    p = p->suc;
  }
  novo->suc = NULL;
  novo->ant = p;
  p->suc = novo;
  return 1;    //sucesso!
}

int removeDoInicio(LDE *l,void *info){
  if(lista_vazia(*l))
    return ERRO_LISTA_VAZIA;
  ElementoDuplo *p = l->cabeca;
  l->cabeca = p->suc;
  if(l->cabeca != NULL){
    l->cabeca->ant = NULL;
  }
  memcpy(info,p->info,l->tamInfo);
  free(p->info);
  free(p);
  return 1;   //sucesso
}

int removeDofim(LDE *l, void *info){
  if(lista_vazia(*l))
    return ERRO_LISTA_VAZIA;
  if(l->cabeca->suc == NULL)            //Só um elemento
    return removeDoInicio(l,info);
  ElementoDuplo *p = l->cabeca;
  while(p->suc->suc != NULL){      //parar no penultimo
    p = p->suc;
  }
  memcpy(info, p->suc->info,l->tamInfo);
  free(p->suc->info);
  free(p->suc);
  p->suc = NULL;
  return 1;           //sucesso!
}

void mostraLista(LDE l, void (*mostra)(void *)){
  if(lista_vazia(l)){
    printf("Lista Vazia!\n");
  }else{
    printf("Dados da lista\n");
    ElementoDuplo *p = l.cabeca;
    while(p != NULL){
      mostra(p->info);
      p = p->suc;
    }
  }
}

int insereNaPos(LDE *l, void *info,int pos){
  if(pos < 0);{
    return ERRO_POSICAO_INVALIDA;
  }if(pos == 0){
    return insereNoInicio(l,info);
  }if(lista_vazia(*l)){
    return ERRO_LISTA_VAZIA;     //posicao 0 e lista vazia
  }
  ElementoDuplo *p = l->cabeca;
  int cont = 0;
  while((cont < pos - 1) && (p->suc != NULL)){
    p = p->suc;
    cont++;
  }
  if(cont != pos - 1){
    return ERRO_POSICAO_INVALIDA;
  }
  ElementoDuplo *novo = aloca_elemento(info,l->tamInfo);
  if(novo == NULL){
    return 0;    //erro na alocacao
  }
  novo->suc = p->suc;
  p->suc = novo;
  novo->ant = p;
  if(novo->suc != NULL){
    novo->suc->ant = novo;
  }
  return 1;     //sucesso
}

int removeDaPos(LDE *l,void *info,int pos){
  if(lista_vazia(*l)){
    return ERRO_LISTA_VAZIA;
  }if(pos < 0){
    return ERRO_POSICAO_INVALIDA;
  }if(pos == 0){
    return removeDoInicio(l,info);
  }
  ElementoDuplo *p = l->cabeca;
  int cont = 0;
  while((cont < pos - 1) && (p->suc != NULL)){
    p = p->suc;
    cont++;
  }
  if(p->suc == NULL){
    return ERRO_POSICAO_INVALIDA;
  }
  ElementoDuplo *x = p->suc;
  p->suc = x->suc;
  memcpy(info,x->info,l->tamInfo);
  free(x->info);
  free(x);
  if(p->suc != NULL){
    p->suc->ant = p;
  }
  return 1;   //sucesso
}

int leNaPosicao(LDE *l,void *info, int pos){
  if(lista_vazia(*l)){
    return ERRO_LISTA_VAZIA;
  }if(pos < 0){
    return ERRO_POSICAO_INVALIDA;
  }
  ElementoDuplo *p = l->cabeca;
  int cont = 0;
  while((cont < pos) && (p->suc != NULL)){
    p = p->suc;
    cont++;
  }
  if(cont != pos)
    return ERRO_POSICAO_INVALIDA;
  memcpy(info,p->info,l->tamInfo);
  return 1;  //sucesso
}

int modificaNaPos(LDE *l, void *info, int pos){
  if(lista_vazia(*l)){
    return ERRO_LISTA_VAZIA;
  }if(pos < 0){
    return ERRO_POSICAO_INVALIDA;
  }
  ElementoDuplo *p = l->cabeca;
  int cont = 0;
  while((cont < pos) && (p->suc != NULL)){
    p = p->suc;
    cont++;
  }
  if(pos != cont)
    return ERRO_POSICAO_INVALIDA;
  memcpy(p->info,info,l->tamInfo);
  return 1;  //sucesso
}

int insereEmOrdem(LDE *l,void *info,int (*compara)(void *a,void *b)){
  ElementoDuplo *p = l->cabeca;
  int cont = 0;
  while((p->suc != NULL) && ((compara(info,p->info)) > 0)){
    p = p->suc;
    cont++;
  }
  return insereNaPos(l,info,cont);

}

ElementoDuplo lista_vazia(Lista l){
  return l->cabeca = NULL;
}

void verifica_ponteiros_lista(LDE *l){
printf("Endereço: %p \t Conteudo: %d \t Prev: %p \t Next: %p\n",l, l->info, l->ant, l->suc);
}

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

