
#include "acc.h"

int acc(int clka, int clk, int *a, int *acu, int *s){
    int saida;
    FILE *fp;
    fp = fopen("tabela-acc.tv", "a");
//    fprintf(fp, "clockanterior-clock-entrada-acumulado_saida\n");
//    printf("clka = %d, clk = %d\n", clka, clk);
    if(clka == 1 && clk == 0){
        fprintf(fp, "%d" ,clk);
        fprintf(fp, "_");
        for(int i = 0; i < 4; i++){
            fprintf( fp, "%d", a[i]);
        }
        fprintf(fp, "_");
        for(int i = 0; i < 4; i++){
            fprintf( fp, "%d", acu[i]);
        }
        fprintf(fp, "_");
        for(int i = 0; i < 4; i++){
            s[i] = a[i];
            fprintf( fp, "%d", a[i]);
        }
    }
    else{
        fprintf(fp, "%d" ,clk);
        fprintf(fp, "_");
        for(int i = 0; i < 4; i++){
            fprintf( fp, "%d", a[i]);
        }
        fprintf(fp, "_");
        for(int i = 0; i < 4; i++){
            fprintf( fp, "%d", acu[i]);
        }
        fprintf(fp, "_");
        for(int i = 0; i < 4; i++){
            s[i] = acu[i];
            fprintf( fp, "%d", acu[i]);
        }
    }
   fprintf(fp, "\n");
            
    fclose(fp);
    return saida;
}

