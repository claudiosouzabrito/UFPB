#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
void gauss(float matriz[3][4]){
	int i,j,k;
	float m;
	cout << "matriz: " << endl;
	for(i=0; i<3; i++){
		cout << matriz[i][0] << " " << matriz[i][1] << " " << matriz[i][2] << " " << matriz[i][3] << endl;
	}
	for(i = 1; i <= 2; i++){
		for(k = 0; k < i; k++){
		//	cout << matriz[i][k] << "/" << matriz[k][k] << endl;
			m = matriz[i][k]/matriz[k][k];
			for(j = 0; j <= 3; j++){
		//		cout << matriz[i][j] << "-=" << m << "*" << matriz[i-1][j] <<endl;
				matriz[i][j] -= m*matriz[k][j];
			}
		}

	}
	//cout << endl << m << endl << endl;
	cout << "matriz triangular:" << endl;

	for(i=0; i<3; i++){
		cout << matriz[i][0] << " " << matriz[i][1] << " " << matriz[i][2] << " " << matriz[i][3] << endl;
	}
	float x[3]; 
	for(i=2; i>=0 ; i--){
		for(j = 2 - i; j > 0; j-- ){
			matriz[i][3] -= x[i+j]*matriz[i][i+j];
		}
		x[i] = matriz[i][3]/matriz[i][i];
	}
	cout << "x[0] = " << x[0] << " x[1] = " << x[1] << " x[2] = " << x[2] << endl;
}
/*
void pivotamento(float matriz[3][4]){
	int i,j,k,ma;
	float m;
	float it[4];
	for(k = 0; k < 2; k++){
		if(k == 0){
			if(matriz[1][k] > matriz[2][k] && matriz[1][k] > matriz[0][k]){
				for(ma = 0; ma < 4; ma++){
					it[ma] = matriz[0][ma];
					matriz[0][ma] = matriz[1][ma];
					matriz[1][ma] = it[ma];
				}
			}
			if(matriz[2][k] > matriz[1][k] && matriz[2][k] > matriz[0][k]){
				for(ma = 0; ma < 4; ma++){
					it[ma] = matriz[0][ma];
					matriz[0][ma] = matriz[2][ma];
					matriz[2][ma] = it[ma];
				}
			}

		}
		if(k == 1){
			if(matriz[1][k] < matriz[2][k]){
				for(ma = 1; ma < 4; ma++){
					it[ma] = matriz[1][ma];
					matriz[1][ma] = matriz[2][ma];
					matriz[2][ma] = it[ma];
				}
			}
		}
		for(i = 2; i-k > 0; i--){
			m = matriz[i][k]/matriz[k][k];
			for(j = 0; j <= 3; j++){
		//		cout << matriz[i][j] << "-=" << m << "*" << matriz[i-1][j] <<endl;
				matriz[i][j] -= m*matriz[k][j];
			}
		}

	}
	for(i=0; i<3; i++){
		cout << matriz[i][0] << " " << matriz[i][1] << " " << matriz[i][2] << " " << matriz[i][3] << endl;
	}
	float x[3]; 
	for(i=2; i>=0 ; i--){
		for(j = 2 - i; j > 0; j-- ){
			matriz[i][3] -= x[i+j]*matriz[i][i+j];
		}
		x[i] = matriz[i][3]/matriz[i][i];
	}
	cout << x[0] << " " << x[1] << " " << x[2] << endl;
}
*/
void jacobi(float matriz[3][4]){
	float x[3], x2[3] = {0}, x3[3], c[3][3], g[3], soma[3];
	int i,j,k;
	float maiordiferenca, maior, d;

	//MOSTRANDO A MATRIZ ORIGINAL
	cout << "matriz: " << endl; 
	for(i=0; i<3; i++){
		cout << matriz[i][0] << " " << matriz[i][1] << " " << matriz[i][2] << " " << matriz[i][3] << endl;
	}

	//FORMANDO O PRIMEIRO VETOR X, E O VETOR G
	for(i = 0; i < 3; i++){
		x[i] = matriz[i][3]/matriz[i][i];
		g[i] = x[i];
	}
	for(i=0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(i == j) c[i][j] = 0.0;
			else c[i][j] = -1*matriz[i][j]/matriz[i][i];
		}
	}

	//FORMANDO A MATRIX C
	cout << "matriz C" << endl;
	for(i=0; i < 3; i++){
		
		cout << c[i][0] << " " << c[i][1] << " " << c[i][2] << endl;
		
	}

	//DANDO INICIO AS ITERACOES
	while(1){
		for(i = 0; i < 3; i++){
			cout << "x[" << i << "] = " << x[i] << " " << "g[" << i << "] = " << g[i] << endl;
		}


		//ZERANDO O VETOR SOMA A CADA ITERACAO
		for(i=0; i < 3; i++) soma[i] = 0; 

		//FAZENDO O VETOR SOMA
		for(i=0; i < 3; i++){
			for(j=0; j < 3; j++){
				soma[i] += c[i][j]*x[j];
			}
		}

		//PRODUZINDO O VETOR X(2)
		for(i=0; i < 3; i++) x2[i] = soma[i] + g[i];

		//PRODUZINDO O VETOR X(3) = X(2) - X(1) E ADQUIRINDO OS MODULOS
		for(i = 0; i < 3; i++){
			x3[i] = x2[i] - x[i];
			if(x[i] < 0) x[i] = x[i]*-1;
			if(x2[i] < 0) x2[i] = x2[i]*-1;
			if(x3[i] < 0) x3[i] = x3[i]*-1;
		}

		//ADQUIRINDO A MAIOR DIFERENCA ENTRE X(2) E X(1), E O MAIOR VALOR DE X(2), AMBOS EM MODULO
		maior = x2[0];
		maiordiferenca = x3[0];
		for(i = 1; i < 3; i++){
			if(x2[i] > maior) maior = x2[i];
			if(x3[i] > maiordiferenca) maiordiferenca = x3[i];
		}

		//OBTENDO D
		d = maiordiferenca/maior;
		cout << "d = " << d << endl;

		//CONDICAO DE PARADA
		if (d < 0.05){
			cout << "chegamos ao fim" << endl;
			break;
		}
		cout << endl << "proxima iteracao---------" << endl;

		//CASO NAO TENHA CHEGADO AO FIM, VAI PASSAR TODOS OS ELEMENTOS DO VETOR X(2) PARA X(1), E FAZER UMA NOVA ITERACAO
		for(i = 0; i < 3; i++) x[i] = x2[i];
	}
}

int main(){
	float matriz[3][4] = {1.5,5.4,3.3,10,4.2,2.3,4.5,11.7,2.7,5.7,7.8,8.9};
	float matriz2[3][4] = {1.5,5.4,3.3,10,4.2,2.3,4.5,11.7,2.7,5.7,7.8,8.9};
	float matriz3[3][4] = {10,2,3,7,1,5,1,8,2,3,10,6};
	int i;
	/*
	cout << "-----------METODO DE GAUSS---------- " << endl;
	gauss(matriz);
	cout << endl << "---------------------" << endl;
	
	cout << "-----------METODO DE PIVOTAMENTO---------- " << endl;
	pivotamento(matriz2);
	*/
	cout << endl << "---------------------" << endl;
	cout << "-----------METODO DE JACOBI---------- " << endl;
	jacobi(matriz3);
}