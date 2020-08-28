#ifndef EX4_H
#define EX4_H

typedef struct {
	char nome[20];
	char curso[40];
	int fase;
	int media;
}Aluno;

void printa_exames(Aluno **a, int k);

#endif
