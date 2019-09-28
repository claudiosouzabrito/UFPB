/*
*
*
PROJETO DE LINGUAGEM DE PROGRAMACAO 2
PROFESSOR: CARLOS EDUARDO COELHO FREIRE BATISTA 
ALUNO: CLAUDIO DE SOUZA BRITO - 20170023696

observacoes: o codigo fonte deve ficar dentro de reqs
	     uso de arquivo grande nao eh recomendado
             
*
*
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
char li[100];
float bytes = 0.0;
int numthreads = 0;
DIR *dir;
struct dirent *lsdir;
struct dirent **namelist;
int lock = 0;

void* thread(void* t){
	char local[100];
	char GET[4] = "GET";
	char get[4];
	int i;
	char saida[100];
	strcpy(local, (char*) t); // recebendo o nome dos arquivos
	printf("thread analizando %s\n", local);
	for(i = 0; i < 5; i++) saida[i] = local[i]; // essa parte serve para a saida do arquivo pular para linha 

	FILE *arq;
	arq = fopen(local, "rb"); // abrindo os arquivos de requerimento
	if(arq == NULL) printf("nao foi possivel abrir o arquivo -> %s", local);

	fread( local, 1, 100, arq); //lendo seu conteudo

	fclose(arq);// fechando arquivo de requerimento

	if(local[0] == 'G' && local[1] == 'E' && local[2] == 'T'); // requerimentos escritos mal feitos nao serao aceitos
	else{
		printf("Requisicao ma feita\n");
		return 0;
	}

	char newlocal[100];
	for( i = 0; i < 100; i++){
		if(local[i] == ' ') break;
	}
	i++;
	for (int j = 0; j < 100; j++) { //criando uma nova string sem os "GET"
    	newlocal[j] = local[i++];
	}

	newlocal[strcspn(newlocal, "\n")] = '\0'; //tirando o \n

	char newnewlocal[100] = "/home/user/20170023696-LP2-ProvaPratica1/files/";
	strcat(newnewlocal,newlocal);

	arq = fopen(newnewlocal, "rb"); //abrindo o arquivo requerido
	if(arq == NULL) printf("nao foi possivel abrir o arquivo -> %s", newnewlocal);

	while(__sync_lock_test_and_set(&lock,1)); //secao critica
	bytes = bytes + fread( newnewlocal, 1, 10000, arq) - 1;	// bytes contados, ATENCAO!!!! SE FOR UM ARQUIVO MUITO GRANDE
	                                                        // O TERCEIRO PARAMETRO TERA QUE SER ALTERADO PARA SUPORTAR
	lock = 0;	//protocolo de saida

	fclose(arq); // fechando arquivo requerido

	char ans[100] = "/home/user/20170023696-LP2-ProvaPratica1/answ/ans-";
	strcat(ans,saida);
	strcat(ans,"ans");

	arq = fopen(ans, "wb"); //abrindo arquivo de resposta
	if(arq == NULL) printf("nao foi possivel abrir o arquivo -> %s", ans);
	fwrite (newnewlocal, sizeof(char), sizeof(newnewlocal), arq); // escrevendo em binario no arquivo resposta  
	fclose(arq);
	return 0;
}

int main(){
	int num;
	int t = 0;
	num = scandir(".", &namelist, 0, alphasort); //enumerando os arquivos no diretorio
	numthreads = num - 4;  //ele le mais do que deveria
	pthread_t threads[numthreads];
	int rc;

	if (num < 0) perror("scandir");
	while(num--) {
		if(num == 3) break; 
        rc = pthread_create(&threads[t++], NULL, thread, (void *)namelist[num]->d_name); // crirando thread
        if (rc){
            printf("ERRO; pthread_create() devolveu o erro %d\n", rc);
            exit(-1);
        }
	}
	for(t = 0; t < numthreads; t++){
		pthread_join(threads[t], NULL);
	} 

	printf("total de %f bytes lidos\n",bytes); //numero de bytes finais lidos
	return 0;
}
