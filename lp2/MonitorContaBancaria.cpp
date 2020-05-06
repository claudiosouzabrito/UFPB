#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

class ContaBancaria {
  double saldo;
  mutex m;

  public: 
  ContaBancaria(double d = 0);
  void somarSaldo(double d = 0);
  double getSaldo();
};

ContaBancaria::ContaBancaria(double d) {
	saldo = d;	
}

void ContaBancaria::somarSaldo(double d) {
	m.lock();
	saldo += d;
	m.unlock();
}

double ContaBancaria::getSaldo() {
	return saldo;
}

int main() {

	ContaBancaria c1(0);

	c1.somarSaldo(2);
	
	thread t1(&ContaBancaria::somarSaldo,&c1,-2);
	thread t2(&ContaBancaria::somarSaldo,&c1,10);
	thread t3(&ContaBancaria::somarSaldo,&c1,30);
	thread t4(&ContaBancaria::somarSaldo,&c1,-20);
/*	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
*/
	
	cout << c1.getSaldo() << endl;
	
	return 0;

}
