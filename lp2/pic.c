
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS 10000

double partes[NUM_THREADS];
pthread_barrier_t myBarr;

void *calcula_pi(void *idx) {
    long n = (long)idx;
    double resultado = 0;

    resultado = ((pow(-1,n))/((2*n)+1));

    pthread_barrier_wait(&myBarr);
 
    int i = (int)idx;

    partes[i] = resultado;
    //printf("Sou thread %d e calculei a parte: %lf\n",i,resultado);
    return 0;
} //end testa_primo


int main (int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    double myPi = 0;

    pthread_barrier_init(&myBarr,NULL,NUM_THREADS);

    for(t=0; t<NUM_THREADS; t++){
       // printf("main: criando thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, calcula_pi, (void *)t);
    if (rc){
        printf("ERRO; pthread_create() devolveu o erro %d\n", rc);
        exit(-1);
    }
    }
 
    for(t=0; t<NUM_THREADS; t++){
 	  pthread_join(threads[t], NULL);
    }
 
    for(t=0; t<NUM_THREADS; t++) {
        myPi += partes[t]; 
    }

    myPi = (myPi * 4);

 
    printf("\n\nValor de pi calculado: %lf\n",myPi);

 return 0;
}
