#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
     pid_t f, w;
     int status;
     char s[100];
     
     printf("Processo principal (PID=%u)\n", getpid());
     f = fork();
     if (f == 0) {
	  printf("Alo do filho (PID=%u)\n", getpid());
          gets(s);
          printf("Filho encerrando\n");
	  sleep(3);
	  exit(4);
     } else {
	  printf("Pai (PID=%u) esperando pelo filho (PID=%u)\n", getpid(), f);
	  w = waitpid(f, &status, 0);
	  printf("Status = %d\n", WEXITSTATUS(status));
     }
     return 0;
}
