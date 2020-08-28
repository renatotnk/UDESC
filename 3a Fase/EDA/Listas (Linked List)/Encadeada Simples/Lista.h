#ifndef LISTA_H
#define LISTA_H
#define ERRO_LISTA_VAZIA -1
#define ERRO_POSICAO_INVALIDA -2
typedef struct ele{
  void *info;
  struct ele *proximo;
}Elemento;

typedef struct Lista{
    int tamInfo;
    Elemento *cabeca;
}Lista;

void inicializa_lista(Lista *p,int t);
int insereNoInicio(Lista *p, void *info);
int insereNoFim(Lista *p, void *info);
void mostraLista(Lista l,void (*mostra)(void *));
int removeDoInicio(Lista *l,void *info);
int removeDofim(Lista *l, void *info);
int insereNaPos(Lista *l1,void *info,int pos);
Elemento *aloca_elemento(void *x, int t);
int removeDaPos(Lista *l,void *info, int pos);
int leNaPosicao(Lista *l,void *info, int pos);
int modificaNaPos(Lista *l,void *info, int pos);
int insereEmOrdem(Lista *l,void *info,int (*compara)(void *a,void *b));


#endif
