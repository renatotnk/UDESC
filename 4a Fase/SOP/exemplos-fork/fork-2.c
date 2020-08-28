#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
     pid_t f, w;
     int status;
     
     printf("Processo principal (PID=%u)\n", getpid());
     f = fork();
     if (f == 0) {
	  sleep(3);
	  printf("Filho executando \"ls /\"...\n\n");
	  execl("/bin/ls", "/bin/ls", "/naoexiste", (char *)NULL);
	  puts("isto nao eh executado");
     } else {
	  printf("Pai (PID=%u) esperando pelo filho (PID=%u)\n", getpid(), f);
	  w = waitpid(f, &status, 0);
	  printf("\nStatus = %d\n", WEXITSTATUS(status));
     }
     return 0;
}
