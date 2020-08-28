#include <stdio.h>
#include <stdlib.h>
#include "exemploalok.h"

int main(void){
	Agenda *agenda = NULL;
	int operacao = 0;
	agenda = inicializa_agenda();
	printf("Informe 1 para cadastrar um contato.\n2 para listar.\n -1 para sair\n");
	scanf("%d",&operacao);

	while(operacao != -1){
		if(operacao == 1){
			inserir_contato(agenda);
		} else if(operacao == 2){
			lista_pessoas(agenda);
		} else {
			printf("Opção inválida\n");
		}
		printf("Informe 1 para cadastrar um contato.\n2 para listar.\n -1 para sair\n");
		scanf("%d",&operacao);
	}
	libera_agenda(agenda);
	return 0;
}