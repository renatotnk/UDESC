#include<unistd.h>

int main(){
	char ola[] = "Ola Mundo\n";

	write(STDOUT_FILENO, ola, 10);
	return 0;
}
