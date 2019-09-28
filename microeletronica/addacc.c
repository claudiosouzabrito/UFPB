#include <stdio.h>
#include "genpat.h"
//alocador de espaÃ§o p ponteiro, converte de inteiro p string
char  *inttostr(entier)
int entier;
{
char *str;
str = (char *) mbkalloc (32 * sizeof (char));
sprintf (str, "%d", entier);
return(str);//ponteiro que e um array de char-concatena os caracteres
}
//somador
int Somador (int mux, int acc, int sel0){
    return (mux+acc+sel0) & 0xF; //analisa os 4 ultimos bits do numero inteiro
}
//cout
int cout(int mux, int acc, int sel0){
    if (mux+acc+sel0>15){
        return 1;
    }
    else return 0;
}
//inv
int inv(int a){
    if(a > 1) return 0;
    else return 1;
}
//mux
int mux(int a, int b, int clk){
    if(!clk) return a;
    else return b;
}
//acc
int acc(int ini, int s, int clk, int antclk){
    if(antclk == 0 && clk == 1)return s;
    else ini;
}
//addacc
void addacc(){
    int cur_vect = 0, i,j;
    int a, sel0, sel1, clk , antclk, ini = 0, s = 0, cot, ac, mu0, mu1, suus ;
    int flagclk = 0;
    for(j = 0; j < 4; j++){
        if(j == 0){
            sel0 = 0;
            sel1 = 0;
        }
        if(j == 1){
            sel0 = 1;
            sel1 = 0;
        }
        if(j == 2){
            sel0 = 0;
            sel1 = 1;
        }
        if(j == 3){
            sel0 = 1;
            sel1 = 1;
        }
        for(a = 0; a < 16; a++){
            for(i = 0; i < 4; i++){
                if(i == 0){
                    antclk = 0;
                    clk = 0;
                }
                if(i == 1){
                    antclk = 0;
                    clk = 1;
                }
                if(i == 2){
                    antclk = 1;
                    clk = 1;
                }
                if(i == 3){
                    antclk = 1;
                    clk = 0;
                }
                mu0 = mux(a, inv(a), sel0);
                suus = Somador(mu0, ac, sel0);
                cot = cout(mu0, ac, sel0);
                s = mux(mu0, suus, sel1);
                ac = acc(ini, s, clk, antclk);
                AFFECT (inttostr(cur_vect), "a", inttostr(a));
                AFFECT (inttostr(cur_vect), "acc", inttostr(ac));
                AFFECT (inttostr(cur_vect), "carry_in", inttostr(sel0));
                AFFECT (inttostr(cur_vect), "carry_out", inttostr(cot));
                AFFECT (inttostr(cur_vect), "soma", inttostr(suus));
                AFFECT (inttostr(cur_vect), "saida", inttostr(s));
                cur_vect++;
                printf("sel0 = %d, sel1 = %d, antclk = %d, clk = %d, a = %d\n", sel0, sel1, antclk, clk, a);
                printf(" acc: %d, carry_in:%d, carry_out:%d soma:%d, saida = %d\n\n",ac, sel0, cot, suus, s);
            }
        }
    }
}
main(){
  int cur_vect = 0;
  DEF_GENPAT("addacc");
  DECLAR("a", ":2", "B", IN, "3 down to 0","");
  DECLAR("acc", ":2", "B", IN, "3 down to 0","");
  DECLAR("carry_in", ":2", "B", IN, "","");
  DECLAR("soma", ":2", "B", OUT, "3 down to 0","");
  DECLAR("carry_out", ":2", "B", OUT, "","");
  DECLAR("saida", ":2", "B", OUT, "3 down to 0","");
  DECLAR("vdd", ":2", "B", IN, "","");
  DECLAR("vss", ":2", "B", IN, "","");
  LABEL ("somador");
  AFFECT ("0","vdd","0b1");
  AFFECT ("0","vss","0b0");
  addacc();
  SAV_GENPAT();
}

