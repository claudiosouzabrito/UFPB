#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
//__sync_fetch_and_add

#define NUM_THREADS 5

int count = 0;

volatile int arrive[5] = {0,0,0,0,0};
volatile int proceed[5] = {0,0,0,0,0};

void* tarefas(void* param) {
	long pp = (long)param;
	int p = (int)pp;
	printf("%d - executando funcao tarefas - thread=%d.\n",p,p);
	int i = 0;
	
	//while (i<1000000) i++; //TAREFA
	sleep(3+p);
	
	arrive[p] = 1;
	//__sync_fetch_and_add(&count,1);
	
    printf("%d valor de arrive [%d] = %d - alterado por thread %d\n",p,p,arrive[p],p);

	while(proceed[p]==0);  //BLOQUEIO DA BARREIRA
	//while (count < NUM_THREADS)
	//	printf("%d sou a thread num=%d e estou bloqueada na barreira\n",p,p);
	//sleep(p);
	printf("%d sou a thread num=%d e passei da barreira.\n",p,p);

	proceed[p] = 0;

	return (void*) pp;
}

void* coordenador(void* param) {
	printf("[COORDENADOR] inicializando...\n");
	for (int i=0;i<NUM_THREADS;i++) {
		while(arrive[i]==0);
		arrive[i] = 0;
	}
	for (int i=0;i<NUM_THREADS;i++) {
		//__sync_fetch_and_add(&proceed[i],1);
		proceed[i] = 1;
		printf("[COORDENADOR] valor de proceed [%d] = %d - alterado por thread monitor\n",i,proceed[i]);
	}

	return 0;

}

int main (int argc, char **argv) {
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;
	pthread_t thread5;
	pthread_t coord;

	int rc1, rc2, rc3, rc4, rc5, rm;

	printf("iniciando...\n");
	long t=0;

	rm = pthread_create(&coord,NULL,coordenador,NULL);

	rc1 = pthread_create(&thread1,NULL,tarefas,(void *)t++);
	rc2 = pthread_create(&thread2,NULL,tarefas,(void *)t++);
	rc3 = pthread_create(&thread3,NULL,tarefas,(void *)t++);
	rc4 = pthread_create(&thread4,NULL,tarefas,(void *)t++);
	rc5 = pthread_create(&thread5,NULL,tarefas,(void *)t++);

	pthread_join(coord,NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
	pthread_join(thread5, NULL);


	return 0;

}
