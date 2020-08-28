#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_ID 11
#define T_MAX 200
#define T_INT 1
#define T_STRING 2
#define T_FLOAT 3
#define MULT 4
#define DIV 5
#define SUB 6
#define ADD 7
#define ID 8
#define CONSTINT 9
#define CONSTFLOAT 10
#define IGUAL 13
#define NEG 12
#define I2F 14
#define LIST 15
#define MAIOR 16
#define MENOR 17
#define MAIORIG 18
#define MENORIG 19
#define COMPIG 20
#define COMPDIF 21
#define NOT 22
#define OU 23
#define E 24
#define IF 25
#define IF_ELSE 26
#define WHILE 27
#define PRINT 28


typedef struct TabSim{
    char id[MAX_ID];
    int tipo;
    int posicao;
    struct TabSim *esq;
    struct TabSim *dir;
}TabSim;

typedef struct{
	struct TabSim *raiz;
}ABB;

typedef struct Atributo{
	int tipo;
	struct LDSE *listaId;
	struct AST *ptr;
	char id[MAX_ID];
	int valorInt;
	float valorFloat;
	char buffer[T_MAX];
}Atributo;

typedef struct LDSE{
    struct No *lista;
}LDSE;

typedef struct No{
	struct No *prox;
	char idi[MAX_ID];
}No;

typedef struct AST{
	int cod;
	struct AST *ptr1;
	struct AST *ptr2;
	struct AST *ptr3;
	struct TabSim *tab;
	int constInt;
	float constFloat;
	char buffer[T_MAX];
}AST;

extern ABB *arvore;
extern FILE *bytearq;

//funções para manipulação de árvore binária
void criaABB(ABB **arvore);
void reiniciaABB(ABB *arvore);
void destroiABB(ABB **arvore);
void apagaNoABB(TabSim *p);
void inserirTabela(int tipo, LDSE *l);
void preOrdem(ABB *pa);
void percorreEmPreOrdem(TabSim *p);
int comparaBusca(char *pInfo1, char *pInfo2);
int consultaTipo(char *chaveDeBusca);
void contaVariaveis2(TabSim *p);
int scontaVariaveis(ABB *p);

//funções para a manipulação de lista simplesmente encadeada
void criaLista(LDSE **p);
void reinicia(LDSE *p);
void destroi(LDSE **p);
void insereNaLista(LDSE *p, char *id);

//funções para a manipuação da árvore binária aritmética
void destroiAB_Aritmetica(AST *arvore);
void apagaNoAB_Aritmetica(AST *p);
AST *criaNo(int operacao, AST *at1, AST *at2);
AST *criaFolha(Atributo *at1,int tipo);
AST *criaFolhaS(char *at1);
AST *criaNoIF(int operacao, AST *at1, AST *at2,AST *at3);
void percorreEmPosOrdem(AST *p);
AST *f2i(AST *at);
AST *i2f(AST *at);
int geraLabel();
void imprimeLogicaRelacional(AST *p, int lv, int lf);

//funções para manipulacao de arquivo
void printCabecalho();
void printFim();