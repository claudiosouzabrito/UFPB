#include "serial2.h"



int main(){
	int serial_port = open("/dev/ttyUSB3", O_RDWR);
    unsigned char buffer[256];
    memset(buffer, NULL, 256);
    DATA1 carro, sensores;
 	ConfigSerial inst = ConfigSerial();
 	ConfigSerial inst1 = ConfigSerial(0,0,0,0,0,0,0,0,0,0,0,0,0,0);
 	
 	inst.print();
 	inst1.print();



 //	cout << "Digite a rotacao do motor: " << endl;
    sensores.rotamoto = 3;
  //  cout << "Digite a rotacao da roda: " << endl;
    sensores.rotaroda = 2;
 //   cout << "Digite o nivel de combustivel: " << endl;
    sensores.fuel = 0.0;
 //   cout << "Digite a temperatura: " << endl;
    sensores.temp = 10000.345;

	//cout << "buffer na main: " << buffer << endl;    
   //inst.escrever(serial_port, buffer, &sensores, sizeof(sensores));
 
 
   inst.ler(serial_port, buffer, &carro, sizeof(carro));

    cout << "Rotacao do motor: " << carro.rotamoto << endl;
  	cout << "Digite a rotacao da roda: " << carro.rotaroda << endl;
  	cout << "Digite o nivel de combustivel: " << carro.fuel << endl;
  	cout << "Digite a temperatura: " << carro.temp << endl;
  	

}
