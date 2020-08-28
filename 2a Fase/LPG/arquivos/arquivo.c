#include <stdio.h>
int main(int argc,char *argv[]){
	int conta = 0;
	double saldo = 0;
	char nome[30];
	FILE *arquivo = NULL;
	if(argc != 2){
		printf("informe o nome do arquivo\n");
		return 1;
	}
	arquivo = fopen(argv[1],"w");
	if(!arquivo){
		printf("nao foi possivel criar o arquivo\n");
		return 1;
	}

	printf("informe conta,saldo e nome\n");
	printf("0,EOF para terminar\n");
	scanf("%d%lf%s",&conta,&saldo,nome);
	while(!feof(stdin)){
		fprintf(arquivo,"%d %lf %s\n",conta,saldo,nome);
		printf("?\n");
		scanf("%d%lf%s",&conta,&saldo,nome);
	}
	fclose(arquivo);
	return 0;
}