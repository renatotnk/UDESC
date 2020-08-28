#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int crescente (int ,int );
int decrescente(int , int );
void bubble_sort(int v[],int tam,int(*f)(int,int));
int main(void){
	int v[100]={0};
	int i;
	int op;
	srand(time(NULL));
	for(i=0;i<=100;i++){
		v[i]=rand()%100;
		}
	printf("vetor atual\n");
	for(i=0;i<100;i++){
		printf("%d\t",v[i]);
	}
	printf("\ninforme 1 para ordem crescente ou 2 para ordem decrescente\t");
	scanf("%d",&op);
	if(op == 1){
		bubble_sort(v,100,crescente);
	}else{
		bubble_sort(v,100,decrescente);
	}
	printf("apos ordenar\n");
	for(i=0;i<100;i++){
		printf("%d\t",v[i]);
	}
	return 0;
}

int crescente(int a,int b){
	return a > b;
}
int decrescente(int a,int b){
	return a < b;
}

void bubble_sort(int v[],int tam,int (*f)(int,int))
{
	int i,j;
	int aux;
	for(i=0;i < tam;i++){
		for(j=0;j < tam-1;j++){
			if((*f)(v[j],v[j+1])){
				aux = v[j];
				v[j] = v[j+1];
				v[j+1] = aux;
			}
		}	
	}
}