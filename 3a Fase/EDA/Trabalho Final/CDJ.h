#ifndef CDJ_H
#define CDJ_H
#define ERRO_LISTA_VAZIA -1
#define ERRO_POSICAO_INVALIDA -2

typedef struct con{
  void *info;
  struct con *ant;
  struct con *suc;
}Membro;

typedef struct{
  int tamInfo;
  Membro *cabeca;
  int qtd;
}CDJ;

void inicializacao(CDJ *l,int t);
Membro *aloca_elemento(void *x, int t);
int insereNoInicio(CDJ *l, void *info);
int insereNoFim(CDJ *l, void *info);
int removeDoInicio(CDJ *l,void *info);
int removeDofim(CDJ *l, void *info);
int removeDaPos(CDJ *l,void *info,int pos);
Membro *pesquisa_membro(CDJ *l, void *info,int (*compara)(void *a,void *b));
int remove_conjunto(CDJ *l,void *info,int (*compara)(void *a, void *b));
int desaloca_estrutura(CDJ *l);
int mostra_conjuntos(CDJ *l);
int une_conjuntos(CDJ *l, void *a, void *b,int (*compara)(void *a, void *b));

#endif
