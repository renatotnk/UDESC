#ifndef EX1_H
#define EX1_H
#define ERRO_PILHAS_CHEIAS -1
#define ERRO_PILHA1_VAZIA -2
#define ERRO_PILHA2_VAZIA -3


typedef struct {
	void **dados;
	int topo1, topo2;
	int capacidade;
	int tam_info;
}PilhaDupla;

void inicializa(PilhaDupla *p,int c, int t);
int empilha1(PilhaDupla *p,void *info);
int empilha2(PilhaDupla *p,void *info);
int desempilha1(PilhaDupla *p, void *info);
int desempilha2(PilhaDupla *p, void *info);
int pilha1_vazia(PilhaDupla p);
int pilha2_vazia(PilhaDupla p);
int pilhas_cheias(PilhaDupla p);

#endif
