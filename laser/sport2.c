
/*
*
*
*
MODELO BASICO DE COMUNICACAO PELA PORTA SERIAL
Material fonte: https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
*
*
*
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // contem arquivos de controle como 0_RDWR
#include <errno.h> // funcoes de erro
#include <termios.h> // controle do terminal em sistemas POSIX
#include <unistd.h> // write(), read(), close()

// Abrindo porta serial. Mudar de caminho caso necessario
int main(){
	int serial_port = open("/dev/ttyUSB0", O_RDWR | O_NONBLOCK ); //IMPORTANTEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE

	// Criando novo struct termios
	struct termios tty;
	memset(&tty, 0, sizeof tty);


	if (serial_port < 0) {
	    printf("Error while opening device... errno = %d\n",errno);
	    perror("Something went wrong with open()");
	   // exit(1);
	}

	/*
	// Erro caso nao seja possivel ler da porta serial
	if(tcgetattr(serial_port, &tty) != 0) {
	printf("Error %i from tcgetattr: %s\n", errno, strerror(errno)); //IMPORTANTEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
	}
	*/
	tty.c_cflag &= ~PARENB; // Bit de paridade, desabilitado
	tty.c_cflag &= ~CSTOPB; // Bit e parada, desabilitado = 1 bit
	tty.c_cflag |= CS8; // 8 Bits por Byte de transmissao 
	tty.c_cflag &= ~CRTSCTS; // Desabilitando controle de hardware RTS/CTS
	tty.c_cflag |= CREAD | CLOCAL; // Permite a leitura e ignora ctrl

	tty.c_lflag &= ~ICANON; // Desabilitar eco
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
	cfsetispeed(&tty, B9600);
	cfsetospeed(&tty, B9600);

	// Mensagem de erro
	if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
   		printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
	}
	char read_buf [256] = "Hello, world!";


	int num_bytes = write(serial_port, read_buf, sizeof(read_buf)); // Escrevendo na porta serial IMPORTANTEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE

	printf("Read %i bytes. Received message: %s", num_bytes, read_buf);


	/*
	*
	A RESPEITO DA FUNCAO DE LEITURA
	*
	*/
	tty.c_cc[VTIME] = 0;    // Processo eh interrompido na funcao read (linha 80) durante 10 decisegundos
	tty.c_cc[VMIN] = 10000;    // Processo eh interrompido 


	memset(&read_buf, '\0', sizeof(read_buf)); // alocando memoria para o buffer de leitura


	num_bytes = read(serial_port, &read_buf, sizeof(read_buf)); // atencao para o bloqueio configurado anteriormente por VTIME e VMIN IMPORTANTEEEEEEEEEEEEEEEEEEEEEEEEEE

	// Mensagem de erro
	if (num_bytes < 0) {
    	printf("Error reading: %s", strerror(errno));
	}


	printf("Read %i bytes. Received message: %s", num_bytes, read_buf); // Esse exemplo so fuciona caso seja um formato de DATA ASCII


	close(serial_port);
	
	}
