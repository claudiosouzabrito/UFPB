#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 12

int x;  
int number;
int next;
int turn[10] = {0,0,0,0,0,0,0,0,0,0};

//__sync_fetch_and_add()

void* somaX(void* param) {
	int i = (int)param;
    printf("THREAD #%d - executando funcao secao_critica.\n",i);
	while(1) {
		turn[i] = __sync_fetch_and_add(&number,1); //protocolo de entrada
		printf("%d e %d\n", turn[i],next);
		while (turn[i] != next); //protocolo de entrada
		if (x >= 100) pthread_exit(0); //protocolo de entrada
		x += 10;  //secao critica
		printf("THREAD #%d - alterei o valor de x para %d, fora dasecao critica\n",i,x);
			//sleep(1);
		next++; //protocolo de saida
	}
	return 0;
}

int main(void) {
	pthread_t threads[NUM_THREADS];
	int rc1;

	x = 0;
	number = 0;
	next = 0;
    long t = 0;

    for(t=0; t<NUM_THREADS; t++){
        printf("main: criando thread %ld\n", t);
        rc1 = pthread_create(&threads[t], NULL, somaX, (void *)t);
        if (rc1){
            printf("ERRO; pthread_create() devolveu o erro %d\n", rc1);
            exit(-1);
        }
    }

	while(x<100);
	return 0;
}
