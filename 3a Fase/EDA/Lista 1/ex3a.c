#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex3.h"
Lista *inicializa_lista(void){
	
	Lista *l = NULL;
	if(!(l = (Lista *) malloc(sizeof(Lista)))){
		printf("[inicializa_lista] Sem Memória\n");	
		exit(EXIT_FAILURE);
	}
	l->alunos = NULL;
	l->elementos = 0;
	
	return l;
}

void inserir_aluno(Lista *m){
	
	int tam_atual = 0;
	Aluno *tmp = NULL;
	
	tmp = (Aluno *) realloc(m->alunos, (tam_atual + 1) * sizeof(Aluno));
	if(tmp == NULL){
		printf("temporariamente sem memoria\n");
		return ;
	}
	m->alunos = tmp;
	m->alunos[m->elementos] = novo_aluno();
	printf("Por favor, informe os dados para o aluno %d\n",m->elementos);
	printf("Entre com o nome do aluno\n");
	scanf("%s",m->alunos[m->elementos]->nome);
	printf("Entre com o curso do aluno\n");
	scanf("%s",m->alunos[m->elementos]->curso);
	printf("Entre com a fase do aluno\n");
	scanf("%d",&(m->alunos[m->elementos].fase);
	printf("Entre com a média do aluno\n");
	scanf("%d",&(m->alunos[m->elementos].media);
	
	m->elementos = m->elementos + 1;


}

Aluno *novo_aluno(void){
	Aluno *al = NULL;
	if(!(al = (Aluno *) malloc(sizeof(Aluno)))) {
		printf("[novo_contato] Sem memória\n");
			exit(EXIT_FAILURE);
	}
	if(!(al->nome = (char *) malloc(sizeof(char) * TAM_NOME))) {
		printf("[novo_aluno] Sem memória\n");
			exit(EXIT_FAILURE);
	}
	if(!(al->curso = (char *) malloc(sizeof(char) * TAM_CURSO))) {
		printf("[novo_aluno] Sem memória\n");
			exit(EXIT_FAILURE);
	}
	
	al->fase = 0;
	al->media = 0;
	
	return al;
}

void printa_exames(Lista *h){
	int i = 0;
	printf("-------Alunos em Exame:-------\n");
	for(i = 0;i < k;i++){	
		if(a[i].media < 7){
			
			printf("Nome do Aluno: %s\t",a[i].nome);
			printf("Media: %d\n",a[i].media);
		}
	} 
}
