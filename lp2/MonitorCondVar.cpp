#ifdef __APPLE__

#ifndef PTHREAD_BARRIER_H_
#define PTHREAD_BARRIER_H_

#include <pthread.h>
#include <errno.h>

#define PTHREAD_BARRIER_SERIAL_THREAD 1

typedef int pthread_barrierattr_t;
typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int tripCount;
} pthread_barrier_t;

int pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned int count)
{
    if(count == 0)
    {
        errno = EINVAL;
        return -1;
    }
    if(pthread_mutex_init(&barrier->mutex, 0) < 0)
    {
        return -1;
    }
    if(pthread_cond_init(&barrier->cond, 0) < 0)
    {
        pthread_mutex_destroy(&barrier->mutex);
        return -1;
    }
    barrier->tripCount = count;
    barrier->count = 0;

    return 0;
}

int pthread_barrier_destroy(pthread_barrier_t *barrier)
{
    pthread_cond_destroy(&barrier->cond);
    pthread_mutex_destroy(&barrier->mutex);
    return 0;
}

int pthread_barrier_wait(pthread_barrier_t *barrier)
{
    pthread_mutex_lock(&barrier->mutex);
    ++(barrier->count);
    if(barrier->count >= barrier->tripCount)
    {
        barrier->count = 0;
        pthread_cond_broadcast(&barrier->cond);
        pthread_mutex_unlock(&barrier->mutex);
        return 1;
    }
    else
    {
        pthread_cond_wait(&barrier->cond, &(barrier->mutex));
        pthread_mutex_unlock(&barrier->mutex);
        return 0;
    }
}

#endif // PTHREAD_BARRIER_H_
#endif // __APPLE__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <iostream>

#define THREADS 5

class CondVar {
   pthread_barrier_t barr;
   int qtd;
public:
   CondVar(int = 1);
   int barreira();
};

CondVar::CondVar(int i) {
   qtd = i;
   if(pthread_barrier_init(&barr, NULL, THREADS)) {
        printf("Could not create a barrier\n");
        exit(0);
   }  
}

int CondVar::barreira() {
   return pthread_barrier_wait(&barr);
}


CondVar c(5);

//pthread_barrier_t barr;

void* tarefas(void* param) {
	long int p = (long int)param;
	printf("executando funcao tarefas - thread=%d.\n",p);
	int i = 0;
	while (i<100000000) i++;

	int rc = c.barreira();

//    int rc = pthread_barrier_wait(&barr);

        if(rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD) {
          printf("Could not wait on barrier\n");
          exit(-1);
        }

	printf("sou a thread num=%d e passei da barreira.\n",p);

	return (void*) p;
}


int main (int argc, char **argv) {
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;
	pthread_t thread5;

	int rc1, rc2, rc3, rc4, rc5, rm;

	printf("iniciando...\n");
	int t=0;
/*
	if(pthread_barrier_init(&barr, NULL, THREADS)) {
        printf("Could not create a barrier\n");
        return -1;
    }
*/
	rc1 = pthread_create(&thread1,NULL,tarefas,(void *)t++);
	rc2 = pthread_create(&thread2,NULL,tarefas,(void *)t++);
	rc3 = pthread_create(&thread3,NULL,tarefas,(void *)t++);
	rc4 = pthread_create(&thread4,NULL,tarefas,(void *)t++);
	rc5 = pthread_create(&thread5,NULL,tarefas,(void *)t++);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
	pthread_join(thread5, NULL);

	return 0;

}
