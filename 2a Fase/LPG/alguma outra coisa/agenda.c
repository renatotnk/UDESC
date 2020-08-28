#include <stdio.h>
#include <stdlib.h>
#include "exemploalok.h"

#define TAM_COMPLEMENTO 80
#define TAM_ENDERECO 80

	char *endereco;
	char *complemento;
	char uf[2];

Agenda *inicializa_agenda (void){

	Agenda *ret = NULL;
	if(!(ret = (Agenda *) malloc(sizeof(Agenda)))){
			printf("[inicializa_agenda] Sem memória\n");
			exit(EXIT_FAILURE);
	}
	ret->contatos = NULL;
	ret->elementos = 0;
	return ret;
}

Endereco *novo_endereco(void){
	Endereco *ret = NULL;
	if(!(ret = (Endereco *) malloc(sizeof(Endereco)))) {
		printf("[novo_endereco] Sem memória\n");
			exit(EXIT_FAILURE);
	}

	if(!(ret->endereco = (char *)malloc(sizeof(char) * TAM_ENDERECO)))
	{
		printf("[novo_endereco] Sem memória\n");
			exit(EXIT_FAILURE);
	}
	if(!(ret->endereco = (char *)malloc(sizeof(char) * TAM_COMPLEMENTO)))
	{
		printf("[novo_endereco] Sem memória\n");
			exit(EXIT_FAILURE);
	}
	return ret;
	}

Contato *novo_contato(void){
	Contato *ret = NULL;
	if(!(ret = (Contato *) malloc(sizeof(Contato)))) {
		printf("[novo_contato] Sem memória\n");
			exit(EXIT_FAILURE);
	}
	ret->nasc.dia = 0;
	ret->nasc.mes = 0;
	ret->nasc.ano = 0;
	if(!(ret->nome = (char *) malloc(sizeof(char) * TAM_NOME))) {
		printf("[novo_contato] Sem memória\n");
			exit(EXIT_FAILURE);
	}
	if(!(ret->telefone = (char *) malloc(sizeof(char) * TAM_TELEFONE))) {
		printf("[novo_contato] Sem memória\n");
			exit(EXIT_FAILURE);
	}

	ret->end = novo_endereco(); 
	return ret;
}

/*inserir variavel trabalho final*/
void inserir_contato(Agenda *a){
	
	int tam_atual = a->elementos;
	Contato **tmp = NULL;

	tmp = (Contato **) realloc(a->contatos, (tam_atual +1) * sizeof(Contato *));
	if(tmp == NULL){
		printf("temporariamente sem memoria\n");
		return;
	}
	a->contatos = tmp;
	a->contatos[a->elementos] = novo_contato();
	printf("Prezado usuário, informe os dados para o índice %d \n",a->elementos);
	printf("Informe dia,mês e ano de nascimento\n");
	scanf("%d %d %d ",&(a->contatos[a->elementos]->nasc.dia),&(a->contatos[a->elementos]->nasc.mes),&(a->contatos[a->elementos]->nasc.ano));
	printf("Informe seu nome e telefone\n");
	scanf("%s %s",a->contatos[a->elementos]->nome, a->contatos[a->elementos]->telefone);
	printf("Informe seu endereço,complemento e UF\n");
	scanf("%s %s %s",a->contatos[a->elementos]->end->endereco, a->contatos[a->elementos]->end->complemento,a->contatos[a->elementos]->end->uf);
	
	a->elementos = a->elementos + 1;

}


void libera_endereco(Endereco *end){

	free(end->endereco);
	free(end->complemento);
	end->endereco = NULL;
	end->complemento = NULL;
	free(end);
}

void libera_contato(Contato *c){

	free(c->nome);
	free(c->telefone);
	libera_endereco(c->end);
	c->nome = NULL;
	c->telefone = NULL;
	c->end = NULL;
	free(c);

}

void libera_agenda(Agenda *a){
	int i;
	for(i = 0; i < a->elementos; i++){
		libera_contato(a->contatos[i]);
	}
	free(a->contatos);
	free(a);
}

void lista_pessoas(Agenda *a){
	int i;
	if(a->elementos == 0){
		printf("Agenda Vazia\n");
		return;
	}
	printf("Pessoas cadastradas na agenda\n");
	for(i = 0; i < a->elementos; i++){
		printf("Contato %d\n",i);
		printf("\tNome: %s\n",a->contatos[i]->nome);
		printf("\tData de Nascimento: %d/%d/%d\n",a->contatos[i]->nasc.dia,a->contatos[i]->nasc.mes,a->contatos[i]->nasc.ano);
		printf("\t%s %s %s",a->contatos[i]->end->endereco,a->contatos[i]->end->complemento,a->contatos[i]->end->uf);
		printf("--------------------\n");
	}
	
}