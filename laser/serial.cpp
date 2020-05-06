#include "serial.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h> // contem arquivos de controle como 0_RDWR
#include <errno.h> // funcoes de erro
#include <termios.h> // controle do terminal em sistemas POSIX
#include <unistd.h> // write(), read(), close()
#include <iostream>
using namespace std;


// Criando novo struct termios
struct termios tty;


void ConfigSerial::print(){
	cout << "funcionando\n";
}

ConfigSerial::ConfigSerial(){
	tty.c_cflag &= ~PARENB; // Bit de paridade, desabilitado
	tty.c_cflag &= ~CSTOPB; // Bit e parada, desabilitado = 1 bit
	tty.c_cflag |= CS8; // 8 Bits por Byte de transmissao 
	tty.c_cflag &= ~CRTSCTS; // Desabilitando controle de hardware RTS/CTS
	tty.c_cflag |= CREAD | CLOCAL; // Permite a leitura e ignora ctrl

	tty.c_lflag &= ~ICANON; // Desabilitar modo canonico, recebendo mais de uma linha por vez
	tty.c_lflag &= ~ECHO; // Desabilitado eco
	tty.c_lflag &= ~ECHOE; // Desabilitado eco
	tty.c_lflag &= ~ECHONL; // Desabilitado eco
	tty.c_lflag &= ~ISIG; // Desabilitar interpretacao de INTR, QUIT e SUSP
	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Desabilita o controle via software
	tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Desabilitando bytes especiais (possivel utilidade futura)

	tty.c_oflag &= ~OPOST; // Desabilitar evita a interpretacao de bytes de output (possivel utilidade futura) 
	tty.c_oflag &= ~ONLCR; // Desabilitar evita a conversao de nova linha 
// tty.c_oflag &= ~OXTABS;  (NOT PRESENT ON LINUX)
// tty.c_oflag &= ~ONOEOT;  (NOT PRESENT ON LINUX)

// Taxa de transmissao de dados
	cfsetospeed(&tty, B9600);
	tty.c_cc[VTIME] = 10;    // Processo eh interrompido na funcao read (linha 80) durante 10 decisegundos
	tty.c_cc[VMIN] = 0;    // Processo eh interrompido 
	cout << "construtor padrao funcionando\n";
}

ConfigSerial::ConfigSerial(int Bpari, int Bpara, int Btrans, int contHard, int canon, int eco, int interp, int contsoft,
 		   int Bespec, int intOutput, int newline, int ttdados, int interdec, int interr)
{
	if(!Bpari) 	tty.c_cflag &= ~PARENB; // Bit de paridade, desabilitado
	else tty.c_cflag |= PARENB;  // Sentando bit de paridade 

	if(!Bpara) 	tty.c_cflag &= ~CSTOPB; // Bit e parada, desabilitado = 1 bit
	else tty.c_cflag |= CSTOPB;  // dois bits de parada usados na comunicacao

	switch (Btrans){

   		case 7:
     		tty.c_cflag |= CS7; // 7 Bits por Byte de transmissao 
   		break;

   		case 6:
     		tty.c_cflag |= CS6; // 6 Bits por Byte de transmissao 
   		break;

   		case 5:
     		tty.c_cflag |= CS5; // 5 Bits por Byte de transmissao 
   		break;

   		default:
     		tty.c_cflag |= CS8; // 8 Bits por Byte de transmissao 
	}

	if(!contHard) 	tty.c_cflag &= ~CRTSCTS; // Desabilitando controle de hardware RTS/CTS
	else tty.c_cflag |= CRTSCTS;  // Habilitando controle de hardware

	if(!canon) 	tty.c_lflag &= ~ICANON; // Desabilitar modo canonico, recebendo mais de uma linha por vez
	else tty.c_lflag |= ICANON; // Habilitar modo canonico, recebendo uma linha por vez

	if(!eco){
		tty.c_lflag &= ~ECHO; // Desabilitado eco
		tty.c_lflag &= ~ECHOE; // Desabilitado eco
		tty.c_lflag &= ~ECHONL; // Desabilitado eco
	}
	else{
		tty.c_lflag |= ECHO; // Desabilitado eco
		tty.c_lflag |= ECHOE; // Desabilitado eco
		tty.c_lflag |= ECHONL; // Desabilitado eco
	}

	if(!interp) 	tty.c_lflag &= ~ISIG; // Desabilitar interpretacao de INTR, QUIT e SUSP
	else 	tty.c_lflag |= ISIG; // Habilitar interpretacao de INTR, QUIT e SUSP

	if(!contsoft) 	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Desabilita o controle via software
	else 	tty.c_iflag |= (IXON | IXOFF | IXANY); // Habilita o controle via software

	if(!Bespec) tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Desabilitando bytes especiais (possivel utilidade futura)
	else	tty.c_iflag |= (IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Habilitando bytes especiais (possivel utilidade futura)

	if(!intOutput)	tty.c_oflag &= ~OPOST; // Desabilitar evita a interpretacao de bytes de output (possivel utilidade futura) 
	else	tty.c_oflag |= OPOST; // Habilitar evita a interpretacao de bytes de output (possivel utilidade futura) 

	if(!newline)	tty.c_oflag &= ~ONLCR; // Desabilitar evita a conversao de nova linha 
	else tty.c_oflag |= ONLCR; // Habilitar evita a conversao de nova linha 

	switch (ttdados){

   		case 0:
     		cfsetospeed(&tty, B0); 
   		break;

   		case 50:
     		cfsetospeed(&tty, B50); 
   		break;

   		case 75:
     		cfsetospeed(&tty, B75); 
   		break;

   		case 110:
     		cfsetospeed(&tty, B110); 
   		break;

   		case 134:
     		cfsetospeed(&tty, B134); 
   		break;

   		case 150:
     		cfsetospeed(&tty, B150); 
   		break;

   		case 200:
     		cfsetospeed(&tty, B200); 
   		break;

   		case 300:
     		cfsetospeed(&tty, B300); 
   		break;

   		case 600:
     		cfsetospeed(&tty, B600); 
   		break;

   		case 1200:
     		cfsetospeed(&tty, B1200); 
   		break;

   		case 1800:
     		cfsetospeed(&tty, B1800); 
   		break;

   		case 2400:
     		cfsetospeed(&tty, B2400); 
   		break;

   		case 4800:
     		cfsetospeed(&tty, B4800); 
   		break;

   		case 19200:
     		cfsetospeed(&tty, B19200); 
   		break;

   		case 38400:
     		cfsetospeed(&tty, B38400); 
   		break;

   		case 57600:
     		cfsetospeed(&tty, B57600); 
   		break;

   		case 115200:
     		cfsetospeed(&tty, B115200); 
   		break;

   		case 230400:
     		cfsetospeed(&tty, B230400); 
   		break;

   		case 460800:
     		cfsetospeed(&tty, B460800); 
   		break;
   		

   		default:
			cfsetospeed(&tty, B9600);
	}

	tty.c_cc[VTIME] = interdec;    // Processo eh interrompido na funcao read  durante decisegundos
	tty.c_cc[VMIN] = interr;    // Processo eh interrompido

	cout << "contrutor personalizado funcionando\n";
}
/*
int ConfigSerial::desserializacao(char* buffer, int n){
	int i,j,k;
	int temp = 0, fuel = 0, rota = 0;
	for(i = 0; i <= n; i++){
		if(buffer[i] == 'R' || buffer[i] == 'T' || buffer[i]  == 'F' || buffer[i] == ''){
			for(k = i+1; buffer[i] != 'R' && buffer[i] != 'T' && buffer[i]  != 'F' && buffer[i] != ''; k++){
				for(j = k; j != i; j--){
					if(buffer[i] = 'R'){
						rota += 
					}
			    }
			}
		}
	}
}
*/
int ConfigSerial::escrever(int serial_port){
	char buffer[256]= "++-";
	//cin >> buffer;
	//buffer[strlen(buffer)+1]= '\0';
    cout << buffer << endl;
	//serializacao();
	
	return write(serial_port, buffer, strlen(buffer));
}

int ConfigSerial::ler(int serial_port){
	char buffer[256];
	
	int n = read(serial_port, &buffer, sizeof(buffer));

	for(int i=0; buffer[i] != '\n'; i++){
				
		cout << buffer[i];	
		
	}
	cout<<endl;

//	desserializacao(buffer, n-1);
	return n;
}
