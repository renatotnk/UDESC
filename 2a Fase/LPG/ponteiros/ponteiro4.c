#include <stdio.h>
int cubo(int n);
int main(void){
int a;
printf("informe um inteiro\n")
scanf("%d",&a);
a = cubo(a);
printf("cubo = %d\n",a);
return 0;
}

int cubo(int n){
	int c;
	c=n*n*n;
	return c;
}