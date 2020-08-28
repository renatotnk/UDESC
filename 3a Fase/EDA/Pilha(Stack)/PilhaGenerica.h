#ifndef PILHAGENERICA_H
#define PILHAGENERICA_H
#define ERRO_PILHA_CHEIA -1
#define ERRO_PILHA_VAZIA -2


typedef struct {
  void **dados;
  int capacidade;
  int topo;
  int tam_info;
}PilhaGenerica;

void inicializa_pilha(PilhaGenerica *p, int c , int t);
int empilha(PilhaGenerica *p1,void *info);
int desempilha(PilhaGenerica *p1,void *info); 

int pilha_vazia(PilhaGenerica p);
int pilha_cheia(PilhaGenerica p);
void mostra_float(void *x);
void mostra_pilha(PilhaGenerica p, void(*mostra)(void *));
void desaloca_pilha(PilhaGenerica *p);
void percorre_pilha(PilhaGenerica *p, void(*processa)(void *));

#endif
