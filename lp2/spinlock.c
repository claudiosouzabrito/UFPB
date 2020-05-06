#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 10

int x;
int lock;

//__sync_lock_test_and_set(&lock,1)

void* somaX(void* param) {
	int p = (int)param;
    printf("THREAD #%d -> executando funcao somaX.\n",p);
	while(1) {
		//while(TS(lock)); //protocolo de entrada	
		while(__sync_lock_test_and_set(&lock,1));
		printf("THREAD #%d - lock = %d\n",p,lock);
		if (x >= 10000) pthread_exit(0);
		x += 10;  //secao critica
		printf("THREAD #%d - alterei o valor de x para %d\n",p,x);

		int j;
		//while(j<100000) j++;
		
		lock = 0; //protocolo de saida
	}
}

int main(void) {
	pthread_t threads[NUM_THREADS];
	int rc1;

	x = 0;
	lock = 0;

    long t=0;

	for(t=0; t<NUM_THREADS; t++){
		printf("main: criando thread %ld\n", t);
		rc1 = pthread_create(&threads[t], NULL, somaX, (void *)t);
		if (rc1){
   		  printf("ERRO; pthread_create() devolveu o erro %d\n", rc1);
   		  exit(-1);
  		}
 	}
	
	while(x < 10000);
	return 0;
}
