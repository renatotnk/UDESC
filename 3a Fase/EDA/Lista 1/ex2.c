#include <stdio.h>
#include <stdlib.h>

void le_vetor(int *p, int k);
void mostra_vetor(int *p, int k);
int eh_maior(int x, int y);
int eh_menor(int x, int y);
int *gera_vetor(int *p, int k,int *cont,int (*comp)(int,int));

int main(){
int n,cont_n,cont_p;
printf("digite o numero de elementos do vetor\n");
scanf("%d",&n);
int *v = malloc(sizeof(int)*n);
le_vetor(v,n);
int *vn = gera_vetor(v,n,&cont_n,eh_menor);
int *vp = gera_vetor(v,n,&cont_p,eh_maior);
mostra_vetor(vn,cont_n);
mostra_vetor(vp,cont_p);

free(v);
free(vn);
free(vp);

}

void le_vetor(int *p, int k){
int i;
	for(i = 0; i < k ;i++){
		printf("preencha o vetor de %d posicoes\n",k);
		scanf("%d",&p[i]);
	}		
}

void mostra_vetor(int *p, int k){
int i;
	for(i = 0;i < k;i++){
		printf("%d:%d\n",i,p[i]);
	}
}

int eh_maior(int x, int y){
	return x>y;
}

int eh_menor(int x, int y){
	return x<y;
}

int *gera_vetor(int *p, int k,int *cont,int (*comp)(int,int) ){
*cont = 0;
int i,j;
	for(i = 0;i < k; i++){
		if(comp(p[i],0)){
			(*cont)++;
		}
	}
	int *p2 = malloc(sizeof(int)* *cont);
	for(i = 0;i < k; i++){
		if(comp(p[i],0)){
			p2[j] = p[i];
		}
	j++;
	}
	
	return p2;
}

