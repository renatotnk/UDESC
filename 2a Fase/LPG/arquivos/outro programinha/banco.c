#include <stdio.h>
 
typedef struct{
	int conta;
	char nome[20];
	char sobrenome[20];
	double saldo;
} Cliente;

int main(void){
FILE *arquivo = NULL;
Cliente e = {0,"","",0.0};
int i;
if(!(arquivo = fopen("dados.dat","wb"))){
	printf("erro ao criar arquivo\n");
	return 1;
}
for(i = 0;i < 100; i++){
	fwrite(&e,(sizeof(Cliente)), 1,arquivo);

	}
	fclose(arquivo);
return 0;
}