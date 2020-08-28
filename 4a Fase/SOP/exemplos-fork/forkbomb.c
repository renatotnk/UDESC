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
     while (1) {
        f = fork();
        sleep(10);
     }
     return 0;
}
