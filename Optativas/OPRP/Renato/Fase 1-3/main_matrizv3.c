#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <omp.h>
#include <mpi.h>
#include "toolsv3.h"
#include "matrizv3.h"
#include "matriz-operacoesv3.h"
//#define DEBUG
#define MPIrun

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char *argv[]) {

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// DECLARAÇÃO de VARIÁVEIS
	mymatriz mat_a, mat_b, mat_cPar;
	mymatriz **mat_soma = NULL, **mat_mult = NULL;
	mymatriz *ompMat_mult = NULL, *mat_cFinalOMP = NULL;
	mymatriz *mat_cFinal = (mymatriz *) malloc(sizeof(mymatriz *));

	char filename[100];
	FILE *fmat;
	int nr_line;
	int *vet_line = NULL;
	int N, M, La, Lb, ntasks = 0;
	double start_time = 0, end_time = 0;
	int tipo_multMat = 2;
	double times[20];
	int contTimes = 0;
	
	matriz_bloco_t **submatA = NULL;
	matriz_bloco_t **submatB = NULL;
	matriz_bloco_t **submatC = NULL;

	int rank, size;
	mymatriz *mat_cMPI = NULL;

	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	if (argc < 3){
		printf ("ERRO: Numero de parametros %s <matriz_a> <matriz_b> <nro_tarefas>\n", argv[0]);
		exit (1);
	}

	if (!rank){
		printf("\n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n \
		#####  \t Leitura das matrizes A e B (%s)  \t #####\n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n",argv[1]);

		// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
		//                Leitura da Matriz A (arquivo)
		fmat = fopen(argv[1],"r");
		if (fmat == NULL) {
			printf("Error: Na abertura dos arquivos.");
			exit(1);
		}

		ntasks = size;

		extrai_parametros_matriz(fmat, &N, &La, &vet_line, &nr_line);
		mat_a.matriz = NULL;
		mat_a.lin = N;
		mat_a.col = La;
		if (malocar(&mat_a)) {
			printf ("ERROR: Out of memory\n");
		}
		filein_matriz (mat_a.matriz, N, La, fmat, vet_line, nr_line);
		free (vet_line);
		fclose(fmat);

		#ifndef DEBUG
		printf("\n ##### Matriz A (%d,%d) (Lin/Col) #####\n", mat_a.lin, mat_a.col);
		//printf("N = %d, La = %d\n", N, La);
		//mimprimir(&mat_a);
		#endif

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

		#ifndef DEBUG
		printf("\n ##### Matriz B (%d,%d) (Lin/Col) #####\n", mat_b.lin, mat_b.col);
		//printf("M = %d, Lb = %d\n", M, Lb);
		//mimprimir(&mat_b);
		#endif

		// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
	}

	if (!rank){
		// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
		//                 Operações de Adição
		printf("\n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n \
		##### \t Operações de soma ##### \t \n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n");

		mat_soma = (mymatriz **) calloc (2,sizeof(mymatriz *));
		for (int ii=0; ii < 2; ii++) {
			printf("\n ##### somar_t%d de Matrizes (A + A) #####\n", ii);

			// ### Início do Núcleo	###
			start_time = wtime();
			mat_soma[ii] = msomar(&mat_a, &mat_a, ii);
			end_time = wtime();
			// ### Fim do Núcleo	###

			#ifndef DEBUG
			//mimprimir(mat_soma[ii]);
			printf("\tRuntime: %f\n", end_time - start_time);
			#endif

			times[contTimes++] = end_time - start_time;
			sprintf(filename, "soma_t%d.result", ii);
			fmat = fopen(filename,"w");
			fileout_matriz(mat_soma[ii], fmat);
			fclose(fmat);
		}
		// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
	}

	if (!rank){
		printf("\n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n \
		#### \t Operações de multiplicação (Sequencial) #### \t \n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n");

		// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
		//               Operações de Multiplicação
		mat_mult = (mymatriz **) malloc (sizeof(mymatriz *)*tipo_multMat);
		for (int ii=0; ii < tipo_multMat; ii++) {
			printf("\n ##### multiplicar_t%d de Matrizes #####\n", ii);

			// ### Início do Núcleo	###
			start_time = wtime();
			mat_mult[ii] = mmultiplicar(&mat_a, &mat_b, ii);
			end_time = wtime();
			// ### Fim do Núcleo	###

			#ifndef DEBUG
			printf("\n ##### Matriz C (no main) #####\n");
			//mimprimir(mat_mult[ii]);
			printf("\tRuntime: %f\n", end_time - start_time);
			#endif

			times[contTimes++] = end_time - start_time;
			sprintf(filename, "mult_t%d.result", ii);
			fmat = fopen(filename,"w");
			fileout_matriz(mat_mult[ii], fmat);
			fclose(fmat);
		}
		// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
	}

	if (!rank){
		// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
		//               Operações de Multiplicação em bloco
		printf("\n ##### multiplicar_t0 de Matrizes (bloco) #####\n");

		// ### Início do Núcleo	###
		start_time = wtime();
		submatA = particionar_matrizv3(mat_a.matriz, N, La, 1, 2);
        submatB = particionar_matrizv3(mat_b.matriz, Lb, M, 0, 2);
        submatC = constroi_submatrizv3(N, M, 2);

        multiplicar_submatriz(submatA[0], submatB[0], submatC[0]);
        multiplicar_submatriz(submatA[1], submatB[1], submatC[1]);

        mat_cFinal = msomar(submatC[0]->matriz, submatC[1]->matriz, 0);
		end_time = wtime();
		// ### Fim do Núcleo	###

		#ifndef DEBUG
		//printf("\n ##### Matriz C (no main) #####\n");
		//mimprimir(mat_cFinal);
		printf("\tRuntime: %f\n", end_time - start_time);
		#endif

		times[contTimes++] = end_time - start_time;
		sprintf(filename, "mult_SeqBl0.result");
		fmat = fopen(filename,"w");
		fileout_matriz(mat_cFinal, fmat);
		fclose(fmat);
		// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
	}

		
	if (!rank){
		printf("\n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n \
		#### \t Operações de multiplicação (Paralelo) \t #### \n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n");
		// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
		//               Operações de Multiplicação
		int ii = 1;
		printf("\n ##### multiplicarTh_t%d de Matrizes #####\n", ii);

		// ### Início do Núcleo	###
		start_time = wtime();
		mat_cPar.matriz = NULL;
		mat_cPar.lin = N;
		mat_cPar.col = N;
		if (malocar(&mat_cPar)) {
			printf ("ERROR: Out of memory\n");
		}

		mzerar(&mat_cPar);
		if ((ntasks > N) || (ntasks == 0)) {
			ntasks = N;
		}

		printf ("\tNúmero de tarefas = %d\n", ntasks);

		start_time = wtime();
		pthread_t *threads = (pthread_t *) malloc(ntasks * sizeof(pthread_t));
		param_t *args = (param_t *) malloc(ntasks * sizeof(param_t));


		for (int i = 0; i < ntasks; i++)
		{
			args[i].tid = i;
			args[i].ntasks = ntasks;
			args[i].N = N;
			args[i].lini = (N/ntasks)*i;

			if (i == (ntasks-1)) {
				if ((N % ntasks) == 0)
				args[i].lfim = (N/ntasks)+args[i].lini;
				else {
					int lin_resto = (int) (N/ntasks) * ntasks;
					//printf ("%d", lin_resto);
					args[i].lfim = (N/ntasks)+args[i].lini+(N-lin_resto);
				}
			} else {
				args[i].lfim = (N/ntasks)+args[i].lini;
			}


			args[i].L = La;
			args[i].M = M;
			args[i].mat_a = &mat_a;
			args[i].mat_b = &mat_b;
			args[i].mat_cPar = &mat_cPar;
			pthread_create(&threads[i], NULL, multiplicarth, (void *) (args+i));
		}

		for (int i = 0; i < ntasks; i++)
		{
			pthread_join(threads[i], NULL);
		}

		end_time = wtime();
		// ### Fim do Núcleo	###

		#ifndef DEBUG
		//mimprimir(&mat_cPar);
		printf("\tRuntime: %f\n", end_time - start_time);
		#endif

		times[contTimes++] = end_time - start_time;
		sprintf(filename, "multth_t0.result");
		fmat = fopen(filename,"w");
		fileout_matriz(&mat_cPar, fmat);
		fclose(fmat);
		// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
	}


	if (!rank){
	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	//               Operações de Multiplicação (OpenMP)

	printf("\n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n \
		#### \t Operações de multiplicação (OpenMP) \t #### \n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n");

		ompMat_mult = (mymatriz *) malloc (sizeof(mymatriz));
		printf("\n ##### multiplicar_omp0 de Matrizes #####\n");
		omp_set_num_threads(ntasks);
		printf ("\tNúmero de tarefas = %i\n", omp_get_max_threads());

		// ### Início do Núcleo	###
		start_time = wtime();
		ompMat_mult = omp_mmultiplicar(&mat_a, &mat_b, ntasks);
		end_time = wtime();
		// ### Fim do Núcleo	###

		#ifndef DEBUG
		printf("\n ##### Matriz C (no main) #####\n");
		//mimprimir((*ompMat_mult));
		printf("\tRuntime: %f\n", end_time - start_time);
		#endif

		times[contTimes++] = end_time - start_time;
		sprintf(filename, "mult_omp0.result");
		fmat = fopen(filename,"w");
		fileout_matriz(ompMat_mult, fmat);
		fclose(fmat);

		// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
	}


	if (!rank){
	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	//               Operações de Multiplicação em bloco OMP
	printf("\n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n \
		#### \t Operações de multiplicação em bloco (OpenMP) \t #### \n \
		%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n");

		mat_cFinalOMP = (mymatriz *) malloc (sizeof(mymatriz));
		printf("\n ##### multiplicar_t0 de Matrizes (bloco OMP) #####\n");
		omp_set_num_threads(ntasks);
		printf ("\tNúmero de tarefas = %i\n", omp_get_max_threads());

		// ### Início do Núcleo	###
		start_time = wtime();
		mat_cFinalOMP = omp_multiplicar_bloco(&mat_a, &mat_b, ntasks);
		end_time = wtime();
		// ### Fim do Núcleo	###

		#ifndef DEBUG
		printf("\n ##### Matriz C (no main) #####\n");
		//mimprimir(mat_cFinalOMP);
		printf("\tRuntime: %f\n", end_time - start_time);
		#endif

		times[contTimes++] = end_time - start_time;
		sprintf(filename, "mult_SeqBlomp0.result");
		fmat = fopen(filename,"w");
		fileout_matriz(mat_cFinalOMP, fmat);
		fclose(fmat);

		// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
	}


	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	//      Operações de Multiplicação em bloco MPI
	// Inicio MPI

	// MULTIPLICAR BLOCO PARALLEL c/ MPI
	if (!rank) {
		printf("\n ##### Multiplicação de Matrizes (bloco MPI) #####\n");
		printf ("\tNúmero de tarefas = %i\n", size);
		start_time = wtime();
		mat_cMPI = mpi_multiplicar(&mat_a, &mat_b, rank, size);
		end_time = wtime();

		//#ifndef DEBUG
		printf("\n ##### Matriz C (no main) #####\n");
		//mimprimir(mat_cMPI);
		printf("\tRuntime: %f\n", end_time - start_time);
		//#endif
		

		times[contTimes++] = end_time - start_time;
		sprintf(filename, "mult_MPI0.result");
		fmat = fopen(filename,"w");
		fileout_matriz(mat_cMPI, fmat);
		fclose(fmat);
		
	} else {
		mat_cMPI = mpi_multiplicar(&mat_a, &mat_b, rank, size);
	}

	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
	
	if (!rank){

		// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
		//              Comparação dos resultados
		printf("\n ##### ##### ##### ##### ##### ##### ##### ##### #####\n");
		printf("\n #####       RELATÓRIO FINAL DAS EXECUÇÕES       #####\n");
		printf("\n ##### ##### ##### ##### ##### ##### ##### ##### #####\n");

		int ctT =0;
		printf("\n ##### Comparação dos resultados da adição de matrizes #####\n");
		printf("\t Tempo de execução 1 : %.4f\n\t[soma_t0 vs soma_t1]\t", times[ctT++]);
		mcomparar (mat_soma[0],mat_soma[1]);
		ctT++;

		printf("\n ##### Comparação dos resultados da Multiplicação de matrizes #####\n");
		for (int i=1; i<tipo_multMat; i++) {
			printf("\t Tempo de execução 1 : %.4f\n\t[mult_t0 vs mult_t%d]\t", times[ctT++], i);
			mcomparar (mat_mult[0],mat_mult[i]);
		}
		ctT++;

		
		printf("\n ##### Comparação dos resultados da Multiplicação de matrizes bloco #####\n");
		printf("\t Tempo de execução 1 : %.4f\n\t[mult_t0 vs mult_SeqBl0]\t", times[ctT++]);
		mcomparar (mat_mult[0],mat_cFinal);
		

		printf("\n ##### Comparação dos resultados da Multiplicação de matrizes (thread) #####\n");
		printf("\t Tempo de execução %d : %.4f\n\t[mult_t0 vs mult_tTh]\t", ntasks, times[ctT++]);
		mcomparar (mat_mult[0],&mat_cPar);


		printf("\n ##### Comparação dos resultados da Multiplicação de matrizes (OMP) #####\n");
		printf("\t Tempo de execução %d : %.4f\n\t[mult_t0 vs mult_tOmp0]\t", ntasks, times[ctT++]);
		mcomparar (mat_mult[0],ompMat_mult);

		printf("\n ##### Comparação dos resultados da Multiplicação de matrizes (blocoOMP) #####\n");

		printf("\t Tempo de execução %d : %.4f\n\t[mult_t0 vs mult_tBlOmp0]\t", ntasks, times[ctT++]);
		mcomparar (mat_mult[0],mat_cFinalOMP);

	#ifdef MPIrun
		if (mat_cMPI != NULL){
			printf("\n ##### Comparação dos resultados da Multiplicação de matrizes (bloco MPI) #####\n");
			printf("\t Tempo de execução %d : %.4f\n\t[mult_t0 vs mult_tMPI0]\t", ntasks, times[ctT++]);
			mcomparar (mat_mult[0],mat_cMPI);
		} else {
			printf("\n ##### Comparação dos resultados da Multiplicação de matrizes (bloco MPI) #####\n");
			printf("\t Não pode ser executado (rank %d)!\t\n\n", rank);
		}

		// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
	}
	#endif

	if (!rank){
		// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
		//                   Liberação de memória
		mliberar(&mat_a);
		mliberar(&mat_b);
		mliberar(&mat_cPar);

		for (int ii=0; ii < 2; ii++) {
			mliberar(mat_soma[ii]);
			free (mat_soma[ii]);
		}
		free(mat_soma);

		for (int ii=0; ii < tipo_multMat; ii++) {
			mliberar(mat_mult[ii]);
			free (mat_mult[ii]);
		}
		free(mat_mult);


		mliberar(mat_cFinal);
		free(mat_cFinal);


		mliberar(ompMat_mult);
		free(ompMat_mult);

		mliberar(mat_cFinalOMP);
		free(mat_cFinalOMP);;

	//#ifdef MPIrun
		mliberar(mat_cMPI);
		free (mat_cMPI);

		// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
	}

	MPI_Finalize();
	//#endif


	return 0;
	
}

