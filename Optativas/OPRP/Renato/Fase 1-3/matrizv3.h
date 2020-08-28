#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SOME_HEADER_FILE_H
#define SOME_HEADER_FILE_H

typedef struct {
  int **matriz;
  int lin;
  int col;
} mymatriz;

typedef struct {
  int lin_inicio;
  int lin_fim;
  int col_inicio;
  int col_fim;
} bloco_t;

typedef struct {
  mymatriz *matriz;
  bloco_t *bloco;
} matriz_bloco_t;
#endif

int** alocar_matriz(int linha, int coluna);
int zerar_matriz(int** matriz, int linha, int coluna);

int mzerar (mymatriz *matriz);
int malocar (mymatriz *matriz);
int mliberar (mymatriz *matriz);
int mimprimir (mymatriz *matriz);
int mgerar(mymatriz *matriz, int valor);
int mcomparar (mymatriz *mat_a, mymatriz *mat_b);

matriz_bloco_t **constroi_submatrizv3 (int mat_lin, int mat_col, int divisor);
matriz_bloco_t *constroi_submatrizv4(int mat_lin, int mat_col);
matriz_bloco_t **particionar_matrizv3 (int **matriz, int mat_lin, int mat_col, int orientacao, int divisor);
matriz_bloco_t  *particionar_matrizv4(mymatriz *mat, int orientacao, int divisor, int start);