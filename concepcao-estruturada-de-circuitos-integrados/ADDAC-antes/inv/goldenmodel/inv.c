
#include "inv.h"
void inv(int a){
    int saida;
    FILE *fp;
    fp = fopen("tabela-inv.tv", "w");
    fprintf( fp, "entrada;saida\n");
    for(a = 0; a < 2; a++){
        if(a) saida = 0;
        else saida = 1;
        fprintf( fp, "%d_%d\n", a, saida);
    }
    fclose(fp);
    
}

