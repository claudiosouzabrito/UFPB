
#include "mux.h"
int mux(int *a, int *b, int c, int *s){
    FILE *fp;
    int saida;
    fp = fopen("tabela-mux.tv", "a");
 //   fprintf(fp, "entrada1;entrada2;controle;saida\n");
   
    if(c){
        for(int i = 0; i < 4; i++){
            fprintf( fp, "%d", a[i]);
        }
        fprintf( fp, "_");
        for(int i = 0; i < 4; i++){
            fprintf( fp, "%d", b[i]);
        }
        fprintf( fp, "_");
        fprintf( fp, "%d", c);
        fprintf( fp, "_");
        for(int i = 0; i < 4; i++){
            s[i] = b[i];
            fprintf( fp, "%d", s[i]);
        }
        fprintf( fp, "\n");
    }
    else{
        for(int i = 0; i < 4; i++){
            fprintf( fp, "%d", a[i]);
        }
        fprintf( fp, "_");
        for(int i = 0; i < 4; i++){
            fprintf( fp, "%d", b[i]);
        }
        fprintf( fp, "_");
        fprintf( fp, "%d", c);
        fprintf( fp, "_");
        for(int i = 0; i < 4; i++){
            s[i] = a[i];
            fprintf( fp, "%d", a[i]);
        }
        fprintf( fp, "\n");
    }

    fclose(fp);
    return saida;
}

