
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX 2000
pthread_mutex_t a;
pthread_cond_t t1,t2;
int n;

void X(void *argp)
{	
	pthread_mutex_lock(&a);
	n *= 16;
	pthread_mutex_unlock(&a);
	pthread_cond_signal(&t1);
}

void Y(void *argp)
{	
	pthread_cond_wait(&t2,&a);
	pthread_mutex_lock(&a);
	n /= 7;
	pthread_mutex_unlock(&a);
}

void Z(void *argp)
{	
	pthread_cond_wait(&t1,&a);
	pthread_mutex_lock(&a);
	n += 40;
	pthread_mutex_unlock(&a);
	pthread_cond_signal(&t2);
}


int main(void)
{
    pthread_t t1, t2, t3;
    int rc;

    pthread_mutex_init(&a, NULL);
    pthread_cond_init (&t1, NULL);
    pthread_cond_init (&t2, NULL);


    n = 1;
    rc = pthread_create(&t1, NULL, X, NULL);
    rc = pthread_create(&t2, NULL, Y, NULL);
    rc = pthread_create(&t3, NULL, Z, NULL);
    printf("n=%d\n", n);
    pthread_mutex_destroy(&a);
    pthread_cond_destroy(&t1);
    pthread_cond_destroy(&t2);
    return 0;
}
