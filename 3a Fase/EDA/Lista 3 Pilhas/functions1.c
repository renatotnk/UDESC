#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex1.h"


void inicializa(PilhaDupla *p,int c, int t){
	p->dados = malloc(sizeof(void *) * c) ;
	p->capacidade = c;
	p-> topo1 = -1;
	p-> topo2 = c;
	p->tam_info = t;
}

int empilha1(PilhaDupla *p,void *info){
	if(pilhas_cheias(*p)){
		return 0;
	}
	p->topo1++;
	p->dados[p->topo1] = malloc(p->tam_info);
	memcpy(p->dados[p->topo1], info , p->tam_info);
	return 1;  //sucesso!
}

int empilha2(PilhaDupla *p,void *info){
	if(pilhas_cheias(*p)){
		return 0;
	}
	p->topo2--;
	p->dados[p->topo2] = malloc(p->tam_info);
	memcpy(p->dados[p->topo2], info , p->tam_info);
	return 1;  //sucesso!
}

int desempilha1(PilhaDupla *p,void *info){
	if(pilha1_vazia(*p)){
	return ERRO_PILHA1_VAZIA;
	}
	memcpy(info, p->dados[p->topo1] , p->tam_info);
	free(p->dados[p->topo1]);
	p->topo1--;
	return 1;  //sucesso!
}

int desempilha2(PilhaDupla *p,void *info){
	if(pilha2_vazia(*p)){
	return ERRO_PILHA2_VAZIA;
	}
	memcpy(info, p->dados[p->topo2] , p->tam_info);
	free(p->dados[p->topo2]);
	p->topo2++;
	return 1;  //sucesso!
}

int pilha1_vazia(PilhaDupla p){
	return p.topo1 == -1;
}
int pilha2_vazia(PilhaDupla p){
	return p.topo2 == p.capacidade;
}

int pilhas_cheias(PilhaDupla p){
	if(p.topo1 == p.topo2 - 1 || p.topo2 == p.topo1 - 1 ){
		return ERRO_PILHAS_CHEIAS;
	}
}

void desaloca_pilha(PilhaGenerica *p){
	int i;
  for(i = 0;i <= p->topo; i++){
  free(p->dados[i]);
}
}
