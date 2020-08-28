 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex4.h"
int main(void){
	Aluno **x = NULL;
	int alunos,i;
	printf("Informe o Número de alunos\n");
	scanf("%d",&alunos);
	x = (Aluno **)malloc(sizeof(Aluno *) * alunos);
	for (i = 0;i < alunos; i++){
	x[i] = malloc(sizeof(Aluno));
	printf("Entre com o nome do aluno\n");
	scanf("%s",x[i]->nome);
	printf("Entre com o curso do aluno\n");
	scanf("%s",x[i]->curso);
	printf("Entre com a fase do aluno\n");
	scanf("%d",&x[i]->fase);
	printf("Entre com a média do aluno\n");
	scanf("%d",&x[i]->media);
	}
	printa_exames(x, alunos);

	for (i = 0;i < alunos; i++){
	free(x[i]);
}
free(x);
	
return 0;
}

void printa_exames(Aluno **a, int k){
	int i = 0;
	printf("-------Alunos em Exame:-------\n");
	for(i = 0;i < k;i++){	
		if(a[i]->media < 7){
			
			printf("Nome do Aluno: %s\t",a[i]->nome);
			printf("Media: %d\n",a[i]->media);
		}
	} 
}
