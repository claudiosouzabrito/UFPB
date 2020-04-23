#include <iostream>
#include <fstream>
using namespace std;
int main(){
	ofstream out;
	out.open("../simulation/modelsim/flopr.tv");
	int reset, resetant = 1, d, saida, clock, clockant = 1, troca, cont = 1;
	for(d = 0; d < 2; d++){
		for(reset = 0; reset < 2; reset++){
			for(clock = 0; clock < 2; clock++){
				if((clock && !clockant) || (reset && !resetant)){
				if (reset) saida = 0;
				else saida = d;
				}
				out << d << "_" << reset << "_" << clock << "_" << saida << endl;
				resetant = reset;
				clockant = clock;
			}
		}

	}
	out.close();
	return 0;
}