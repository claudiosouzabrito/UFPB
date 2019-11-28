
#include "acc.h"

void acc(int clka, int clk, int a, int acu){
    int saida;
    FILE *fp;
    fp = fopen("tabela-acc.tv", "w");
    fprintf(fp, "clock-anterior;clock;entrada;acumulado;saida\n");
    for(clka = 0; clka < 2; clka++){
        for (clk = 0; clk < 2; clk++) {
            for(a = 0; a < 2; a++){
                for( int acu = 0; acu < 2; acu++){
                    if(clka == 1 && clk == 0) saida = a;
                    else saida = acu;
                    fprintf(fp, "%d%d%d%d_%d\n", clka, clk, a, acu, saida);
                }
            }
        }
    }
    fclose(fp);
}

