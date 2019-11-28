
#include "somador.h"
void somador(int a, int b, int c, int s, int o){
    int d;
    FILE *fp;
    fp = fopen("tabela-somador.tv", "w");
    fprintf(fp, "entrada1;entrada2;carry_in;carry_on;saida\n");
    for( a = 0; a < 2; a++){
        for ( b = 0; b < 2; b++) {
            for( c = 0; c < 2; c++){
                d = a+b+c;
                switch (d)
                {
                case 0:
                    s = 0;
                    o = 0;
                    break;
                case 1:
                    s = 1;
                    o = 0;
                    break;
                case 2:
                    s = 0;
                    o = 1;
                    break;
                default:
                    s = 1;
                    o = 1;
                    break;
                }
                fprintf(fp, "%d%d%d_%d%d\n", a, b, c, o, s);
            }
        }
    }
    fclose(fp);
    
}

