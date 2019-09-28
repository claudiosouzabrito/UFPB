/*
*
*
PROJETO 2 DE LINGUAGEM DE PROGRAMACAO 2
PROFESSOR: CARLOS EDUARDO COELHO FREIRE BATISTA 
ALUNO: CLAUDIO DE SOUZA BRITO - 20170023696
*
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <iostream>
#include <semaphore.h> 
#include <ctime>
using namespace std;
#define SERVER_ADDR "127.0.0.1"
#define SERVERNAME "Server: cloudne/2.2.14 (Win64)\n" // NOME DO MEU SERVIDOR
#define LEN 4096



sem_t mutex; //SEMAFORO EM RELACAO A ESCRITA NO LOG.TXT
sem_t mutex1; // SEMAFORO EM RELACAO AS RESPOSTAS DE SOLICITACAO
DIR *dir;
struct dirent *lsdir;
struct dirent **namelist;


void* cliente(void* vsd) {
  int  nBytes;
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i = 5;
  int sockfd;
  char buffer[1024], arqalvo[1024], tipo[1024];
  char name[2000];
  strcpy(name, (char*)vsd);
  int len = sizeof(serverAddr);
  int flag = 0;
  time_t tt; 
  struct tm * ti; 

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { //CRIANDO UM SOCKET
        perror("Error on server socket creation:");
    }

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(22222);
  serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
  memset(serverAddr.sin_zero, 0x0, 8);

  if (connect(sockfd, (struct sockaddr*) &serverAddr, len) == -1) {//CONECTANDO
        perror("Can't connect to server(boca)");
   }
 
  FILE *arq, *arq1;
  ////////////////////////////////////////////////////////////////TRATAMENTO DAS REQUISICOES
  arq = fopen(name, "r");
  int cont = 1;
  
  while ((fgets(buffer, sizeof(buffer), arq))!=NULL){
    
    if(cont == 1){
      if(buffer[0] == 'G' && buffer[1] == 'E' && buffer[2] == 'T'){ //CASO O GET ESTEJA CORRETO
        while(buffer[i] != ' ') i++;
        memcpy(arqalvo, &buffer[5], i-5);  //GUARDANDO O NOME DO ARQUIVO
      }
      else flag = 1; ///////////////////////////////////////////CASO NAO ESTEJA
    }
    i = 8;
    if(cont == 3){
      while(buffer[i] != '*') i++;
      memcpy(tipo, &buffer[8], i-8); //GUARDANDO O TIPODO ARQUIVO
    }
    cont++;
    if(cont == 4) break;
  }
  fclose(arq);

  if(flag){ /////////////////////////////////////////////RESPOSTA DE SOLICITACAO CASO HAJA BAD REQUEST
    sem_wait(&mutex1);//SEMAFORO
    send(sockfd, "HTTP/1.1 400 Bad Request\n", LEN, 0);
    time (&tt); 
    ti = localtime(&tt);
    send(sockfd, "Date: ", LEN, 0);
    send(sockfd, asctime(ti), LEN, 0);
    send(sockfd, SERVERNAME, LEN, 0);
    send(sockfd, "Content-Length: erro\n", LEN, 0);
    send(sockfd, "Content-Type: ", LEN, 0);
    send(sockfd, tipo, LEN, 0);
    send(sockfd, "; charset=iso-8859-1\n", LEN, 0);
    send(sockfd, "Connection: Closed\n", LEN, 0);
    sem_post(&mutex1); //SEMAFORO
    close(sockfd);
    return 0;
  }
  char newnewlocal[100] = "/home/user/20170023696_claudio-de-souza-brito-LP2-Trabalho2/files/";
  strcat(newnewlocal,arqalvo);
  arq = fopen(newnewlocal, "rb"); 
  if(arq == NULL){////////////////////////////////////////////CASO O ARQUIVO NA SEJA ENCONTRA ERRO 404
    sem_wait(&mutex1);//SEMAFORO
    send(sockfd, "HTTP/1.1 404 Not Found\n", LEN, 0);
    time (&tt); 
    ti = localtime(&tt);
    send(sockfd, "Date: ", LEN, 0);
    send(sockfd, asctime(ti), LEN, 0);
    send(sockfd, SERVERNAME, LEN, 0);
    send(sockfd, "Content-Length: erro\n", LEN, 0);
    send(sockfd, "Content-Type: ", LEN, 0);
    send(sockfd, tipo, LEN, 0);
    send(sockfd, "; charset=iso-8859-1\n", LEN, 0);
    send(sockfd, "Connection: Closed\n", LEN, 0);
    sem_post(&mutex1); //SEMAFORO
    close(sockfd);
    return 0;
  }
  int tamanho = fread(newnewlocal, 1, 7181, arq); //TAMANHO DO ARQUIVO EM BYTES, LIMITE MUITO PEQUENO, PERIGO DE SEGMENTATION FAULT
  fclose(arq);
  sem_wait(&mutex1);// SEMAFORO
  send(sockfd, "HTTP/1.1 200 OK\n", LEN, 0); // RESPOSTA GERADA CASO ACONTECA SUCESSO
  time (&tt); 
  ti = localtime(&tt);
  send(sockfd, "Date: ", LEN, 0);
  send(sockfd, asctime(ti), LEN, 0);
  send(sockfd, SERVERNAME, LEN, 0);
  send(sockfd, "Content-Length: ", LEN, 0);
  send(sockfd, tamanho, LEN, 0); //////////////////NAO EH POSSIVEL PASSAR INTEIRO POR SOCKETS, SOLUCAO NAO ENCONTRADA
  send(sockfd, "\n", LEN, 0);
  send(sockfd, "Content-Type: ", LEN, 0);
  send(sockfd, tipo, LEN, 0);
  send(sockfd, "; charset=iso-8859-1\n", LEN, 0);
  send(sockfd, "Connection: Closed\n", LEN, 0);
  sem_post(&mutex1); //SEMAFORO
  close(sockfd);


  arq = fopen(name, "rb"); // abrindo os arquivos de requerimento
  if(arq == NULL) printf("nao foi possivel abrir o arquivo -> %s\n", name);
  fread( name, 1, 2000, arq);
  fclose(arq);
  arq = fopen("/home/user/20170023696_claudio-de-souza-brito-LP2-Trabalho2/log.txt","a");
  if(arq == NULL) printf("nao foi possivel abrir o arquivo -> log\n");

  sem_wait(&mutex); //SEMAFORO
  fprintf(arq, name); // ESCREVENDO TODAS AS REQUISICOES NO LOG.TXT
  sem_post(&mutex); //SEMAFORO


  fclose(arq);

  close(sockfd); // FECHANDO SOCKET

  return 0;
}

int main(int argc, char** argv) {
  sem_init(&mutex, 0, 1); // CRIACAO DSO SEMAFOROS
  sem_init(&mutex1, 0, 1);
	int sd;
	int port=22222;
	struct sockaddr_in addr;
  int num = scandir(".", &namelist, 0, alphasort); //enumerando os arquivos no diretorio
  printf("num = %d\n", num);
 	if (num < 0) perror("scandir");
	int numthreads = num - 4;  //ele le mais do que deveria
	pthread_t threads[numthreads];
  char buffer_in[LEN] = "\0";
  int client;

	printf("server start\n");

	sd = socket(PF_INET, SOCK_STREAM, 0); // CRIANDO SOCKET

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		printf("error bind");


	if ( listen(sd, 20) != 0 )
		printf("error listen");

  int tc = 0;

  
	while (num--){

		if (num == 3) break;

		int nt = pthread_create(&threads[tc++],NULL,cliente,(void *)namelist[num]->d_name); //CHAMANDO AS THREADS E MANDANDO O NOME DO ARUIVO DE CADA
		socklen_t client_len = sizeof(addr);
    client = accept(sd, (struct sockaddr *) &addr, &client_len); // ESPERA O CLIENTE PRA CONECTAR-SE
	}
  
  
	for(tc = 0; tc < numthreads; tc++){
		pthread_join(threads[tc], NULL);
	} 
  
  sem_destroy(&mutex); //DESTRUIND OS SEMAFOROS
  sem_destroy(&mutex1); 

	return 0;
}

