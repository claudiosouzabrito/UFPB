#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
struct sockaddr_in destino;
int conexao;
int e_socket;
main(){
   e_socket = socket(AF_INET,SOCK_STREAM,0);
   if(e_socket < 0)
   {
       perror("ERRO !");
exit(1); }
   destino.sin_family = AF_INET;
   destino.sin_port = htons(22222);
   destino.sin_addr.s_addr = inet_addr("127.0.0.1");
   //bzero(&(destino.sin_zero),8);
   conexao = connect(e_socket,(struct sockaddr * )&destino,sizeof(destino));
   if(conexao < 0) {
       perror("Porta fechada! \n");
       close(e_socket);
       exit(1);
   }
   printf("A PORTA 22222 ESTA ABERTA (RECEBENDO CONEXOES TCP) !\n");
   close(e_socket);
}
