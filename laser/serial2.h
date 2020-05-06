#ifndef SERIAL2_H
#define SERIAL2_H
#include <stdio.h>
#include <string.h>
#include <fcntl.h> // contem arquivos de controle como 0_RDWR
#include <errno.h> // funcoes de erro
#include <termios.h> // controle do terminal em sistemas POSIX
#include <unistd.h> // write(), read(), close()
#include <iostream>

using namespace std;

typedef struct DATA1{
    int rotaroda, rotamoto;
    float fuel, temp;

}DATA1;

class ConfigSerial {
 	private:
 	public:
 		ConfigSerial();
 		ConfigSerial(int Bpari, int Bpara, int Btrans, int contHard, int canon, int eco, int interp, int contsoft,
 		     int Bespec, int intOutput, int newline, int ttdados, int interdec, int interr);
 		void print();
		int escrever(int serial_port, unsigned char* buffer, DATA1* sensores, int tam);
		int ler(int serial_port, unsigned char* buffer, DATA1* sensores,  int tam);
		void serializacao(unsigned char* buffer, DATA1* sensores, int tam);
		void desserializacao(unsigned char* buffer, DATA1* sensores, int tam);

};

#endif
