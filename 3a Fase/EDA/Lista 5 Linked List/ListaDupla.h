#ifndef LISTADUPLA_H
#define LISTADUPLA_H
#define ERRO_LISTA_VAZIA -1
#define ERRO_POSICAO_INVALIDA -2
typedef struct ele{
  void *info;
  struct ele *ant;
  struct ele *suc;
}ElementoDuplo;

typedef struct{
  int tamInfo;
  ElementoDuplo *cabeca;
}LDE;

void inicializa_lista_dupla(LDE *l,int t);
ElementoDuplo lista_vazia(l);
ElementoDuplo *aloca_elemento(void *x, int t);
int insereNoInicio(LDE *l, void *info);
int insereNaPos(LDE *l, void *info,int pos);
int removeDaPos(LDE *l,void *info,int pos);
int insereNoFim(LDE *l, void *info);
int removeDoInicio(LDE *l,void *info);
int removeDofim(LDE *l, void *info);
void mostraLista(LDE l, void (*mostra)(void *));
int leNaPosicao(LDE *l,void *info, int pos);
int modificaNaPos(LDE *l, void *info, int pos);
int insereEmOrdem(LDE *l,void *info,int (*compara)(void *a,void *b));
ElementoDuplo lista_vazia(Lista l);
void verifica_ponteiros_lista(LDE *l);
void inverte_lista(LDE l);

#endif
