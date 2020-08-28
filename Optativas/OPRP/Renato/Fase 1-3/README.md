Aluno: Renato Tanaka

Prazado avaliador, por favor dê preferência para a execução da avaliação nas máquinas remotas da disciplina. Para isso, utilize o comando scp como descrito abaixo para copiar o arquivo para as máquinas:

	$ scp ~/local_baixado/Renato.zip ens1:/~/

Após isso, logue na máquina ens1 por ssh e passe o comando unzip para descompactar o arquivo:
	
	oprp@ens1~$ unzip Renato.zip

	As funções implementadas se encontram no arquivo matriz-operacoesv3.c, e são utilizadas no arquivo main_matrizv3.c

	Uso:
		$ make clean
		$ make all

	Após isso, gerar duas matrizes com as dimensões desejadas utilizando o comando:
		$ ./gera_matrizv3 [dimensao_linha][dimensao_coluna]

NOTA: Certifique-se que as matrizes são compatíveis para as operações.

	Em seguida, executar o comando a seguir para executar o programa principal:
		$ mpirun --hostfile [arq_hostfile] -np [n_processos] [mat1_gerada] [mat2_gerada]

	Sendo:
		1. o arquivo arq_hostfile contém as informações das máquinas a serem utilizadas pelo MPI* 
		2. n_processos corresponde ao número de processos a serem inicializados pelo MPI** e também o nro de threads a serem utilizadas pelo OpenMP.
		3. Os dois primeiros argumentos as matrizes a serem operadas

	*Para execuções locais, favor passar o arquivo localhost como parâmetro de [arq_hostfile]. Para execuções na máquina da disciplina, passar aqui o arquivo hostfile_ens
	
	**POR FAVOR, CERTIFIQUE-SE QUE A MÁQUINA A SER EXECUTADA SUPORTA O NRO DE PROCESSOS/THREADS PASSADOS PELO PARÂMETRO.

#### OPCIONALMENTE, OS ARQUIVOS run_100x200_ens.sh e run_1000x1000_ens.sh também podem ser executados para a automatização da avaliação. #### 
	#### PARA EXECUTAR, BASTA DIGITAR #### 
		./run_NxN_ens.sh
	Os scripts irão executar os comandos make clean, make, gera_matrizv3 e mpirun de acordo com a dimensionalidade do nome do arquivo respectivo.
	Os arquivos run_100x200_local.sh e run_1000x1000_local.sh irão realizar a mesma tarefa, porém apenas executando localmente.

### Exemplo Manual ###
oprp@ens1~$ make clean;
oprp@ens1~$ make all;
oprp@ens1~$ ./gera_matrizv3 1000 1000;
oprp@ens1~$ mpirun --hostfile hostfile_ens -np 4 mat1_gerada mat2_gerada
oprp@ens1~$ make clean

Após a execução, é recomendada a execução novamente do comando:
	oprp@ens1~$ make clean

#### Exemplo automático ####
./run_100x200_ens.sh
./run_1000x1000_ens.sh

ou

./run_100x200_local.sh
./run_1000x1000_local.sh


