#include <stdio.h>
#include "eda.h"
#include "cmd.h"
#include "expr.tab.h"
extern FILE *yyin;
extern struct arvore* tabelaSimbolosGlobais;
extern struct arvore* tabelaSimbolosFuncoes;
int main(int c, char *argv[])
{
	FILE * file;
	file = fopen (argv[1], "r");
	printf("Arquivo: %s\n\n", argv[1]);
	if (file == NULL){
		printf("Arquivo não encontrado\n");
		return -1;
	}
	writeJasminInit(argv[1]);
	writeJasminBody();
	tabelaSimbolosGlobais = criarArvore();
	tabelaSimbolosFuncoes = criarArvore();
	yyin = file;
	yyparse();
	printf("\nArvore Funcional:\n");
	printArvore(tabelaSimbolosFuncoes);
	printf("\nArvore Principal:\n");
	printArvore(tabelaSimbolosGlobais);
	showFunctionTable();
	writeJasminExit();
	callJasmin();
	return 0;
}
