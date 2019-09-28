#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* handle_client(void* vsd) {
  int  nBytes;
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i;

  char buffer[1024];
  int sd = (int)vsd;
  printf("connected %d\n",sd);
  recv(sd, buffer, sizeof(buffer),0);
  
  if ((buffer[0])!='G') {
        char resp[100] = "HTTP/1.1 400 MOK\nContent-Type: text/html\n\n\nERRO!!!!!!\n\0";
        //mudanca para aproximar do trabalho
        send(sd,resp,sizeof(resp),0);
        send(sd,buffer,sizeof(buffer),0);
  } else { 
	  //send(sd, "OI\0",3,0);
  	//send(sd, buffer, recv(sd, buffer, sizeof(buffer), 0), 0);
  	char resp[100] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n\n\n\0";
  	char resp2[100] = "<html><head><title>aaa</title></head><body><b>OI BRASIL!!!!!!!<b/></body></html>\n";
	//mudanca para aproximar do trabalho
  	send(sd,resp,sizeof(resp),0);
	send(sd,resp2,sizeof(resp2),0);
	//send(sd,buffer,sizeof(buffer),0);
 	
	printf("recv buffer: %s",buffer);
}
  close(sd);
  printf("fechei conexao %d\n",sd);

  return 0;
}

int main(int argc, char** argv) {
	int sd;
	int port=22222;
	struct sockaddr_in addr;
    pthread_t threads[3];

	if ( argc != 2 )
		printf("usage: %s <portnum>\n...Using default port (%d).\n", argv[0], port);
	else { 
		printf("using port: %s\n",argv[1]);
		port = atoi(argv[1]);
	}

	printf("server start\n");

	sd = socket(PF_INET, SOCK_STREAM, 0);
	/* testar se sd > 0 para saber do sucesso da criacao */

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		printf("error bind");


	if ( listen(sd, 20) != 0 )
		printf("error listen");

        int tc = 0;

	while (1)
	{	
		printf("aguardando cliente...\n");
		
		int nt = pthread_create(&threads[tc++],NULL,handle_client,(void*)client);
		int client = accept(sd, 0, 0);
	}
	return 0;
}

