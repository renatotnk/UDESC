#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NTHR 3

pthread_barrier_t barreira;

void *func(void *arg)
{
     unsigned long id = (unsigned long) arg;

     printf("thread %lu iniciando\n", id);
     sleep((unsigned int)id + 1);
     printf("thread %lu chegando na barreira\n", id); 
     pthread_barrier_wait(&barreira);
     printf("thread %lu saindo da barreira\n", id);
     pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
     long i;
     int rc;
     pthread_t threads[NTHR];

     rc = pthread_barrier_init(&barreira, NULL, NTHR);
     if (rc != 0) {
	  perror("erro em pthread_barrier_init()");
	  exit(1);
     }
     
     for (i = 0; i < NTHR; i++) {
	  rc = pthread_create(&threads[i], NULL, func, (void *) i);
	  if (rc != 0) {
	       perror("erro em pthread_create()");
	       exit(1);
	  }
     }
     
     for (i = 0; i < NTHR; i++) {
	  rc = pthread_join(threads[i], NULL);
	  if (rc != 0) {
	       perror("erro em pthread_join()");
	       exit(1);
	  }
     }
     
     return 0;
}
