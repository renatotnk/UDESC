/*
 * Author: Mateus Boiani
 * Date: July / 2016
 *
 * This library propose easily dynamic allocation in portuguese
 * language. (PT-BR)
 *
 * Instructions:
 *
 * - (realloc) realocar_memoria
 * - (malloc)  alocar_memoria
 * - (free)    desalocar_memoria
 *
 * Queries:
 *
 * - memoria_alocada
 * - variaveis_alocadas
 * - variaveis_ativas
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Good Luck!
 *
 * Copyright 2016 MateuZ Boiani <mateuz.boiani@gmail.com>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "aloca_memoria.h"

unsigned long long int total_memoria_alocada = 0;
Allocations *variables_allocated = NULL;

unsigned total_variables = 0;
unsigned activesVariables = 0;

void inicializa_memoria(){

	variables_allocated = (Allocations *) malloc( sizeof(Allocations) );

	if(variables_allocated == NULL){
		printf("Error when initialiize variables allocation system.");
		exit(EXIT_FAILURE);
	}

	variables_allocated[0].begin			= NULL;
	variables_allocated[0].sizeAllocated	= 0;
	variables_allocated[0].status			= 0;
}

int buscaPos_memoria(){
	if (variables_allocated == NULL){
		inicializa_memoria();
		return 0;
	}

	int i = 0;
	for(i = 0; i < total_variables; i++)
		if (variables_allocated[i].status == 0)
			return i;

	Allocations *new = NULL;
	new = (Allocations *) realloc (variables_allocated, (total_variables + 1) * sizeof(Allocations));

	if(new != NULL){
		variables_allocated = new;
		return total_variables;
	}else{
		free(variables_allocated);
		variables_allocated = NULL;
		printf("Error (re)allocating memory [1].\n");
		exit(EXIT_FAILURE);
	}

	return -1;
}

void *alocar_memoria(size_t size){
	void *t = NULL;
	t = (void *) malloc (size);

	if(t == NULL)
		return NULL;

	total_memoria_alocada += size;
	int i = buscaPos_memoria();
	if(i != -1){
		/* -------------------------------------------- *
		 * 	Keep safe how much memory was allocated.	*
		 * ---------------------------------------------*/
		variables_allocated[i].begin = t;
		variables_allocated[i].sizeAllocated = size;
		variables_allocated[i].status = 1;
		activesVariables++;
		total_variables++;
	}

	return t;
}

void desalocar_memoria(void *v){
	if (v != NULL){
		int j = 0;
		for (j = 0; j < total_variables; j++){
			//printf("[ %d ] v: %p | b: %p\n", j, v, variables_allocated[j].begin);
			if( v == variables_allocated[j].begin && variables_allocated[j].status == 1){
				variables_allocated[j].status = 0;
				total_memoria_alocada -= variables_allocated[j].sizeAllocated;
				variables_allocated[j].begin = NULL;
				free(v);
				v = NULL;
				activesVariables--;
			}
		}
	}else{
		printf("Variable is a (nil) Pointer\n");
	}
}

void memoria_alocada(){
	printf("Total allocated memory is %lld bytes.\n", total_memoria_alocada);
}

void variaveis_alocadas(){
	printf("Total allocated variables: %d.\n", total_variables);
}

void variaveis_ativas(){
	printf("Total released variables: %d.\n", total_variables - activesVariables);
}

void *realocar_memoria(void *v, size_t new_size){
	int j = 0;
	for (j = 0; j < total_variables; j++){
		//printf("[ %d ] v: %p | b: %p\n", j, v, variables_allocated[j].begin);
		if( v == variables_allocated[j].begin && variables_allocated[j].status == 1){
			void *new = NULL;
			new = (void *) realloc (v, new_size);
			if(new != NULL){
				if (new_size < variables_allocated[j].sizeAllocated) {
					total_memoria_alocada = total_memoria_alocada - (variables_allocated[j].sizeAllocated - new_size);
				} else {
					total_memoria_alocada = total_memoria_alocada + (new_size - variables_allocated[j].sizeAllocated);
				}

				variables_allocated[j].begin = new;
				variables_allocated[j].sizeAllocated = new_size;
				variables_allocated[j].status = 1;
				return new;
			}else{
				printf("Error (re)allocating memory [2].\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	return NULL;
}
