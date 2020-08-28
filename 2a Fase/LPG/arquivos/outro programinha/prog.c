#include <stdio.h>
#include "banco2.h"
int main(int argc, char **argv)
{
	FILE *arquivo = NULL;
	int op = 0;
	void (*f[])(FILE *) = {cadastrar_cliente, remover_cliente, atualizar_cliente, relatorio};
	
	if (argc < 2){
		printf("uso: %s arquivo_binario.dat",argv[0]);
		return 1;
	}
	
	arquivo = fopen(argv[1], "rb+");
	if(!arquivo){
		printf("erro ao acessar o arquivo %s\n",argv[1]);
		return 1;
	}


	while((op = menu()) != 1){
		f[op](arquivo);
	}
	fclose(arquivo);

	return 0;
}