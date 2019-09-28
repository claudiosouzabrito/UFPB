#include <stdio.h>
#include "genpat.h"

int cur_vect;
//alocador de espaço p ponteiro, converte de inteiro p string
char  *inttostr(entier)
int entier;
{
	char *str;
	str = (char *) mbkalloc (32 * sizeof (char));
	sprintf (str, "%d", entier);
	return(str);//ponteiro que e um array de char-concatena os caracteres
}

int a = 0, clk = 0, a_inv = 0, signal0 = 0, signal1 = 0, aux = 0, acc = 0, sel0 = 0, sel1 = 0, c_0 = 0, c_4 = 0, clka = 1, s = 0;

// Inversor
int inv(int a){
	return (~a) &0xF;
}

// MUX
int mux21(int d0, int d1, int s){
	if(!s)
		return d0;
	else
		return d1;
}

// Somador
int somador (int a, int b, int c){
	return (a+b+c) & 0xF; //analisa os 4 ultimos bits do numero inteiro
}

// Acumulador
int acumulador(int clk, int d, int clka){
	if( clk == 0 && clka == 1) return d;
	else return acc;
	
}

int cout(int a, int b, int c){//carry out
	if (a+b+c>15){
		return 1;
	}
	else return 0;
}

void adac(int a, int sel0, int sel1){
	printf("Antes::::::::A: %d, sel0: %d, sel1: %d, clk: %d, c_4: %d, s: %d, acc: %d\n", a, sel0, sel1, clk, c_4, signal1, acc);
	int mux0 = mux21(a, inv(a), sel0);
	int soma = somador(mux0, acc, sel0);
	c_4 = cout(mux0, acc, sel0);
	int mux1 = mux21(mux0, soma, sel1);
	s = mux1;
	acc = acumulador(clk, mux1, clka);
	printf("Diferenciado::::::::mux0:%d, soma:%d, mux1:%d, s:%d\n", mux0, soma, mux1, s);
	printf("Depois::::::::A: %d, sel0: %d, sel1: %d, clk: %d, c_4: %d, s: %d, acc: %d\n", a, sel0, sel1, clk, c_4, signal1, acc);
}

main(){

  DEF_GENPAT("adac_sem_atraso");
	DECLAR("sel0", ":2", "B", IN, "","");
	DECLAR("sel1", ":2", "B", IN, "","");
	DECLAR("clk", ":2", "B", IN, "","");

  DECLAR("a", ":2", "B", IN, "3 down to 0","");
//	DECLAR("c_0", ":2", "B", IN, "","");


  

//	DECLAR("acc", ":2", "B", INOUT, "3 down to 0", "");
  
  DECLAR("s", ":2", "B", OUT, "3 down to 0","");
  DECLAR("c_4", ":2", "B", OUT, "","");

  DECLAR("vdd", ":2", "B", IN, "","");
  DECLAR("vss", ":2", "B", IN, "","");
 
	cur_vect = 0;
  LABEL ("copia");
  AFFECT ("0","vdd","0b1");
  AFFECT ("0","vss","0b0");
	
	
	sel0 = 0;
	sel1 = 0;
	acc = 0;
	

		for(a = 0; a < 16; a++){

			for(clk = 0; clk < 2; clk ++){
				adac(a, sel0, sel1);
	//			AFFECT(inttostr(cur_vect), "acc", inttostr(acc));			
				AFFECT (inttostr(cur_vect), "clk", inttostr(clk));
				AFFECT (inttostr(cur_vect), "a", inttostr(a));
	//			AFFECT (inttostr(cur_vect), "adac", inttostr(adac(a, sel0, sel1)));
				AFFECT (inttostr(cur_vect), "sel0", inttostr(sel0));
				AFFECT (inttostr(cur_vect), "sel1", inttostr(sel1));
			

				AFFECT (inttostr(cur_vect), "c_4", inttostr(c_4));
				AFFECT (inttostr(cur_vect), "s", inttostr(s));
		//		acc = acumulador(clk, signal1, acc);

//				printf("A: %d, sel0: %d, sel1: %d, clk: %d, c_4: %d, s: %d\n", a, sel0, sel1, clk, c_4, signal1);
				cur_vect++;
				clka = clk;
			}
		}

	LABEL ("soma");
  AFFECT ("0","vdd","0b1");
  AFFECT ("0","vss","0b0");
	
	
	sel0 = 0;
	sel1 = 1;

		for(a = 0; a < 16; a++){

			for(clk = 0; clk < 2; clk ++){
				adac(a, sel0, sel1);
	//			AFFECT(inttostr(cur_vect), "acc", inttostr(acc));			
				AFFECT (inttostr(cur_vect), "clk", inttostr(clk));
				AFFECT (inttostr(cur_vect), "a", inttostr(a));
	//			AFFECT (inttostr(cur_vect), "adac", inttostr(adac(a, sel0, sel1)));
				AFFECT (inttostr(cur_vect), "sel0", inttostr(sel0));
				AFFECT (inttostr(cur_vect), "sel1", inttostr(sel1));
			

				AFFECT (inttostr(cur_vect), "c_4", inttostr(c_4));
				AFFECT (inttostr(cur_vect), "s", inttostr(s));
		//		acc = acumulador(clk, signal1, acc);

//				printf("A: %d, sel0: %d, sel1: %d, clk: %d, c_4: %d, s: %d\n", a, sel0, sel1, clk, c_4, signal1);
				cur_vect++;
				clka = clk;
			}
		}



	LABEL ("inversao");
  AFFECT ("0","vdd","0b1");
  AFFECT ("0","vss","0b0");
	
	
	sel0 = 1;
	sel1 = 0;

		for(a = 0; a < 16; a++){

			for(clk = 0; clk < 2; clk ++){
				adac(a, sel0, sel1);
	//			AFFECT(inttostr(cur_vect), "acc", inttostr(acc));			
				AFFECT (inttostr(cur_vect), "clk", inttostr(clk));
				AFFECT (inttostr(cur_vect), "a", inttostr(a));
	//			AFFECT (inttostr(cur_vect), "adac", inttostr(adac(a, sel0, sel1)));
				AFFECT (inttostr(cur_vect), "sel0", inttostr(sel0));
				AFFECT (inttostr(cur_vect), "sel1", inttostr(sel1));
			

				AFFECT (inttostr(cur_vect), "c_4", inttostr(c_4));
				AFFECT (inttostr(cur_vect), "s", inttostr(s));
		//		acc = acumulador(clk, signal1, acc);

//				printf("A: %d, sel0: %d, sel1: %d, clk: %d, c_4: %d, s: %d\n", a, sel0, sel1, clk, c_4, signal1);
				cur_vect++;
				clka = clk;
			}
		}

LABEL ("subtracao");
  AFFECT ("0","vdd","0b1");
  AFFECT ("0","vss","0b0");
	
	
	sel0 = 1;
	sel1 = 1;

		for(a = 0; a < 16; a++){

			for(clk = 0; clk < 2; clk ++){
				adac(a, sel0, sel1);
	//			AFFECT(inttostr(cur_vect), "acc", inttostr(acc));			
				AFFECT (inttostr(cur_vect), "clk", inttostr(clk));
				AFFECT (inttostr(cur_vect), "a", inttostr(a));
	//			AFFECT (inttostr(cur_vect), "adac", inttostr(adac(a, sel0, sel1)));
				AFFECT (inttostr(cur_vect), "sel0", inttostr(sel0));
				AFFECT (inttostr(cur_vect), "sel1", inttostr(sel1));
			

				AFFECT (inttostr(cur_vect), "c_4", inttostr(c_4));
				AFFECT (inttostr(cur_vect), "s", inttostr(s));
		//		acc = acumulador(clk, signal1, acc);

//				printf("A: %d, sel0: %d, sel1: %d, clk: %d, c_4: %d, s: %d\n", a, sel0, sel1, clk, c_4, signal1);
				cur_vect++;
				clka = clk;
			}
		}
	
  SAV_GENPAT();

}
