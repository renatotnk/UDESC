#include "matrizv3.h"
#include <time.h>

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int malocar (mymatriz *matriz){
	int **newMatriz = NULL;

	newMatriz = (int **) malloc(matriz->lin*sizeof(int *));
	if (!newMatriz) {
		printf("ERROR: Out of memory\n");
		return 1;
	}
	for (int i =0; i < matriz->lin; i++) {
		newMatriz[i] = (int *) malloc(sizeof(int)*matriz->col);
		if (!newMatriz) {
			printf("ERROR: Out of memory\n");
			return 1;
		}
	}

	matriz->matriz = newMatriz;
	return 0;
}

int** alocar_matriz(int linha, int coluna){

	int **newMatriz = NULL;

	newMatriz = (int **) malloc(linha * sizeof(int *));
	if (!newMatriz){
		printf("ERROR: Out of memory\n");
		exit(EXIT_FAILURE);
	}
	for (int i =0; i < linha; i++) {
		newMatriz[i] = (int *) malloc(sizeof(int) * coluna);
		if (!newMatriz) {
			printf("ERROR: Out of memory\n");
			exit(EXIT_FAILURE);
		}
	}

	return newMatriz;
}

int zerar_matriz(int** matriz, int linha, int coluna){
	for (int i=0; i < linha; i++){
		for (int j=0; j < coluna; j++){
				matriz[i][j] = 0;
		}
	}	
	return 0;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% MATRIZ %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int mgerar(mymatriz *matriz, int valor){
	srand( (unsigned)time(NULL) );

	for (int i=0; i < matriz->lin; i++){
		for (int j=0; j < matriz->col; j++){
			if (valor == -9999){
				matriz->matriz[i][j] = rand() % 3;
			}else{
				matriz->matriz[i][j] = valor;
			}
		}
	}	
	return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int mimprimir (mymatriz *matriz){
	int linha, coluna;
	linha = matriz->lin;
	coluna = matriz->col;

	if (linha > 9) {
		linha = 9;
	}

	if (coluna > 9) {
		coluna = 9;
	}

	for (int j =0; j < coluna; j++)
	printf("\t(%d)", j);
	printf("\n");
	for (int i=0; i < linha; i++) {
		printf("(%d)", i);
		for (int j=0; j < coluna; j++){
			printf("\t%d", matriz->matriz[i][j]);
		}
		printf("\n");
	}

	if ((matriz->lin > 4) || (matriz->col > 4)) {
		printf("\n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n \
		WARNING: Impressão truncada em 4x4! \n \
		WARNING: Último elemento matriz[%d][%d] = %d \n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n", \
		matriz->lin-1, matriz->col-1, matriz->matriz[matriz->lin-1][matriz->col-1]);
	}

	return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int mliberar (mymatriz *matriz) {
	for (int i =0; i < matriz->lin; i++) {
		//printf("%p\n", matriz->matriz[i]);
		free(matriz->matriz[i]);
	}
	free(matriz->matriz);
	return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int mzerar (mymatriz *matriz){
	return mgerar(matriz,0);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int mcomparar (mymatriz *mat_a, mymatriz *mat_b){
	for (int j =0; j < mat_a->col; j++)
	for (int i=0; i < mat_a->lin; i++) {
		for (int j=0; j < mat_a->col; j++){
			if (mat_a->matriz[i][j] != mat_b->matriz[i][j]) {
				printf("O elemento [%d,%d] é diferente nas matrizes analisadas!", i,j);
				return 1;
			}
		}
	}
	printf("\tVERIFICADO: Matrizes idênticas\n");
	return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
int gerar_submatriz (int **mat_origem, matriz_bloco_t *submatriz, bloco_t *bloco) {
	bloco_t *newblock;

	submatriz->matriz = mat_origem;
	newblock = (bloco_t *) malloc (sizeof(bloco_t));
	newblock->lin_inicio = bloco->lin_inicio;
	newblock->lin_fim = bloco->lin_fim;
	newblock->col_inicio = bloco->col_inicio;
	newblock->col_fim = bloco->col_fim;
	printf ("Estrutura lin_inicio %d,%d\n", newblock->lin_inicio, bloco->lin_inicio);
	submatriz->bloco = newblock;
	printf ("Estrutura submatriz_lin_inicio %d\n", submatriz->bloco->lin_inicio);
	return 0;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int imprimir_submatriz (matriz_bloco_t *submatriz){
	for (int j = submatriz->bloco->col_inicio; j <= submatriz->bloco->col_fim; j++)
	printf("\t(%d)", j);
	printf("\n");
	for (int i= submatriz->bloco->lin_inicio; i <= submatriz->bloco->lin_fim; i++) {
		printf("(%d)", i);
		for (int j= submatriz->bloco->col_inicio; j <= submatriz->bloco->col_fim; j++){
			printf("\t%d", submatriz->matriz[i][j]);
			if (submatriz->matriz[i][j] < 0)
			  printf("\t ERROR \n");
				return 1;
		}
		printf("\n");
	}
	return 0;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int imprimir_bloco (matriz_bloco_t *submatriz) {

	printf("## Bloco (BEGIN) ##\n");
	printf("Submatriz[lin_ini,col_ini] = %d\n", submatriz->matriz[submatriz->bloco->lin_inicio][submatriz->bloco->col_inicio]);
	printf("Submatriz[lin_fim,col_fim] = %d\n", submatriz->matriz[submatriz->bloco->lin_fim][submatriz->bloco->col_fim]);
	printf("Matriz (%p) (l_i,c_i) = (%d,%d) (l_f,c_f) = (%d,%d) \n", submatriz->matriz, submatriz->bloco->lin_inicio, submatriz->bloco->col_inicio, submatriz->bloco->lin_fim, submatriz->bloco->col_fim);
	printf("mat_lin/mat_col/divisor = (%d,%d,%d) \n", submatriz->mat_lin, submatriz->mat_col, submatriz->divisor);
	printf("## Bloco (END) ##\n");
	return 0;
}
*/

matriz_bloco_t **constroi_submatrizv3 (int mat_lin, int mat_col, int divisor) {
	matriz_bloco_t **m = (matriz_bloco_t**) malloc(divisor * sizeof(matriz_bloco_t*));

	for (int i=0; i<divisor; i++){
		m[i] = (matriz_bloco_t*) malloc(sizeof(matriz_bloco_t));
		m[i]->bloco = (bloco_t*) malloc(sizeof(bloco_t));

		mymatriz *aux = (mymatriz*) malloc(sizeof(mymatriz));
		aux->lin = mat_lin;
		aux->col = mat_col;
		malocar(aux);
		mzerar(aux);

		m[i]->matriz = aux;
		m[i]->bloco->lin_inicio = 0;
		m[i]->bloco->lin_fim = mat_lin;
		m[i]->bloco->col_inicio = 0;
		m[i]->bloco->col_fim = mat_col;
	}

	return m;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// divisor corresponde ao nro de particoes
// orientacao, 0 corte horizontal, 1 para corte vertical
matriz_bloco_t **particionar_matrizv3 (int **matriz, int mat_lin, int mat_col, int orientacao, int divisor) {
	matriz_bloco_t **m = (matriz_bloco_t**) malloc(divisor*sizeof(matriz_bloco_t*));

	mymatriz *matriz_st = (mymatriz*) malloc(sizeof(mymatriz));
	matriz_st->matriz = matriz;

	int k;
	switch (orientacao) {
	case 0:
		k = mat_lin/divisor;
		for (int i=0; i<divisor; i++) {
			m[i] = (matriz_bloco_t*) malloc(sizeof(matriz_bloco_t));
			m[i]->bloco = (bloco_t*) malloc(sizeof(bloco_t));
			m[i]->matriz = matriz_st;
			m[i]->bloco->lin_inicio = k*i;
			m[i]->bloco->lin_fim = m[i]->bloco->lin_inicio + k;
			m[i]->bloco->col_inicio = 0;
			m[i]->bloco->col_fim = mat_col;
		}
		m[divisor-1]->bloco->lin_fim = mat_lin;
		break;

	default:
		k = mat_col/divisor;
		for (int i=0; i<divisor; i++) {
			m[i] = (matriz_bloco_t*) malloc(sizeof(matriz_bloco_t));
			m[i]->bloco = (bloco_t*) malloc(sizeof(bloco_t));
			m[i]->matriz = matriz_st;
			m[i]->bloco->col_inicio = k*i;
			m[i]->bloco->col_fim = m[i]->bloco->col_inicio + k;
			m[i]->bloco->lin_inicio = 0;
			m[i]->bloco->lin_fim = mat_lin;
		}
		m[divisor-1]->bloco->col_fim = mat_col;
	}

	return m;
}


matriz_bloco_t  *particionar_matrizv4(mymatriz *mat, int orientacao, int divisor, int start) {
	matriz_bloco_t *m = (matriz_bloco_t*) malloc(sizeof(matriz_bloco_t));

	m->bloco = (bloco_t*) malloc(sizeof(bloco_t));
	m->matriz = mat;

	switch (orientacao) {
		case 0:
			m->bloco->lin_inicio = start;
			m->bloco->lin_fim = m->bloco->lin_inicio + divisor;
			m->bloco->col_inicio = 0;
			m->bloco->col_fim = mat->col;
			break;
		
		default:
			m->bloco->lin_inicio = 0;
			m->bloco->lin_fim = mat->lin;
			m->bloco->col_inicio = start;
			m->bloco->col_fim = m->bloco->col_inicio + divisor;
			break;
	}

	return m;
}


matriz_bloco_t *constroi_submatrizv4(int mat_lin, int mat_col){
	matriz_bloco_t *m = (matriz_bloco_t*) malloc(sizeof(matriz_bloco_t));

	m->bloco = (bloco_t*) malloc(sizeof(bloco_t));
	m->matriz = (mymatriz*) malloc(sizeof(mymatriz));
    m->matriz->lin = mat_lin;
    m->matriz->col = mat_col;
    malocar(m->matriz);
    mzerar(m->matriz);

    m->bloco->lin_inicio = 0;
    m->bloco->lin_fim = mat_lin;
    m->bloco->col_inicio = 0;
    m->bloco->col_fim = mat_col;

	return m;
}

/*
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
matriz_bloco_t **liberar_submatriz (matriz_bloco_t **submatriz) {
  	int nro_submatrizes;

	nro_submatrizes = submatriz[0]->divisor;
	for (int i = 0; i < nro_submatrizes; i++) {
		free (submatriz[i]->bloco);
		free (submatriz[i]);
	}
	free (submatriz);
	return NULL;
}
*/
