#include <stdio.h>
int main(void){
	int vetor[] = {7,8,10,11};
	int a = 4;
	int i;
	int *p=NULL;
	p = &a;
	printf("*p = %d\n",*p);
	p = vetor;//??????
	for (i=0;i<4;i++){
		printf("vetor[%d] = %d\n",i,vetor[i]);
		printf("p[%d] = %d\n",i,p[i]);
		printf("*(p+%d) = %d\n",i,*(p+i));
		printf("*(vetor+%d) = %d\n",i,*(vetor+i));
	}	
	printf("&vetor = %p\n"
	"vetor = %p\n"
	"&vetor[0] = %p\n",&vetor,vetor,&vetor[0]);
	p++;
	printf("*p = %d\n",*p);
	--p;
	printf("*p = %d\n",*p);


	return 0;
}