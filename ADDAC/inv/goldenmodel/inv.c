
#include "inv.h"
int inv(int a){
    int saida;
    FILE *fp;
    fp = fopen("tabela-inv.tv", "a");
///    fprintf( fp, "entrada_saida\n");
    if(a) saida = 0;
    else saida = 1;
    fprintf( fp, "%d_%d\n", a, saida);
    
    fclose(fp);
    return saida;
}

