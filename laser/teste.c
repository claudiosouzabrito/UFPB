#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
		int rotacaomoto;
		int rotaroda;
		float tempmoto;
		float combustivel;
		
	} estrutura; 

void serializar(void *estrutura, int tam, char *buffer){
	memcpy(buffer, estrutura, tam);
} 

void desserializar(char *buffer, int tam, void* estrutura){
	memcpy(estrutura, buffer, tam);
}

int main(){
	estrutura est1;
	est1.rotacaomoto = 2;
	est1.rotaroda = 1;
	est1.tempmoto = 3.44;
	est1.combustivel = 2.5;
	char buffer[16];
	serializar(&est1, sizeof(est1), buffer);
	//AQUI EU VOU TRANSMITIR O BUFFER
	estrutura est2;
	//CHEGOU A MENSAGEM
	desserializar(buffer, sizeof(est2), &est2);
	printf("%d\n", est2.rotacaomoto + 1);

	return 0;

}