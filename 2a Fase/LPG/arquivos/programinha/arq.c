#include <stdio.h>
#include "banco.h"
int devedor(double s){
	return s < 0;
}

int credor(double s){
	return s > 0;
}

int zerado(double s){
	return (s == 0);
}

void relatorio(FILE *arq,int (*f)(double)){
	int conta = 0;
	double saldo = 0;
	char nome[30];
	fscanf(arq,"%d%lf%s",&conta,&saldo,nome);
	while(! feof(arq)){
		if((*f)(saldo)){
			printf("%d %s %lf\n",conta,nome,saldo);
		}
	fscanf(arq,"%d%lf%s",&conta,&saldo,nome);
	}
}