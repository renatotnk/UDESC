#include <stdio.h>
#include <stdlib.h>
int main(void){
int a;
a=10;
char c = 'y';
int *p = 0 ;
char *pc = NULL;
int *p2 = NULL;
a = 3;
p = &a; //ENDERECO da memoria de a,nao conteudo
int b = 10;
p2 = &b; //p2= ENDERECO da memoria de b,nao conteudo
a = 5;
*p = 50;// acessa o interior da memória apontada e modifica seu interior
// *== operador de desreferenciamento
*p2 = 21;
printf("%d\n",*p);//entra na memória apontada e imprime seu endereço
printf("%p\n",p)//neste caso,imprime o endereço de memória,não seu conteúdo
printf("%p\n",&p)//imprime o ENDERECO de memória do ponteiro
//p = &c // NÃO FUNCIONA,TIPOS DIFERENTES,C É CHAR E P É INTEIRO
p= &b // NESTE CASO,SE PODE APONTAR PARA B,POIS É DO MESMO TIPO
 




return 0;
}