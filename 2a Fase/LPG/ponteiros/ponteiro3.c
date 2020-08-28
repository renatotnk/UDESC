#include <stdio.h>
int main(void){
int a ;
int *p = NULL;
p=&a;
scanf("%d",p);//&a
printf("%d\n",*p);



	return 0;
}