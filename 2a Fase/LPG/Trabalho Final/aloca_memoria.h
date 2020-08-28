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

#ifndef _ALOCA_MEMORIA_H_
#define _ALOCA_MEMORIA_H_

/* -------------------------------------------- *
 * 	Keep safe how much memory was allocated:	*
 * 	begin: Address where started the allocation.*
 * 	sizeAllocated: Size of allocated variable.	*
 * 	status: If the variable still is active.	*
 * ---------------------------------------------*/
typedef struct{
	void *begin;
	size_t sizeAllocated;
	short status;
} Allocations;

void inicializa_memoria();
int buscaPos_memoria();
void *alocar_memoria(size_t);
void desalocar_memoria(void *);
void memoria_alocada();
void variaveis_alocadas();
void variaveis_ativas();
void *realocar_memoria(void *, size_t);

#endif
