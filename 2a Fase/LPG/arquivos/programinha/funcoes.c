#include <stdio.h>
#include "banco.h"
int main(int argc,char *argv[]){
	FILE *arquivo = NULL;
	int op;
	if(argc < 2){
		printf("uso: %s arquivo\n",argv[0]);
		return 1;
	}
	
	arquivo = fopen(argv[1],"r");
	if(!arquivo){
		printf("arquivo nao encontrado\n");
		return 1;
	}
	int (*f[])(double) = {devedor,credor,zerado};
	while((op = menu()) != -1){
		rewind(arquivo);
		relatorio(arquivo,f[op]);
	}
	fclose(arquivo);
	return 0;
	
}
