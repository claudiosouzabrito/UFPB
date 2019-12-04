
#include "acc.h"

void acc(int clka, int clk, int a, int acu){
    int saida;
    FILE *fp;
    fp = fopen("tabela-acc.tv", "w");
    fprintf(fp, "clock;entrada;acumulado;saida\n");
        for (clk = 0; clk < 2; clk++) {
            for(a = 0; a < 2; a++){
                for( int acu = 0; acu < 2; acu++){
                    if(clk == 0) saida = a;
                    else saida = acu;
                    fprintf(fp, "%d_%d_%d_%d\n",clk, a, acu, saida);
                }
            }
        }
    
    fclose(fp);
}

