#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS 10000

int global_var;

void *PrintHello(void *threadid) {
  int x,y;
  y = 0;
  long tid = (long)threadid;
   printf("Olá! Sou a thread #%ld\n", tid);
   for (x = 0; x < 1000; x++)
   	global_var += 10;
   printf("Thread #%ld definiu global_var para %d\n",tid,global_var);
//   while(y<100000000) y++; 
   return 0;
}
int main (int argc, char *argv[]) {
 pthread_t threads[NUM_THREADS];
 int rc;
 long t;
 
 global_var = 0;

 for(t=0; t<NUM_THREADS; t++) {
  printf("main: criando thread %ld\n", t);
  rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
  if (rc){
   printf("ERRO; pthread_create() devolveu o erro %d\n", rc);
   exit(0);
  }
 }

 printf("main: vou fazer o join\n");
 for(t=0; t<NUM_THREADS; t++){
 pthread_join(threads[t], NULL);
 }

 printf("main: terminando...");
 printf(" e o valor de global_var = %d",global_var);
 return 0;

}

