#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PilhaGenerica.h"

void inicializa_pilha(PilhaGenerica *p, int c, int t){
p->dados = malloc(sizeof(void *) * c) ;
p->capacidade = c;
p-> topo = -1;
p->tam_info = t;
}

int empilha(PilhaGenerica *p, void *info){
if(pilha_cheia(*p)){
	return ERRO_PILHA_CHEIA;
}
p->topo++;
p->dados[p->topo] = malloc(p->tam_info);
memcpy(p->dados[p->topo], info , p->tam_info);
return 1;  //sucesso!
}

int desempilha(PilhaGenerica *p, void *info){
if(pilha_vazia(*p)){
	return ERRO_PILHA_VAZIA;
}
memcpy(info, p->dados[p->topo] , p->tam_info);
free(p->dados[p->topo]);
p->topo--;

return 1;  //sucesso!
}

int pilha_vazia(PilhaGenerica p){
	return p.topo == -1;
}

int pilha_cheia(PilhaGenerica p){
	return p.topo == p.capacidade - 1 ;
}

void mostra_float(void *x){
float *p = x; // isso eh igual a " *(float*)x "
printf("%.1f\n",*p);
}

void mostra_pilha(PilhaGenerica p, void(*mostra)(void *)){
  if(pilha_vazia(p)){
    printf("Pilha vazia!\n");
  }else{
    printf("Dados da pilha: \n");
    percorre_pilha(&p,mostra);
/*mostra(p.dados[i]);*/ /*chama mostra_float na main,tipo abstrato de dado, callback*/
  }
}

void desaloca_pilha(PilhaGenerica *p){
  percorre_pilha(p,free);
  free(p->dados);
}

void percorre_pilha(PilhaGenerica *p, void(*processa)(void *)){
  int i;
  for(i = 0;i <= p->topo; i++){
    processa(p->dados[i]);
  }
}
