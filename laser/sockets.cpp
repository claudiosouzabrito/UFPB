/*
 * ============================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  Simple protocol server implementation
 *
 *        Version:  0.1
 *        Created:  08/02/2017 10:55:44 PM
 *       Compiler:  gcc
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <string>
#include <thread>
using namespace std;

/* Server port  */
#define PORT 4242
#define PORT2 4243

/* Buffer length */
#define LEN 4096
#define SERVER_ADDR "127.0.0.1"

void server(){
    /* Client and Server socket structures */
    struct sockaddr_in client, server;
    int slen;    
    /* File descriptors of client and server */
    int serverfd, clientfd;

    char buffer_in[LEN], buffer_out[LEN];

    //fprintf(stdout, "Starting server\n");
    cout << "Starting server(boca)\n";
    /* Creates a IPv4 socket */
    serverfd = socket(AF_INET, SOCK_STREAM, 0);

    cout << "AF_INET == " << AF_INET << " SOCK_STREAM == " << SOCK_STREAM << endl;

    if(serverfd == -1) {
        perror("Can't create the server(boca) socket:");
        //matar
    }
    //fprintf(stdout, "Server socket created with fd: %d\n", serverfd);
    cout << "server(boca) socket created with fd: " << serverfd << endl;


    /* Defines the server socket properties */
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT2);

    cout << "server.sin_port == " << server.sin_port << endl << "server.sin_family = " << server.sin_family << endl;

    memset(server.sin_zero, 0x0, 8);


    /* Handle the error of the port already in use */
    int yes = 1;
    if(setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("Socket options error:");
        //matar
    }


    /* bind the socket to a port */
    if(bind(serverfd, (struct sockaddr*)&server, sizeof(server)) == -1 ) {
        perror("Socket bind error:");
        //matar
    }


    /* Starts to wait connections from clients */
    if(listen(serverfd, 1) == -1) {
        perror("Listen error:");
        //matar;
    }
   // fprintf(stdout, "Listening on port %d\n", PORT);
  //  cout << "Listening on port " << PORT << endl;

    socklen_t client_len = sizeof(client);
    if ((clientfd=accept(serverfd, (struct sockaddr *) &client, &client_len )) == -1) {
        perror("Accept error:");
        //matar
    }
    cout << "clientfd == " << clientfd << endl;

    /* Copies into buffer our welcome message */
    strcpy(buffer_in, "Hello, client(ouvidos)!\n\0");


    /* Sends the message to the client */
    if (send(clientfd, buffer_in, strlen(buffer_in), 0)) {
        //fprintf(stdout, "Client connected.\nWaiting for client message ...\n");
        //cout << "server connected.\nWaiting for client message ...\n";

        /* Communicates with the client until bye message come */
        while (true) {

            /* Zeroing the buffers */
            memset(buffer_in, 0x0, LEN);
            memset(buffer_out, 0x0, LEN);

            //fprintf(stdout, "Say something to the server: ");
            cout << "Say something to the client(ouvido): ";
            //cin >> buffer_out;

            fgets(buffer_out,LEN, stdin);

            /* Sends the read message to the cliente through the socket */
            send(clientfd, buffer_out, strlen(buffer_out), 0);

            /* Receives an answer from the cliente */
            slen = recv(clientfd, buffer_in, LEN, 0);

            if(strcmp(buffer_in, "fim de conexao") == 0) break;
            // printf("Server answer: %s\n", buffer_in);
            cout << "client(ouvidos) answer: " << buffer_in << endl;

            /* 'bye' message finishes the connection */
        }

    }

    /* Client connection Close */
    close(clientfd);

    /* Close the local socket */
    close(serverfd);

   // printf("Connection closed\n\n");
    cout << "Connection closed\nfim da thread server(boca)\n";

}

/*
 * Main execution of the server program of the simple protocol
 */
int main(void) {
    int aba;
    thread boca(server);
    /*
    while(1){
        aba++;
        aba--;
    }
    */
    
    int port;
    cout << "indique a porta que vc esta interessado\n" << endl;
    cin >> port;
    sleep(5);
    // Server socket 
    struct sockaddr_in server;
    // Client file descriptor for the local socket 
    int sockfd;
    clock_t t = clock();
    int p;
   // string inter;

    int len = sizeof(server);
    int slen;

    // Receive buffer 
    char buffer_in[LEN], vetx[3], vety[3], vetz[3];
    int invetx, invety, invetz;
    // Send buffer 
    char buffer_out[LEN], battery[LEN];


   // fprintf(stdout, "Starting Client ...\n");
    cout << "Starting client(ouvidos)...\n";


    
     //Creates a socket for the client
     
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error on server socket creation:");
        return EXIT_FAILURE;
    }
    //fprintf(stdout, "Client socket created with fd: %d\n", sockfd);
    cout << "client(ouvidos) socket created with fd: "<< sockfd << endl;

    // Defines the connection properties 
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    memset(server.sin_zero, 0x0, 8);


    // Tries to connect to the server 
    if (connect(sockfd, (struct sockaddr*) &server, len) == -1) {
        perror("Can't connect to server(boca)");
        return EXIT_FAILURE;
    }



    // Receives the presentation message from the server 
    if ((slen = recv(sockfd, buffer_in, LEN, 0)) > 0) {
        buffer_in[slen + 1] = '\0';
        //fprintf(stdout, "Server says: %s\n", buffer_in);
        cout << "server(boca) says: " << buffer_in << endl;
    }


    // Commuicate with the server until the exit message come
     
    do {

        // Zeroing buffers 
        memset(buffer_in, 0x0, LEN);
        memset(buffer_out, 0x0, LEN);

        //Receives server message 
        int message_len;
        if((message_len = recv(sockfd, buffer_in, LEN, 0)) > 0) {
             buffer_in[message_len - 1] = '\0';
            // printf("Client says: %s\n", buffer);
             cout << "server(boca) says: "<< buffer_in << endl;
        }

        t = clock() + t;
        //p = t%100;
        t = 100000 - t;
        snprintf(battery, LEN, "%d", t);
        //strcpy(buffer_out,inter);
        if(strcmp(buffer_in, "fim de conexao") == 0) {
            send(sockfd, "fim de conexao", 14, 0);
            break;
            }
       // send(sockfd, buffer_out, LEN, 0);
        // 'bye' message finishes the connection 
        else{
            if( buffer_in[2] == ':' && buffer_in[5] == ':'){
              //  send(sockfd, "if correto\n", LEN, 0);
                vetx[0] = buffer_in[0];
                vetx[1] = buffer_in[1];
                vetx[2] = '\0';
                vety[0] = buffer_in[3];
                vety[1] = buffer_in[4];
                vety[2] = '\0';
                vetz[0] = buffer_in[6];
                vetz[1] = buffer_in[7];
                vetz[2] = '\0';
                strcat(buffer_out, "entendido: ");
                strcat(buffer_out, vetx);
                strcat(buffer_out, " horizontais, ");
                strcat(buffer_out, vety);
                strcat(buffer_out, " verticais, ");
                strcat(buffer_out, vetz);
                strcat(buffer_out, " de altitude, ");
                strcat(buffer_out, battery);
                strcat(buffer_out, " de bateria");
                send(sockfd, buffer_out, LEN, 0);
                
               // cout << buffer_in[0] << endl << buffer_in[1] << endl << buffer_in[2] << endl;
               // cout << buffer_in[3] << endl << buffer_in[4] << endl << buffer_in[5] << endl;
               // cout << buffer_in[6] << endl << buffer_in[7] << endl << buffer_in[8] << endl;
                
            }
            else{
                
              //  cout << buffer_in[0] << endl << buffer_in[1] << endl << buffer_in[2] << endl;
              //  cout << buffer_in[3] << endl << buffer_in[4] << endl << buffer_in[5] << endl;
              //  cout << buffer_in[6] << endl << buffer_in[7] << endl << buffer_in[8] << endl;
                
                send(sockfd, "mensagem invalida\n", LEN, 0);
            } 
        } 
    } while(1);


    // Close the connection whith the server 
    close(sockfd);

    //fprintf(stdout, "\nConnection closed\n\n");
    cout << "\nConnection closed\n\n";

    return EXIT_SUCCESS;



   
}