#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

// Estrutura para a lista de ofertas
struct oft{
	char codigo[256];
	int qntd;
	int qntdOriginal;
	struct oft * next;
};
typedef struct oft oferta;

struct argsT{
	int i;
	char * nome_arquivo;
};

int main_inserindo = 1;

// Criando mutex para controlar a exclusão mútua
int thread_mudando = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

// Variavel global com o endereço da lista para acesso das threads
oferta * lista_ofertas = NULL;

// Cria um novo nó para a lista
oferta * cria_no(){
	oferta  * new_node;
	new_node = (oferta *) malloc(sizeof(oferta));
	return new_node;
}

// Insere um novo nó no final da lista ou cria um quando a lista estiver vazia
/* Limite de caracteres foi necessário pois strcpy estava causando erros e
   qualquer outra tentativa de somar a quantidade quando um elemento possuia
   o mesmo nome resultava em todos os elementos da lista acabarem com o mesmo
   nome de alguma forma.
*/
void push(oferta ** L, char codigo[256], int qnt){
	// Confere se a lista está vazia ou já possui elementos
  	if((*L) == NULL){
		oferta * novo_no = cria_no();
		(*L) = novo_no;
		strcpy(novo_no->codigo, codigo);
		novo_no->qntd = qnt;
		novo_no->qntdOriginal = qnt; 
		novo_no->next = NULL;
		return ;
	}else{	
    		oferta * novo_no;
		oferta * aux;
	    	aux = (*L);
		// Loop buscando o ultimo elemento da lista
		while(aux->next != NULL){
			if(strcmp(aux->codigo, codigo) == 0){
				aux->qntd += qnt;
				aux->qntdOriginal += qnt;
				return;
			}
			aux = aux->next;
		}
		// Tratando ultimo caso
		if(strcmp(aux->codigo, codigo) == 0){
			aux->qntd += qnt;
			aux->qntdOriginal += qnt;
			return;
		}
		// Inserindo o novo nó
		novo_no = cria_no(); 
		strcpy(novo_no->codigo, codigo);
		novo_no->qntd = qnt;
		novo_no->qntdOriginal = qnt; 
		novo_no-> next = NULL;
		aux->next = novo_no;
		return ;
	}
}

// Loop através da lista com impressão dos elementos
void imprime_lista(oferta * lista){
	while(lista->next != NULL){
		printf("Codigo: %s\tQuantidade: %d\tQuantidade Original: %d\n", lista->codigo, lista->qntd, lista->qntdOriginal);
		lista = lista->next;
	}
	printf("Codigo: %s\tQuantidade: %d\tQuantidade Original: %d\n", lista->codigo, lista->qntd, lista->qntdOriginal);
}

int satisfeito(oferta * lista){
	oferta * aux = lista;
	while(aux != NULL){
		if(aux->qntd > 0){
			return 0;
		}
		aux = aux->next;
	}
	
	return 1;
}

pthread_barrier_t barreira;

void * inicializa_thread(void * argp){
	struct argsT *args = argp;
	int i = args->i + 1;
	char * arq = malloc(sizeof(args->nome_arquivo));
	strcpy(arq, args->nome_arquivo);

	char nome_arq_thread[sizeof(i) + sizeof(arq) + 1];
	sprintf(nome_arq_thread,"%s-%d",arq,i);

	oferta * demanda = NULL;
	FILE * file = fopen(nome_arq_thread, "r");
	// Checando existência do arquivo da thread
	if(file == NULL){
		printf("Arquivo de thread não encontrado!\n");
		exit(-1);
	}
	char line [256];
	while(fgets(line,sizeof(line),file) != NULL){
		// Removendo o \n
		line[strlen(line)-1] = '\0';
		// Dividindo a linha
		char codigo[256];
		int qnt;
		sscanf(line, "%s %d",codigo, &qnt);
		push(&demanda, codigo, qnt);
	}
	fclose(file);

	// Esperando outras threads carregarem
	pthread_barrier_wait(&barreira);

	oferta * aux_demanda = demanda;
	oferta * aux_oferta = lista_ofertas;
	
	int ultima_iteracao = 2;

	// Processamento enquanto a main estiver inserindo dados e depois ainda há uma última 
	// iteração para o caso de algum item inserido por último ainda ser de interesse da thread
	while(ultima_iteracao){
		while(aux_demanda != NULL){
			while(aux_oferta != NULL){
				pthread_mutex_lock(&mutex);
				while(thread_mudando == 1)
			       			pthread_cond_wait(&cond, &mutex);
				thread_mudando = 1;
				if(strcmp(aux_demanda->codigo, aux_oferta->codigo) == 0){
										
					if(aux_demanda->qntd > aux_oferta->qntd){
						aux_demanda->qntd -= aux_oferta->qntd;
						aux_oferta->qntd = 0;
					}else{
						aux_oferta->qntd -= aux_demanda->qntd;
						aux_demanda->qntd = 0;
					}
					
				}
				thread_mudando = 0;
				pthread_cond_signal(&cond);
				pthread_mutex_unlock(&mutex);
				sched_yield();
				aux_oferta = aux_oferta->next;
			}
			aux_demanda = aux_demanda->next;
		}
		if(satisfeito(demanda)){
			break;
		}
		aux_demanda = demanda;
		aux_oferta = lista_ofertas;

		if(!main_inserindo){
			ultima_iteracao--;
		}
	}

	pthread_exit(demanda);
}

int main(int argc, char * argv[]){
	// Informando o usuário caso ele tenha esquecido algum argumento
	if(argc < 3){
		printf("Faltam argumentos.\n");
		printf("Uso: ./pregao nthreads arquivo\n");
		exit(1);
	}

	// Lendo o numero de threads
	int nthr;
	sscanf(argv[1], "%d", &nthr);
	// Lendo o nome do arquivo
	char nome_arquivo[sizeof(argv[2])];
	strcpy(nome_arquivo, argv[2]);
	
	pthread_t threads[nthr];
	long t;
	int rc;
	
	// Informando o usuário caso ele tenha informado algo que não seja um número para nthreads
	if(nthr == 0 && argv[0][0] != '0'){
		printf("Erro, nthreads deve ser um número\n");
		exit(-1);	
	}
	
	// Inicializando barreira
	rc = pthread_barrier_init(&barreira, NULL, nthr);
	if (rc != 0) {
		perror("Erro em pthread_barrier_init()");
		exit(1);
     	}

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	// Criando nthr threads
	for(t=0;t < nthr;t++){
		struct argsT * args = malloc(sizeof(struct argsT));
		args->i = t;
		args->nome_arquivo = malloc(sizeof(nome_arquivo));
		strcpy(args->nome_arquivo, nome_arquivo);
		rc = pthread_create(&threads[t], NULL, inicializa_thread, args);
		if(rc){
			printf("Erro ao criar threads.\n");
			exit(-1);
		}
	}

	sleep(1);

	// Abrindo o arquivo
	FILE * file = fopen(nome_arquivo, "r");
	if(file == NULL){
		printf("Arquivo de ofertas não encontrado!\n");
		exit(-1);
	}
	char line [256];
	while(fgets(line,sizeof(line),file) != NULL){
		// Removendo o \n
		line[strlen(line)-1] = '\0';
		// Dividindo a linha
		char codigo[256];
		int qnt;
		sscanf(line,"%s %d",codigo, &qnt);
		// Checando se a linha é válida para ser inserida na fila
		if(strlen(codigo) > 0 && qnt > 0){
			// Se codigo == # então o programa dorme, senão insere no fim da lista
			if(strcmp(codigo, "#") == 0){
				msleep(qnt);
			}else{
				pthread_mutex_lock(&mutex);
				while(thread_mudando == 1)
			       			pthread_cond_wait(&cond, &mutex);
				thread_mudando = 1;
				push(&lista_ofertas, codigo, qnt);
				thread_mudando = 0;
				pthread_cond_signal(&cond);
				pthread_mutex_unlock(&mutex);	
			}
		}
	}
	fclose(file);
	main_inserindo = 0;

	oferta * retornos[nthr];
	
	// Recuperando os ponteiros de retorno de cada thread
	for (int i = 0; i < nthr; i++){
       		pthread_join(threads[i],(void**)&retornos[i]);
	}

	//Imprimindo portifólios	
	oferta * aux;
	for (int i = 0; i < nthr; i++){
		printf("Thread %d - Portfolio de itens:\n", i+1);
		printf("Item               Quantidade  Demanda\n");
		aux = retornos[i];
		while(aux != NULL){
			printf(fmtport, aux->codigo, (aux->qntdOriginal - aux->qntd), aux->qntdOriginal);
			aux = aux->next;
		}
		printf("\n");
	}

	// Imprimindo saldo
	printf("Saldo de itens:\n");
	printf("Item               Quantidade  Ofertado\n");
	aux = lista_ofertas;
	while(aux != NULL){
		printf(fmtsaldo, aux->codigo, aux->qntd, aux->qntdOriginal);
		aux = aux->next;
	}

	// Free's
	for(int i = 0; i < nthr; i++){
		free(retornos[i]);
	}

	free(lista_ofertas);

	pthread_exit(0);
}







