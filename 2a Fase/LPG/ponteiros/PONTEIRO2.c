#include <stdio.h>
int main(void){
int *p = NULL;
int *p2 = NULL;
int a = 10;
//p2 = &p// ERRADOOOO,ponteiro tipo int
p = &a;
int **pp = NULL;// CERTOOOOOO ponteiro para ponteiro de inteiros,tipo int*
*p = 50;//endereco*(9016)= 50
**pp = 50;//endereco do endereco **(9000) = 50








return 0;

}