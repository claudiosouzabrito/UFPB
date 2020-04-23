#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int pesoa 4
int pesob 3
int pesoc 2
int pesod 1
int pesoe 0

int calcula_decimal(int a, int b, int c, int d, int e){
    int resultado=0;
    resultado= (a*pow(2,pesoa))+ (b*pow(2,pesob)) + (c*pow(2,pesoc))+ (d*pow(2,pesod)) + (e*pow(2,pesoe));
    printf("Decimal: %d\n", resultado);
    return resultado;
}

int main(void){
    FILE *arquivo;
    arquivo = fopen("../simulation/modelSim/deco.tv", "w");
    char bits[32]={0};
    int set=0;
    int f=0;
    int a,b,c,d,e;
    for(a=0; a<2; a++){
        for(b=0; b<2; b++){
            for(c=0;c<2; c++){
                for(d=0; d<2; d++){
                    for(e=0; e<2; e++){
                        set = calcula_decimal(a,b,c,d,e);
                        bits[set]=1;
                        fprintf(arquivo, "%d%d%d%d%d_", a, b, c,d,e);
                        for(int i=31; i>=0; i--){
                            f=(int)bits[i];
                            fprintf(arquivo, "%d",f);
                            bits[i]=0;
                        }
                        fprintf(arquivo, "\n");
                    }
                }  
            }
        }
    }
    return 0;
}