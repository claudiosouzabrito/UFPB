#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_ITENS 10
int p, c, buf;

void* prod(void *param) {
	int a[NUM_ITENS]; // = {1,2,3,4,5,6,7,8,9,0};
	int i;
	for (i=0;i<NUM_ITENS;i++) a[i] = i;

	while (p < NUM_ITENS) {
		//await (p == c)
		
		while (p != c)
		
		buf = a[p];
		printf("buf = a[%d] = %d\n",p,a[p]);
		p++;
	}
	return 0;
}

void* cons(void *param) {
	int b[NUM_ITENS];
	while (c < NUM_ITENS) {
		//await (p > c)
		while (!(p > c)) 

		b[c] = buf;
		printf("b[%d] = buf = %d\n",c,buf);
		c++;
	}
	int i;
	for (i = 0; i < NUM_ITENS; i++)
		printf("b[%d] = %d\n",i,b[i]);
	return 0;
}

int main (int argc, char *argv[]) {
 pthread_t tprod, tcons;
 int rc;
 long t;

 p = 0;
 c = 0; 

 rc = pthread_create(&tprod, NULL, prod, NULL);
 rc = pthread_create(&tcons, NULL, cons, NULL);

 pthread_join(tprod,NULL);
 pthread_join(tcons,NULL);

 
 return 0;

}

