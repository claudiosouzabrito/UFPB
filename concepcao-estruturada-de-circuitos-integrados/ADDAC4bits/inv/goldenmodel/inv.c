
#include "inv.h"
void inv(int *a, int *saida){
    FILE *fp;
    fp = fopen("tabela-inv.tv", "a");
///    fprintf( fp, "entrada_saida\n");
    for(int i = 0; i < 4; i++){
        if(a[i]) saida[i] = 0;
        else saida[i] = 1;
    }
    for(int i = 0; i < 4; i++){
        fprintf( fp, "%d", a[i]);
    }
    fprintf( fp, "_");
    for(int i = 0; i < 4; i++){
        fprintf( fp, "%d", saida[i]);
    }
    fprintf( fp, "\n");
    fclose(fp);
}

