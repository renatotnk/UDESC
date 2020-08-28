#include "matriz-operacoesv3.h"
#include<stdio.h>

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% MATRIZ %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mymatriz *msomar (mymatriz *mat_a, mymatriz *mat_b, int tipo) {
	mymatriz *mat_c = NULL;

	if ((mat_a->lin != mat_b-> lin) || (mat_a->col != mat_b->col)){
		printf ("Erro: Matrizes incompatíveis!\n");
		exit(1);
	}

	mat_c = (mymatriz *) malloc (sizeof(mymatriz));
	mat_c->lin = mat_a->lin;
	mat_c->col = mat_a->col;

	if (malocar(mat_c)){
		printf ("ERROR: Out of memory\n"); 
	}

	if (tipo == 1) {
		for (int i=0; i < mat_c->lin; i++)
		  for (int j=0; j < mat_c->col; j++)
					mat_c->matriz[i][j] = mat_a->matriz[i][j]+mat_b->matriz[i][j];
	} else {
		for (int j=0; j < mat_c->col; j++)
			for (int i=0; i < mat_c->lin; i++)
					mat_c->matriz[i][j] = mat_a->matriz[i][j]+mat_b->matriz[i][j];
	}
  	return mat_c;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void* multiplicarth (void *arg) {
	int i;
	param_t *p = (param_t *) arg;

	for(i = p->lini; i < p->lfim; i++){
		for(int j = 0; j < p->M; j++){
			for(int k = 0; k < p->L; k++){
				p->mat_cPar->matriz[i][j] += p->mat_a->matriz[i][k] * p->mat_b->matriz[k][j];
			}
		}
	}
	return 0; 
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mymatriz *mmultiplicar (mymatriz *mat_a, mymatriz *mat_b, int tipo) {
	if (mat_a->col != mat_b->lin){
		printf("Matrizes de formato incompativel\n");
        exit(EXIT_FAILURE);
	}

	mymatriz *mat_c = NULL;
	mat_c = (mymatriz *) malloc (sizeof(mymatriz));
	mat_c->lin = mat_a->lin;
	mat_c->col = mat_b->col;

	if(malocar(mat_c)){
		printf ("ERROR: Out of memory\n");
	}

	mzerar(mat_c);

	int i = 0, j = 0, k = 0;
	int c_Lin = mat_a->lin;
	int c_Col = mat_b->col;
	
	for(i = 0; i < c_Lin; i++){
		for(j = 0; j < c_Col; j++){
			for(k = 0; k < mat_a->col; k++){
				mat_c->matriz[i][j] += mat_a->matriz[i][k] * mat_b->matriz[k][j];
			}
		}
	}

	return mat_c;
}

mymatriz *transpor(mymatriz *mat){
  mymatriz *mat_trans = (mymatriz *) malloc (sizeof(mymatriz));
	mat_trans->lin = mat->col;
	mat_trans->col = mat->lin;

  if (malocar(mat_trans)) printf ("ERROR: Out of memory\n");

  for (int i=0; i<mat_trans->lin; i++)
    for (int j=0; j<mat_trans->col; j++)
      mat_trans->matriz[i][j] = mat->matriz[j][i];
  
  return mat_trans;
}

int min(int a, int b){
    if (a > b)
        return b;
    return a;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicar_submatriz (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc) {
    for (int i = mat_suba->bloco->lin_inicio; i<mat_suba->bloco->lin_fim; i++){
    	for (int j = mat_subb->bloco->col_inicio; j<mat_subb->bloco->col_fim; j++) {
      		mat_subc->matriz->matriz[i][j] = 0;
      		for (int k = mat_suba->bloco->col_inicio; k<mat_suba->bloco->col_fim; k++){
        		mat_subc->matriz->matriz[i][j] += mat_suba->matriz->matriz[i][k] * mat_subb->matriz->matriz[k][j];
			}
    	}
	}

  	return 1;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mymatriz *omp_mmultiplicar (mymatriz *mat_a, mymatriz *mat_b, int threads) {
	mymatriz *mat_c = (mymatriz *) malloc (sizeof(mymatriz));
	mat_c->lin = mat_a->lin;
	mat_c->col = mat_b->col;
	if(malocar(mat_c)){
		printf ("ERROR: Out of memory\n");
	}
	if(mzerar(mat_c)){
		printf ("ERRO: Matriz nao zerada!\n");
	}

	int i, j , k;
	printf("Multiplicando matriz com %d threads\n", threads);
	#pragma omp parallel for num_threads(threads) private(i,j,k)
		for (i=0; i<mat_a->lin; i++){
        	for (j=0; j<mat_b->col; j++){
            	for(k=0; k<mat_a->col; k++){
                	mat_c->matriz[i][j] += mat_a->matriz[i][k] * mat_b->matriz[k][j];
				}
			}
		}
	return mat_c;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mymatriz *omp_multiplicar_bloco (mymatriz *mat_a,mymatriz *mat_b, int threads){
	matriz_bloco_t **A = particionar_matrizv3(mat_a->matriz, mat_a->lin, mat_a->col, 1, threads);
    matriz_bloco_t **B = particionar_matrizv3(mat_b->matriz, mat_b->lin, mat_b->col, 0, threads);
    matriz_bloco_t **C = constroi_submatrizv3(mat_a->lin, mat_b->col, threads);

    mymatriz *resultado = (mymatriz*)malloc(sizeof(mymatriz));
    resultado->lin = mat_a->lin;
    resultado->col = mat_b->col;

    if(malocar(resultado)){
		printf ("ERROR: Out of memory\n");
	}
	if(mzerar(resultado)){
		printf ("ERRO: Matriz nao zerada!\n");
	}

    int tid;
	//printf("Multiplicando matriz em bloco com %d threads\n", threads);

    #pragma omp parallel num_threads(threads) private(tid)
    {

		tid = omp_get_thread_num();

		multiplicar_submatriz(A[tid], B[tid], C[tid]);

		#pragma omp critical
		{
			mymatriz *aux = msomar(resultado, C[tid]->matriz, 0);
			mliberar(resultado);
			free(resultado);
			resultado = aux;
		}

		free(A[tid]->bloco);
		free(A[tid]);
		free(B[tid]->bloco);
		free(B[tid]);
		free(C[tid]->bloco);
		mliberar(C[tid]->matriz);
		free(C[tid]->matriz);
		free(C[tid]);

    }

    free(A);
    free(B);
    free(C);

    return resultado;
}

mymatriz *mpi_multiplicar (mymatriz *mat_a, mymatriz *mat_b, int rank, int size) {	
	//MULTIPLICACAO DISTRIBUIDA
	mymatriz *mat_c = NULL;

	if(mat_a == NULL || mat_b != NULL){
		return omp_multiplicar_bloco(mat_a, mat_b, size);
	} 
	
	//Porque nao funciona?????

    // Envia dados da matriz B para todos os nós:
    MPI_Bcast(&mat_b->lin, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&mat_b->col, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// Aloca matriz b em outros nós senão o root
    if(rank){
        malocar(mat_b);
	}
	//Envia Matriz B em si
    MPI_Bcast(&mat_b->matriz[0][0], mat_b->lin * mat_b->col, MPI_INT, 0, MPI_COMM_WORLD);

    // Envia nro de linhas de A:
    int a_lin;
    if(!rank){
        a_lin = mat_a->lin;
	}
    MPI_Bcast(&a_lin, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Gera matriz de linhas de A e faz scatter das linhas de A:
    mymatriz *mat_a_linha = (mymatriz*) malloc(sizeof(mymatriz));

	//Reparte as linhas de A de acordo com o nro de processos
    mat_a_linha->lin = ceil(a_lin/(float)size);
    mat_a_linha->col = mat_b->lin;
    malocar(mat_a_linha);

    // Matriz A é alimentada com os dados dos nós e gerenciada pelo processo de rank 0
	if (!rank){
        MPI_Scatter(&mat_a->matriz[0][0], mat_a_linha->lin * mat_a_linha->col, MPI_INT, &mat_a_linha->matriz[0][0], mat_a_linha->lin * mat_a_linha->col, MPI_INT, 0, MPI_COMM_WORLD);
	} else {
        MPI_Scatter(NULL, mat_a_linha->lin * mat_a_linha->col, MPI_INT, &mat_a_linha->matriz[0][0], mat_a_linha->lin * mat_a_linha->col, MPI_INT, 0, MPI_COMM_WORLD);
	}

    // Gera matriz resultado para compor C:
    mymatriz *mat_c_resultado = mmultiplicar(mat_a_linha, mat_b, 0);

    // Une os resultados em C:
    if(!rank){
        mat_c = (mymatriz *) malloc (sizeof(mymatriz));
        mat_c->lin = size * mat_a_linha->lin;
        mat_c->col = mat_b->col;
        malocar(mat_c);
		// Gather para compor matriz C
        MPI_Gather(&mat_c_resultado->matriz[0][0], mat_c_resultado->lin * mat_c_resultado->col, MPI_INT, &mat_c->matriz[0][0], mat_c_resultado->lin * mat_c_resultado->col, MPI_INT, 0, MPI_COMM_WORLD);
        mat_c->lin = mat_a->lin;
    } else {
		// Se der errado, nao alimente
        MPI_Gather(&mat_c_resultado->matriz[0][0], mat_c_resultado->lin * mat_c_resultado->col, MPI_INT, NULL, mat_c_resultado->lin * mat_c_resultado->col, MPI_INT, 0, MPI_COMM_WORLD);
    }

    // Libera a memória:
    mliberar(mat_c_resultado);
    free(mat_c_resultado);
    mliberar(mat_a_linha);
    free(mat_a_linha);

    return mat_c;
}

