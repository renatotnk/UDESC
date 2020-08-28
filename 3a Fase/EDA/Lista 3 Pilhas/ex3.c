#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int topo;
	int tamanho;
	char * str;
} tipo_pilha;

void inicia_pilha(tipo_pilha * p, int tam){
	p->topo = -1;
	p->tamanho = tam;
	p->str = (char *)malloc(tam * sizeof(char));
}

int pilha_cheia(tipo_pilha * p){
    if(p->topo >= (p->tamanho-1)){
        return 1;
    }
    return 0;
}

int pilha_vazia(tipo_pilha *p){
    if(p->topo == -1){
        return 1;
    }
    return 0;
}

void empilha(tipo_pilha * p, char c){
    if(!pilha_cheia(p)){
        p->str[++p->topo] = c;
    }
}

char desempilha(tipo_pilha * p){
    if(!pilha_vazia(p)){
        return p->str[--p->topo];
    }
}

int main(){
    char pali[100];
    scanf("%s",pali);
    tipo_pilha Pilha;
    tipo_pilha * p;
    p = &Pilha;
    
    inicia_pilha(p, strlen(pali));
    int i;
    for(i=0;i < p->tamanho;i++){
        empilha(p,pali[i]);
    }
    for(i=p->tamanho - 1;i >= 0;i--){
        if(pali[i] == p->str[(p->tamanho - 1) - i]){
            desempilha(p);
        }else{
            printf("%c não é igual a %c\n",pali[i], p->str[(p->tamanho -1) - i]);
            break;
        }
    }
    if(pilha_vazia(p)){
        printf("É palindromo!\n");
    }else{
        printf("Não é palindromo!\n");
    }
    
    return 1;
}
