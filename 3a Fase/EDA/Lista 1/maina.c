#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex3.h"


int main(void){
	Lista *x = NULL;
	int alunos = 0;
	int i,opcao;
	x = inicializa_lista();
	printf("Informe 1 para cadastrar um aluno.\n2 para listar alunos em exame.\n -1 para sair\n");
	scanf("%d",&opcao);
	
	while(opcao != -1){
		if(opcao == 1){
			inserir_aluno(x);
		} else if(operacao == 2){
			printa_exames(x);
		} else {
			printf("Opção inválida\n");
		}
		printf("-------Sistema Acadêmico-------");
		printf("Informe 1 para cadastrar um contato.\n2 para listar.\n -1 para sair\n");
		scanf("%d",&opcao);
	}
	
	/* arrumar depois */
	
	/*
	if(alunos = 0){
	printf("Informe o Número de alunos\n");
	scanf("%d",&alunos);
	x = (Aluno *)malloc(sizeof(Aluno) * alunos);
	for (i = 0;i < alunos; i++){
		printf("Entre com o nome do aluno\n");
		scanf("%s",x[i].nome);
		printf("Entre com o curso do aluno\n");
		scanf("%s",x[i].curso);
		printf("Entre com a fase do aluno\n");
		scanf("%d",&x[i].fase);
		printf("Entre com a média do aluno\n");
		scanf("%d",&x[i].media);
		}
	}

	printa_exames(x, alunos);
	*/
	
	
return 0;
}
