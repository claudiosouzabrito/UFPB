
#include "mux.h"
void mux(int a, int b, int c){
    int saida;
    FILE *fp;
    fp = fopen("tabela-mux.tv", "w");
    fprintf(fp, "entrada1;entrada2;controle;saida\n");
    for( a = 0; a < 2; a++){
        for ( b = 0; b < 2; b++) {
            for( c = 0; c < 2; c++){
                if(c) saida = b;
                else saida = a;
                fprintf(fp, "%d%d%d_%d\n", a, b, c, saida);
            }
        }
    }
    fclose(fp);
    
}

