#include <stdio.h>
void cubo(int *n);
int main(void){
int a = 0;
printf("informe um inteiro\n");
scanf("%d",&a);
cubo(&a);
printf("cubo = %d\n",a);
return 0;
}

void cubo(int *n){
	*n= *n * *n * *n;
}