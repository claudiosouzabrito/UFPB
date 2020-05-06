
#include "somador.h"
void somador(int *a, int *b, int c, int *s, int o){
    FILE *fp;
    fp = fopen("tabela-somador.tv", "a");
//    fprintf(fp, "entrada1;entrada2;carry_in;carry_out;saida\n");
    o = c;
    for(int i = 3; i > -1; i--){
        s[i] = a[i] + b[i] + o;
        switch (s[i]){
        case 0:
            //da uma pirueta ai
            break;
        case 1:
            o = 0;
            break;
        case 2:
            s[i] = 0;
            o = 1;
            break;
        default:
            s[i] = 1;
            o = 1;
            break;
        }
    }
    for(int i = 0; i < 4; i++){
        fprintf( fp, "%d", a[i]);
    }
    fprintf(fp, "_");
    for(int i = 0; i < 4; i++){
        fprintf( fp, "%d", b[i]);
    }
    fprintf(fp, "_");
    fprintf(fp, "%d",c);
    fprintf(fp, "_");
    fprintf(fp, "%d", o);
    fprintf(fp, "_");
    for(int i = 0; i < 4; i++){
        fprintf( fp, "%d", s[i]);
    }
    fprintf(fp, "\n");

    
   
    fclose(fp);
    
}

