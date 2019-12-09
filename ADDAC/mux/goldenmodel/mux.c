
#include "mux.h"
int mux(int a, int b, int c){
    int saida;
    FILE *fp;
    fp = fopen("tabela-mux.tv", "a");
 //   fprintf(fp, "entrada1;entrada2;controle;saida\n");
   
    if(c) saida = b;
    else saida = a;
    fprintf(fp, "%d%d%d_%d\n", a, b, c, saida);

    fclose(fp);
    return saida;
}

