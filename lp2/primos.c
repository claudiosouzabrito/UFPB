#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *testa_primo(void *threadid) {
 long tid = (long)threadid;

 int num_inicio = (int)(tid * 1);
 int num_fim = num_inicio + 999;
 printf("sou thread #%ld e vou testar de %d a %d\n",tid,num_inicio,num_fim);
 
 int num_corrente = 0;

 for (num_corrente = num_fim; num_corrente >= num_inicio; num_corrente--) {
     //printf("#%ld testando %d\n",tid,num_corrente);
     if ((num_corrente % 2) != 0) {
		int j = 0;
		int not_primo = 0;
		if (num_corrente <=3) break;

		for (j = 3; j < num_corrente; j++) {
			if (num_corrente % j == 0) {
				not_primo = 1;
				//	printf("#%ld Numero %d nao eh primo (%d)\n",tid,num_corrente,j);
			}
			if (not_primo == 1) break;

		}//for (j = 3...
		if (not_primo == 0) 
			printf("#%ld Numero %d eh primo\n",tid,num_corrente);

     	}//if (num_corrente %2 


 } // for (num_corrente = num_fim...

 return 0;
} //end testa_primo


int main (int argc, char *argv[]) {
 pthread_t threads[NUM_THREADS];
 int rc;
 long t;

 for(t=0; t<NUM_THREADS; t++){
  printf("main: criando thread %ld\n", t);
  rc = pthread_create(&threads[t], NULL, testa_primo, (void *)t);
  if (rc){
   printf("ERRO; pthread_create() devolveu o erro %d\n", rc);
   exit(-1);
  }
 }
 
 for(t=0; t<NUM_THREADS; t++){
 	pthread_join(threads[t], NULL);
 }
 return 0;
}
