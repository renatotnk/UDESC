#include <stdio.h>
union numero{
	int a;
	double b;
};
int main(void){
	union numero n;
	n.a = 100;
	printf("n.a = %d\n n.b = %.2lf\n",n.a,n.b);
	n.b = 50.0;
	printf("n.a = %d\n n.b = %.2lf\n",n.a,n.b);
	return 0;
}