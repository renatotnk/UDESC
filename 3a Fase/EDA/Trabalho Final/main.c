#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CDJ.h"

void mostra_char(void *x){
	char *p = x; 
	printf("%c\n",*p);
}

int compara_char(char *a,char *b){
  if(*a == *b){
    return 0;
  }else{
  	return -1;
  }
}

int main(){
CDJ principal;
inicializacao(&principal,sizeof(CDJ));
printf("-----Simulador de conjuntos disjuntos-----\n");
int option = 0;
	while((scanf("%d",&option)) != EOF){
		printf("1- Inserir um novo conjunto  \n 2 - Unir dois conjuntos \n 3- Buscar conjunto \n 4 - Mostrar conjuntos \n 5 - 			Destroi conjunto especifico \n 6 - Desaloca Estrutura \n  Ctrl+D - Sair");
		if(option == 1){
			CDJ sub;
			inicializacao(&sub, sizeof(char));
			printf("Digite o 1o elemento (que sera seu representante) caractere do novo conjunto\n(VALIDO APENAS PARA 				CARACTERES)\n");
			char car;
			scanf("%c",&car);
			if(pesquisa_membro(&principal,&car,compara_char) == NULL){
				insereNoFim(&sub,&car);
				insereNoFim(&principal,&sub);
			}else{
				printf("Elemento ja pertence a um conjunto, por favor, tente outro numero\n");
			}
		}
		else if(option == 2){
			printf("Digite o representante do 1o conjunto a ser unido\n");
			char x,y;
			scanf("%c",&x);
			printf("Digite o representante do 2o conjunto a ser unido\n");
			scanf("%c",&y);
			une_conjuntos(&principal,&x,&y,compara_char);				
		}
		else if(option == 3){
			char v;
			printf("Digite o representante do conjunto a ser buscado\n");
			scanf("%c",&v); 	
			if((pesquisa_conj(&principal,&v,compara_char) == NULL){
				printf("Conjunto nao encontrado!\n");
			}else{
				mostra_char((pesquisa_conj(&principal,&v,compara_char)->info));
			}
		}
		else if(option == 4){
			mostra_conjuntos(&principal);				
			if(mostra_conjuntos(&principal) == -1)
			     printf("Erro ao mostrar a lista!\n");
		}	
		else if(option == 5){
			printf("Digite o representante do conjunto a ser destruido\n");
			char e;
			scanf("%c",&e);
			(remove_conjunto(&principal,&e,compara_char));
			if((remove_conjunto(&principal,&e,compara_char)) == -1) {
				printf("Lista Vazia!\n");
			}else if((remove_conjunto(&principal,&e,compara_char)) == 0){
				printf("Conjunto nao encontrado!\n");
			}else{
				printf("Conjunto removido com sucesso!\n");
			}
		}
		else if(option == 6){
			if(desaloca_estrutura(&principal) == -1){
				printf("Erro na destruicao da lista!\n");
			}else{
				desaloca_estrutura(&principal);
			}			
		}else{
		    printf("Opcao invalida!\n");
		}
	}
	return 0;
}

