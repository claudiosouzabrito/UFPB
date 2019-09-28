
#include "serial.h"
int main(){
	int serial_port = open("/dev/ttyUSB0", O_RDWR); 
	
 	ConfigSerial inst = ConfigSerial();
 	ConfigSerial inst1 = ConfigSerial(0,0,0,0,0,0,0,0,0,0,0,0,0,0);
 	inst.print();
 	inst1.print();
    //cout << inst.escrever(serial_port) << endl;
 	inst.ler(serial_port);
} 