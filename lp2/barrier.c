
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//__sync_fetch_and_add

#define THREADS 5

pthread_barrier_t barr;

void* tarefas(void* param) {
	int p = (int)param;
	printf("executando funcao tarefas - thread=%d.\n",p);
	int i = 0;
	while (i<1000000) i++; //TAREFA
	i = 0;

	//if (p==4) sleep(10);

	printf("sou a thread num=%d e terminei minha tarefa\n",p);
    	
    int rc = pthread_barrier_wait(&barr);
    /*
    if(rc != 0 && rc != 1){
        printf("Could not wait on barrier, %d\n", p);
        exit(-1);
    }
    */
    //sleep (p);
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
	if(pthread_barrier_init(&barr, NULL, THREADS)) {
        printf("Could not create a barrier\n");
        return -1;
    }

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
