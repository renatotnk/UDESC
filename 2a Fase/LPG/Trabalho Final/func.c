/*
Aluno: Renato Tanaka,Johnnathan Victor Sabba
Trabalho 2 LPG
Professor: Guilherme
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aloca_memoria.h"
#include "func.h"


CPUInt * inicializaCPU (void) {
	CPUInt *ret  = NULL;
	if(!(ret = alocar_memoria(sizeof(CPUInt)))){
			printf("[inicializa_CPU] Sem memória\n");
			exit(EXIT_FAILURE);
	}
	ret->reg1 = 0;
	ret->reg2 = 0;
	ret->instrucao = (char *) alocar_memoria (sizeof(10)) ;
	return ret;
}

RAMInt * inicializaRAM (void) {
	RAMInt *ret = NULL;
	if(!(ret = alocar_memoria(sizeof(RAMInt)))){
			printf("[inicializaRAM] Sem memória\n");
			exit(EXIT_FAILURE);
	}
	ret->elementos = 0;
	ret->variaveis = NULL;
	return ret;
}

void declararRAMInt (RAMInt * ram ,int valor ,char * id){
	int tam_atual = ram->elementos;
	Variavel *tmp = NULL;
	if(tam_atual == 0)
		tmp = alocar_memoria(sizeof(Variavel));
	else
		tmp = realocar_memoria(ram->variaveis, sizeof(Variavel)*(tam_atual +1) );

	if(tmp == NULL){
		printf("temporariamente sem memoria\n");
		exit(EXIT_FAILURE);
	}
	ram->variaveis = tmp;
	ram->variaveis[tam_atual].valor = valor;
	strcpy(ram->variaveis[tam_atual].identificador, id);
	ram->elementos = tam_atual +1;
}


int buscando_variavel(RAMInt *variaveis,char *elemento){
	int i;
	for(i = 0; i < variaveis->elementos; i++){
		if(strcmp(variaveis->variaveis[i].identificador, elemento) == 0){
			return i;
		}
	}
	return -1;
}

void executarStoreCPUInt (CPUInt * cpu ,RAMInt * ram ,char * dest ,char * orig){
	int f = buscando_variavel(ram, dest);
	if(f != -1){
		if(strcmp(orig, "reg1") == 0){
			ram->variaveis[f].valor = cpu->reg1;
		} else if (strcmp(orig, "reg2") == 0){
			ram->variaveis[f].valor = cpu->reg2;
		} else {
			printf("erro ao atribuir registrador\n");
		}
	}

}


void executarLoadCPUInt  (CPUInt * cpu ,RAMInt * ram ,char * dest ,char * orig){
	int g = buscando_variavel(ram, orig);
	printf("Esta na posicao: %d\n", g);
	if (g != -1){
		if(strcmp(dest, "reg1") == 0){
			cpu->reg1 = ram->variaveis[g].valor;
			printf("%d\n", cpu->reg1);
		} else if (strcmp(dest, "reg2") == 0) {
			cpu->reg2 = ram->variaveis[g].valor;
			printf("%d\n", cpu->reg2);
		} else {
			printf("erro ao carregar variável\n");
		}
	}
}

void printa_registradores(CPUInt * cpu ,RAMInt * ram){
	printf(" ------------- Registradores ------------- \n");
	printf("%d %d\n", cpu->reg1, cpu->reg2);
	int i = 0;
	printf(" ------------- Memoria ------------- \n");
	for(i = 0; i < ram->elementos; i++)
		printf("%s %d\n", ram->variaveis[i].identificador, ram->variaveis[i].valor);
}

void calculadora (CPUInt *cpu, char *dest, char *orig){
	int a , b;
	if( (strcmp(dest,"reg1") == 0) && (strcmp(orig,"reg2") == 0)){
		a = cpu->reg1;
		b = cpu->reg2;
	} else if( (strcmp(dest,"reg2") == 0) && (strcmp(orig,"reg1") == 0)) {
		a = cpu->reg2;
		b = cpu->reg1;
	} else if( (strcmp(dest,"reg1") == 0) && (strcmp(orig,"reg1") == 0)) {
		a = cpu->reg1;
		b = cpu->reg1;
	} else if( (strcmp(dest,"reg2") == 0) && (strcmp(orig,"reg2") == 0)){
		a = cpu->reg2;
		b = cpu->reg2;
	}else{
		printf("Destino e/ou origem inválidos. (reg1 ou reg2)\n");
		exit(EXIT_FAILURE);
	}

	int resultado = 0;

	if( strcmp(cpu->instrucao, CPUInt_instrucoes[2]) == 0){
		printf("Operação selecionada de soma\n");
		resultado = a + b;
	} else if(strcmp(cpu->instrucao, CPUInt_instrucoes[3]) == 0)  {
		printf("Operação selecionada de subtracao\n");
		resultado = a - b;
	} else if(strcmp(cpu->instrucao, CPUInt_instrucoes[4]) == 0) {
		printf("Operação selecionada de multiplicacao\n");
		resultado = a * b;
	} else if(strcmp(cpu->instrucao, CPUInt_instrucoes[5]) == 0){
		printf("Operação selecionada de divisao\n");
		resultado = a / b;
	}

	if( strcmp(dest,"reg1") == 0) {
		cpu->reg1 = resultado;
	}else if (strcmp(dest,"reg2") == 0){
		cpu->reg2 = resultado;
	}

}

void removerRAMInt (RAMInt * ram ,int valor ,char * id){
	Variavel *p = NULL;
	Variavel aux;
	int posicao = buscando_variavel(ram,id);
	int ultima_posicao = ram->elementos - 1;
	if ( posicao == -1){
		printf("Variavel nao encontrada!\n");
	}else if(ram->elementos == 1){
			desalocar_memoria(ram->variaveis);
			ram->elementos--;
			printf("Variavel removida com sucesso!\n");
	}else if (ram->elementos > 1){
		aux = ram->variaveis[posicao];
		ram->variaveis[posicao] = ram->variaveis[ultima_posicao];
		ram->variaveis[ultima_posicao] = aux;
		p = realocar_memoria(ram->variaveis, sizeof(Variavel)* ram->elementos-1);
		if(p != NULL){
			ram->variaveis = p;
			ram->elementos--;
			printf("Variavel removida com sucesso!\n");
		}
	}
}
int savecheckpoint (CPUInt *cpu, RAMInt *ram){
	FILE * arqsave = NULL;
	int i;
	if ((arqsave = fopen("save.txt", "w+")) == NULL) {
		printf("Não foi possivel Criar o Arquivo Save\n");
		exit(1);
	}
	fprintf(arqsave,"%d ",ram->elementos); /*Salva Elementos da Ram (variaveis[elementos]*/
	fprintf(arqsave, "%d ",cpu->reg1 ); /*Salva Variavel em REG1*/
	fprintf(arqsave, "%d ",cpu->reg2 );/*Salva Variavel em REG2*/
	for(i = 0; i < ram->elementos; ++i) {
		fprintf(arqsave, "% d ",ram->variaveis[i].valor);
	}
	for(i = 0; i < ram->elementos; ++i) {
		fprintf(arqsave, " %s ",ram->variaveis[i].identificador);
	}
	fclose(arqsave);
	
	printf("Programa encerrado e salvo!\n");	
	return 0;
	


}

void loadcheckpoint(CPUInt *cpu, RAMInt *ram) {
	FILE * arqload = NULL;
	
	int i;
	
		if ((arqload = fopen("save.txt", "r")) == NULL) {
		printf("Não foi possivel recuperar o progresso salvo anteriormente\n");
		exit(EXIT_FAILURE);
	}

	
	fscanf(arqload, "%d %d %d",&ram->elementos, &cpu->reg1, &cpu->reg2);
	ram->variaveis = alocar_memoria(ram->elementos * sizeof(Variavel));
	if(ram->variaveis == NULL) {
		printf("Temporariamente sem Memoria\n");
		exit(EXIT_FAILURE);
		}
	 
for (i = 0; i < ram->elementos; ++i) {
	fscanf(arqload, " %d",&ram->variaveis[i].valor);
}
for (i = 0; i < ram->elementos; ++i) {
	fscanf(arqload, " %s",ram->variaveis[i].identificador);	
	
	
}
fclose(arqload);
}


void destruirCPU (CPUInt * cpu){
desalocar_memoria(cpu->instrucao);
desalocar_memoria(cpu);
}

void destruirRAM (RAMInt * ram){
desalocar_memoria(ram->variaveis);

desalocar_memoria(ram);
}
