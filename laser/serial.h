#ifndef SERIAL_H
#define SERIAL_H
#include <stdio.h>
#include <string.h>
#include <fcntl.h> // contem arquivos de controle como 0_RDWR
#include <errno.h> // funcoes de erro
#include <termios.h> // controle do terminal em sistemas POSIX
#include <unistd.h> // write(), read(), close()
#include <iostream>
using namespace std;


class ConfigSerial {
 	private:
 	public:
 		ConfigSerial();
 		ConfigSerial(int Bpari, int Bpara, int Btrans, int contHard, int canon, int eco, int interp, int contsoft,
 		     int Bespec, int intOutput, int newline, int ttdados, int interdec, int interr);
 		void print();
		int escrever(int serial_port);
		int ler(int serial_port);
	//	int desserializacao(char* buffer, int tam);
		
}; 

#endif