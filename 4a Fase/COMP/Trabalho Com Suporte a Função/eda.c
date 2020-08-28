#include "eda.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
List* criaLista (char *id){
	List *ret = (struct List*)malloc(sizeof(struct List));
	if (ret != NULL){
		memcpy(ret->id, id, 11);
		ret->proximo = NULL;
	}
	return ret;
}
void insereLista (struct List *head, char *id){
	if(head->proximo == NULL){
		head->proximo = (struct List*)malloc(sizeof(struct List));
		if (head->proximo != NULL){
			memcpy(head->proximo->id, id, 11);
			head->proximo->proximo = NULL;
		}
	} else {
		insereLista(head->proximo, id);
	}
}
void printaLista (struct List *l){
	if(l == NULL) {
		printf("\n");
		return;
	};
	printf("%s ",(char*)l->id);
	printaLista(l->proximo);
}
struct arvore* criarArvore(){
	struct arvore* ret = (struct arvore*)malloc(sizeof(struct arvore));
	ret->root = NULL;
	ret->qnt = 0;
	return ret;
}
void insereArvore(struct arvore* arv, char* valor){
	if(arv->root == NULL){
		arv->root = criaNo(valor,arv->qnt);
		arv->qnt++;
		return;
	} else {
		insereArvoreInternal(arv->root, valor,arv->qnt);
		arv->qnt++;
		return;
	}
}
void insereArvoreInternal(struct no* node, char* valor, int posicao){
	int ret = strcmp(node->valor, valor);
	if(ret == 0){
		printf("Simbolo %s já inserido\n", valor);
		exit(-1);
	}
	if(ret >0 && node->maior == NULL){
		node->maior = criaNo(valor,posicao);
		return;
	}
	if(ret <0 && node->menor == NULL){
		node->menor = criaNo(valor,posicao);
		return;
	}
	if(ret < 0){
		insereArvoreInternal(node->menor, valor, posicao);
	} else {
		insereArvoreInternal(node->maior, valor, posicao);
	}
}
struct no* criaNo(char* valor, int num){
	struct no* ret = (struct no*)malloc(sizeof(struct no));
	ret->valor = malloc(sizeof(char)*100);
	strcpy(ret->valor, valor);
	ret->valor[99] = '\0';
	ret->tipo = NDEFINIDO;
	ret->num = num;
	ret->maior = NULL;
	ret->menor = NULL;
	return ret;
}
void printArvore (struct arvore* arv){
	printNodes(arv->root, 0);
}
void printNodes (struct no* node, int nivel){
	int n = 0;
	for(n = 0; n < nivel; n ++){
		printf("	");
	}
	if(node == NULL)
	{
		printf("|-: NULL\n");
		return;
	}
	printf("|-: %s / %c / %d\n", node->valor, node->tipo, node->num);
	printNodes(node->maior, nivel +1);
	printNodes(node->menor, nivel +1);
}
void insereListaNaArvore(List* lista, struct arvore* arv, TIPO tipo){
	if (lista == NULL){
		atualizaTipoDaArovre(arv->root, tipo);
		return;
	}
	if (arv == NULL) return;
	insereArvore(arv, (char*)lista->id);
	insereListaNaArvore((List*)lista->proximo, arv, tipo);
}
void atualizaTipoDaArovre (struct no * root, TIPO tipo)
{
	if(root == NULL) return;
	if(root->tipo == NDEFINIDO) root->tipo = tipo;
	atualizaTipoDaArovre(root->maior, tipo);
	atualizaTipoDaArovre(root->menor, tipo);
}
int buscaPosicao (struct arvore* arv ,char* valor)
{
	return buscaPosicaoInternal(arv->root, valor);
}
int buscaPosicaoInternal (struct no* node, char* valor)
{
	if(node == NULL)
	{
		printf("Variável %s não foi declarada.\n", valor);
	}
	int decisao = strcmp(node->valor, valor);
	if(decisao == 0) return node->num;
	if(decisao > 0) return buscaPosicaoInternal(node->maior, valor);
	else return buscaPosicaoInternal(node->menor, valor);
}
void printaIntList(struct IntList* l)
{
	if(l == NULL){
		printf("\n");
		return;
	}
	printf("->%d", l->valor);
	printaIntList(l->proximo);
}
struct IntList* criaIntList(int valor)
{
	struct IntList* ret = malloc(sizeof(struct IntList));
	ret->proximo = NULL;
	ret->valor = valor;
	return ret;
}
void insereIntList(struct IntList* head, int valor)
{
	if(head->proximo == NULL){
		head->proximo = criaIntList(valor);
		return;
	}
	insereIntList(head->proximo, valor);
}
struct IntList* juntarIntList(struct IntList* head, struct IntList* bunda)
{
	juntarIntListInternal(head, bunda);
	return head;
}
void juntarIntListInternal(struct IntList* cabeca, struct IntList* bunda)
{
	if(cabeca->proximo == NULL){
		cabeca->proximo = bunda;
		return;
	}
	juntarIntList(cabeca->proximo, bunda);
}
char* buscaPonteiroDoNome(struct arvore* arv, char* valor)
{
	return buscaPonteiroDoNomeInternal(arv->root, valor);
}
char* buscaPonteiroDoNomeInternal(struct no* node, char* valor)
{
	if(node == NULL)
	{
		printf("O termo %s não foi encontrado\n", valor);
		exit(-1);
	}
	int decisao = strcmp(node->valor, valor);
	if(decisao == 0) return node->valor;
	if(decisao > 0) return buscaPonteiroDoNomeInternal(node->maior, valor);
	if(decisao < 0) return buscaPonteiroDoNomeInternal(node->menor, valor);
}
