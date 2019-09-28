#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define NUMCONS 1
#define NUMPROD 1
#define BUFFSIZE 10

pthread_t cons[NUMCONS];
pthread_t prod[NUMPROD];
pthread_mutex_t buffer_mutex;

int buf;

int buf_prod[10] = {10,20,30,40,50,60,70,80,90,100};
int buf_cons[10];

sem_t *sem_free; //empty
sem_t *sem_fill; //full



void *produtor(void *arg) {
	int idx = (int*)(arg);
        int n = 10;
	int count = 0;//conta quantos itens foram produzidos	
	int vfree;
	int vfill;
	printf("PRODUCER %d\n",idx);
	while(1) {
		if (count == BUFFSIZE) break;
		sem_getvalue(sem_free,&vfree);
		printf("[[PROD %d]] SEM_FREE=%d\n",idx,vfree);	
		sem_wait(sem_free);
 		buf = buf_prod[count];
		printf("[PROD %d]] PRODUZI: %d\n",idx,buf);
		count++;
 		sem_post(sem_fill);
		sem_getvalue(sem_fill,&vfill);
 		printf("[[PROD %d]] SEM_FILL=%d\n",idx,vfill);	
	} 
}

void *consumidor(void *arg) {
	int idx;
	idx = (int*)(arg);
	int vfree;
	int vfill;
	int count = 0; //conta quantos itens foram consumidos

	printf("CONSUMER %d\n",idx);
	while(1) {
		if (count == BUFFSIZE) break;
 		sem_getvalue(sem_fill,&vfill);
                printf("[[CONS %d]] SEM_FILL=%d\n",idx,vfill);
		sem_wait(sem_fill);
		buf_cons[count] = buf;
		count++;
		printf("[%d] Consumindo numero %d\n",idx, buf);
		sem_post(sem_free);
                sem_getvalue(sem_free,&vfree);
 		printf("[[CONS %d]] SEM_FREE=%d\n",idx,vfree);
	} 
}

int main(int argc, char **argv) {

    int i;
    int rsf;

    int v_sem_free, v_sem_fill;

    /* 
     int sem_init(sem_t *sem, int pshared, unsigned int value); 
     sem - endereco de uma variavel que referencia um semaforo (sem_t)
     pshared - se for compartilhar entre procesoss (fork) usar 1,
               do contrario usar 0 (linux nao suporta)
     value - valor inicial para o semaforo 
    */

    sem_init(sem_free,0,0);
    sem_init(sem_fill,0,1);

    /*
    	int sem_getvalue(sem_t *sem, int *valp);
	sem - endereco de uma variavel que referencia um semaforo (sem_t)
        valp - endereco de uma variavel inteira para armazenar o 
	       valor do semaforo
    */
    rsf = sem_getvalue(sem_free,&v_sem_free);
    printf("VALOR INICIAL [sem_free]:%d %d\n",v_sem_free,rsf);

    rsf = sem_getvalue(sem_free,&v_sem_fill);
    printf("VALOR INICIAL [sem_free]:%d %d\n",v_sem_free,rsf);

        printf("Criando threads produtoras\n");
        for(i=0; i<NUMPROD; i++) {
                 pthread_create(&(prod[i]), NULL,
                        produtor, (void*)i);
        }

	printf("Criando threads consumidoras\n");
	for(i=0; i<NUMCONS; i++) {
		 pthread_create(&(cons[i]), NULL,
       			consumidor, (void*)i);
	}


        for(i=0; i<NUMPROD; i++) {
                 pthread_join(prod[i], NULL);
        }

        for(i=0; i<NUMCONS; i++) {
                 pthread_join(cons[i], NULL);
        }

	int ii;
	printf("\n\n");
	for (ii=0;ii<10;ii++)
		printf("buf_cons[%d] = %d\n",ii,buf_cons[ii]);

	sem_destroy(sem_fill);
	sem_destroy(sem_free);
}


