#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "matrizv3.h"
#include "matriz-operacoesv3.h"
#include "toolsv3.h"

int main(int argc, char *argv[]){
    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// DECLARAÇÃO de VARIÁVEIS
	mymatriz mat_a, mat_b;
	mymatriz **mat_soma, **mat_mult;
    matriz_bloco_t **vet_particao_a;
    matriz_bloco_t **vet_particao_b;
    matriz_bloco_t **resultado;
	char filename[100];
	FILE *fmat;
	int nr_line;
	int *vet_line = NULL;
	int N, M, La, Lb;
	double start_time, end_time;
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	if (argc != 3){
		printf ("ERRO: Numero de parametros %s <matriz_a> <matriz_b>\n", argv[0]);
		exit (1);
	}

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	//                Leitura da Matriz A (arquivo)
	fmat = fopen(argv[1],"r");
	if (fmat == NULL) {
		printf("Error: Na abertura dos arquivos.");
		exit(1);
	}
	extrai_parametros_matriz(fmat, &N, &La, &vet_line, &nr_line);
	//return 1;
	mat_a.matriz = NULL;
	mat_a.lin = N;
	mat_a.col = La;
	if (malocar(&mat_a)) {
		printf ("ERROR: Out of memory\n");
	}
	filein_matriz (mat_a.matriz, N, La, fmat, vet_line, nr_line);
	free (vet_line);
	fclose(fmat);
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	//               Leitura da Matriz B (arquivo)
	fmat = fopen(argv[2],"r");
	if (fmat == NULL) {
		printf("Error: Na abertura dos arquivos.");
		exit(1);
	}
	extrai_parametros_matriz(fmat, &Lb, &M, &vet_line, &nr_line);
	mat_b.matriz = NULL;
	mat_b.lin = Lb;
	mat_b.col = M;
	if (malocar(&mat_b)) {
		printf ("ERROR: Out of memory\n");
	}
	filein_matriz (mat_b.matriz, Lb, M, fmat, vet_line, nr_line);
	free (vet_line);
	fclose(fmat);
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	//                 Operações de Adição
	mat_soma = (mymatriz **) calloc (2,sizeof(mymatriz *));
	for (int ii=0; ii < 2; ii++) {
		printf("\n ##### somar_t%d de Matrizes #####\n", ii);
		start_time = wtime();
		mat_soma[ii] = msomar(&mat_a, &mat_a, ii);
		end_time = wtime();
		mimprimir(mat_soma[ii]);
		printf("\tRuntime: %f\n", end_time - start_time);
		sprintf(filename, "soma_t%d.result", ii);
		fmat = fopen(filename,"w");
		fileout_matriz(mat_soma[ii], fmat);
		fclose(fmat);
	}
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	printf("\n%%%%%%%%%%%%%%%%\n");

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	//               Operações de Multiplicação
	mat_mult = (mymatriz **) malloc (sizeof(mymatriz *)*6);
	for (int ii=0; ii < 6; ii++) {
		printf("\n ##### multiplicar_t%d de Matrizes #####\n", ii);
		start_time = wtime();
		mat_mult[ii] = mmultiplicar(&mat_a, &mat_b, ii);
		end_time = wtime();
		mimprimir(mat_mult[ii]);
		printf("\tRuntime: %f\n", end_time - start_time);
		sprintf(filename, "mult_t%d.result", ii);
		fmat = fopen(filename,"w");
		fileout_matriz(mat_mult[ii], fmat);
		fclose(fmat);
	}
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    return 0;
}