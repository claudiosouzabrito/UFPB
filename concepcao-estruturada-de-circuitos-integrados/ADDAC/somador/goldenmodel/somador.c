
#include "somador.h"
void somador(int a, int b, int c, int *s, int *o){
    int d;
    FILE *fp;
    fp = fopen("tabela-somador.tv", "a");
//    fprintf(fp, "entrada1;entrada2;carry_in;carry_out;saida\n");

    d = a+b+c;
    switch (d)
    {
    case 0:
        *s = 0;
        *o = 0;
        fprintf(fp, "%d%d%d_%d%d\n", a, b, c, *o, *s);
        break;
    case 1:
        *s = 1;
        *o = 0;
        fprintf(fp, "%d%d%d_%d%d\n", a, b, c, *o, *s);
        break;
    case 2:
        *s = 0;
        *o = 1;
        fprintf(fp, "%d%d%d_%d%d\n", a, b, c, *o, *s);
        break;
    default:
        *s = 1;
        *o = 1;
        fprintf(fp, "%d%d%d_%d%d\n", a, b, c, *o, *s);
        break;
    }
    
   
    fclose(fp);
    
}

