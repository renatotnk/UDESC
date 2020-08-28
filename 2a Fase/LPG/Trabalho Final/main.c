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

int main(){
	CPUInt *cpu = NULL;
	RAMInt *ram = NULL;
	cpu = inicializaCPU();
	ram = inicializaRAM();

	int arg;
	char arg1[TAMANHO_ID] = "";
	char arg2[TAMANHO_ID] = "";
	char arg3[TAMANHO_ID] = "";
	printf(" -------------------- Simulacao de computador -------------------- \n");
	printf("Bem-vindo ao simulador! Pressione ctrl+D para sair!\n");
	printf("Informe 3 comandos\n");
	 while((scanf("%s%s%s", arg1, arg2, arg3) != EOF  )) {
		if ((strcmp(arg1,"int")) == 0){
			arg = atoi(arg3);
			declararRAMInt (ram,arg,arg2);
			printa_registradores(cpu,ram);
		}else if ((strcmp(arg1,CPUInt_instrucoes[0])) == 0) {
			executarLoadCPUInt(cpu,ram,arg2,arg3);
			printa_registradores(cpu,ram);
		}else if (strcmp(arg1,CPUInt_instrucoes[1]) == 0) {
			executarStoreCPUInt(cpu,ram,arg2,arg3);
			printa_registradores(cpu,ram);
		}else if(strcmp (arg1,CPUInt_instrucoes[2]) == 0) {
			strcpy(cpu->instrucao,arg1);
			calculadora(cpu,arg2,arg3);
			printa_registradores(cpu,ram);
		}else if (strcmp (arg1,CPUInt_instrucoes[3]) == 0)  {
			strcpy(cpu->instrucao,arg1);
			calculadora(cpu,arg2,arg3);
			printa_registradores(cpu,ram);
		}else if (strcmp (arg1,CPUInt_instrucoes[4]) == 0) {
			strcpy(cpu->instrucao,arg1);
			calculadora(cpu,arg2,arg3);
			printa_registradores(cpu,ram);
		}else if (strcmp (arg1,CPUInt_instrucoes[5]) == 0) {
			strcpy(cpu->instrucao,arg1);
			calculadora(cpu,arg2,arg3);
			printa_registradores(cpu,ram);
		}else if (strcmp (arg1,CPUInt_instrucoes[6]) == 0) {
			removerRAMInt (ram, 0, arg2);
			printa_registradores(cpu,ram);
		}else if(strcmp (arg1, CPUInt_instrucoes[7]) == 0) {
			strcpy(cpu->instrucao,arg1);
		 	savecheckpoint (cpu, ram);
		}else if(strcmp (arg1, CPUInt_instrucoes[8]) == 0) {
			strcpy(cpu->instrucao,arg1);
			loadcheckpoint	(cpu, ram);
			printa_registradores(cpu, ram);
	
		}else{
			printf("Operação inválida!\n");
		}
	}
	
	destruirCPU (cpu);
	destruirRAM (ram);
	memoria_alocada();
	variaveis_alocadas();
    	variaveis_ativas();
	printf("Programa encerrado com sucesso!\n");
	return 0;
}
