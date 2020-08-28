#include <stdio.h>
#include <stdlib.h>
#include "aux.h"

extern FILE *yyin;


ABB *arvore;
FILE *bytearq;

int main(int argc, char *argv[])
{
	FILE *arquivo = NULL;	
	arquivo = fopen(argv[1], "r");
	if(arquivo == NULL){
		printf("ERRO AO ABRIR ARQUIVO");
	}

	bytearq = fopen("bytecodes.j", "w");
	if(bytearq == NULL){
		printf("ERRO AO ABRIR ARQUIVO");
	}


	fprintf(bytearq, ".class public Compiladores\n"".super java/lang/Object\n\n");

	criaABB(&arvore);
	yyin = arquivo;
	yyparse();
	fclose(arquivo);

	return 0;
}
