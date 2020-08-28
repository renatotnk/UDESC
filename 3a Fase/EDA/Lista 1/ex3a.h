#ifndef EX3_H
#define EX3_H

#define TAM_NOME 20
#define TAM_CURSO 40
typedef struct {
	char *nome[20];
	char *curso[40];
	int fase;
	int media;
}Aluno;

typedef struct {
	Aluno *alunos;
	int elementos;
}Lista;

Lista *inicializa_lista(void);
void inserir_aluno(Lista *m);
void printa_exames(Lista *h);

#endif
