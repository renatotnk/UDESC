#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int n;

int main(void)
{
     pid_t f, w;
     int status;
     
     n = 7;
     printf("Processo principal (PID=%u)\n", getpid());
     f = fork();
     if (f == 0) {
	  sleep(1); 
	  printf("filho: n=%d\n", n);
	  n = 10;
	  printf("filho: n=%d\n", n);
	  exit(0);
     } else {
	  printf("pai: n=%d\n", n);
	  printf("Pai (PID=%u) esperando pelo filho (PID=%u)\n", getpid(), f);
	  w = waitpid(f, &status, 0);
	  printf("pai: n=%d\n", n);
     }
     return 0;
}
