/*
 * Produtor-consumidor usando pthreads, mutexes e variaveis de condicao.
 * Adaptado da solucao do Tanenbaum, Sistemas Operacionais Modernos, 3a Ed.
 * 
 * Para compilar: gcc -pthread -o prodcons-ast prodcons-ast.c
 */

#include <stdio.h>
#include <pthread.h>

#define MAX 1000000000                        /* quantos numeros produzir */

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;                   /* usado para sinalizacao */
int buffer = 0;              /* buffer usado entre produtor e consumidor */

void *producer(void *ptr)
{
     int i;
     for (i = 1; i <= MAX; i++) {
	  pthread_mutex_lock(&the_mutex); /* obtem acesso exclusivo ao buffer */
	  while (buffer != 0)
	       pthread_cond_wait(&condp, &the_mutex);
	  buffer = i;                             /* poe item no buffer */
	  printf("\rprod=%d", i);
	  pthread_cond_signal(&condc);             /* acorda consumidor */
	  pthread_mutex_unlock(&the_mutex);  /* libera acesso ao buffer */
     }
     pthread_exit(NULL);
}

void *consumer(void *ptr)
{
     int i;
     for (i = 1; i <= MAX; i++) {
	  pthread_mutex_lock(&the_mutex); /* obtem acesso exclusivo ao buffer */
	  while (buffer == 0)
	       pthread_cond_wait(&condc, &the_mutex);
	  printf("\r\t\tcons=%d", buffer);
	  buffer = 0;                          /* retira item do buffer */
	  pthread_cond_signal(&condp);               /* acorda produtor */
	  pthread_mutex_unlock(&the_mutex);  /* libera acesso ao buffer */
     }
     pthread_exit(NULL);
}

int main(void)
{
     pthread_t pro, con;
     pthread_mutex_init(&the_mutex, NULL);
     pthread_cond_init(&condc, NULL);
     pthread_cond_init(&condp, NULL);
     pthread_create(&con, NULL, consumer, NULL);
     pthread_create(&pro, NULL, producer, NULL);
     pthread_join(pro, NULL);
     pthread_join(con, NULL);
     pthread_cond_destroy(&condc);
     pthread_cond_destroy(&condp);
     pthread_mutex_destroy(&the_mutex);
     return 0;
}
