#include <stdio.h>
#include <stdlib.h>
int main(void){
	int i;
	char c;
	float f;
	double d;
	int v[10] = {0};
	int *p;
	short s;
	printf("int = %lu\n"
		   "char = %lu\n"
		   "float = %lu\n"
		   "double = %lu\n"
		   "v[10] = %lu\n"
		   "p = %lu\n"
		   "s = %lu\n",sizeof(i),sizeof(c),sizeof(f),sizeof(d),sizeof(v),sizeof(p),sizeof(s));
return 0;
}