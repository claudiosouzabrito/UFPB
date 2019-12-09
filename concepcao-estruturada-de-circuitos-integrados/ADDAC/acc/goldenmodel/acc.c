
#include "acc.h"

int acc(int clka, int clk, int a, int acu){
    int saida;
    FILE *fp;
    fp = fopen("tabela-acc.tv", "a");
//    fprintf(fp, "clockanterior-clock-entrada-acumulado_saida\n");
//    printf("clka = %d, clk = %d\n", clka, clk);
    if(clka == 1 && clk == 0) saida = a;
    else saida = acu;
    fprintf(fp, "%d_%d_%d_%d_%d\n", clk, a, acu, saida);
            
    fclose(fp);
    return saida;
}

