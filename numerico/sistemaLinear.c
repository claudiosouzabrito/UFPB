/* Resolução de Sistemas Lineares com técnicas de cálculo Numérico */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int *system_def(void){
    int i;
    puts(" ");
    for(i=0;i<=2;i++){
        if(i!=1)
        puts("*************************************************");
        else
        puts("**** Programa de Resolucao de Sistema Linear ****");  
    }
    printf("\n Qual a dimensao do sistema? ");
    char s_dimensao [4];
    scanf("%s", s_dimensao);

    int dimensao = strlen(s_dimensao); 
    char *token = strtok(s_dimensao, "x");
    int linha, coluna, aux=0;

    while(token != NULL) {
        if(aux==0){
            linha = atoi(token);   // conversão de string para inteiro
            //printf("linha= %d\n", linha);
        }
        else{
            coluna = atoi(token);
            //printf("coluna= %d\n", coluna);
        }
        ++aux;
        token = strtok(NULL, "x");
    }
    int *infos;
    infos = (int*) calloc (2, sizeof(int));
    infos[0]=linha;
    infos[1]=++coluna;
    return infos;
}

float **aloca_matriz(int *infos){
    float **matriz =(float**)malloc(sizeof (float*)*infos[0]);
    puts(" ");
    for(int i=0;i<infos[0];i++){
        matriz[i]=(float*)malloc(sizeof(float*)*infos[1]);
        printf("****** Preenchimento da Linha (%d) ******\n", i+1);
        for(int j=0;j<infos[1];j++){
            if(j==infos[1]-1){
                printf("Digite o Termo independete: ");
                scanf("%f", &matriz[i][j]);
            }
            else{
                printf("Digite o Coefinciente %d: ", j+1);
                scanf("%f", &matriz[i][j]);
            }
        }
        printf("\nDigite o termo independente:");
        puts(" ");
    }
    return matriz;
}

void print_matriz(float **matriz, int *infos){
    puts("***************************************");
    for(int i=0;i<infos[0];i++){
        for(int j=0; j<infos[1]; j++){
            if(j==0)
                printf("|  %.2f  ", matriz[i][j]);
            else if ((j==infos[1]-2)| (j==infos[1]-1) )
                printf("  %.2f  |", matriz[i][j]);
            else
                printf("  %.2f  ", matriz[i][j]);
        }
        puts(" ");
    }
    puts("**************************************");
}

int gauss(float **matriz, int *infos){
    float pivo;
    int linha_ref=0, aux=0, flag=-1;
    float result[infos[0]]={0};
    
    for(int t=0; t<(infos[0]);t++){//for so roda 2 vezes em 3x3

        if(t+2==infos[0]+1){//Mudanca de coluna
            ++aux;
           
            printf("LINHA %d com LINHA %d\n", infos[0], infos[0]-1);
            printf("Calculo do Pivo: divisao de %.2f por %.2f\n\n", matriz[infos[0]-1][aux], matriz[infos[0]-2][aux]);//divide 3/2
            if((matriz[infos[0]-1][1]==0)&(matriz[infos[0]-2][1]==0))
                pivo = 0.0;
            else{
                pivo = matriz[infos[0]-1][1]/matriz[infos[0]-2][1];
            }
            printf("Pivo = %.2f\n", pivo);
            for(int j=0;j<=infos[1];j++)
                matriz[infos[0]-1][j]-=pivo*matriz[infos[0]-2][j];

            printf("\nREALIZANDO OP NA LINHA %d com LINHA %d\n", t+1, t);
        }
        else{
            printf("LINHA %d com LINHA %d\n", t+2, 1);
            printf("Calculo do Pivo: divisao de %.2f por %.2f\n", matriz[t+1][aux], matriz[0][aux]);
            pivo = matriz[t+1][0]/matriz[0][0];
            printf("Pivo = %.2f\n", pivo);
            for(int j=0;j<=infos[1];j++)
                matriz[t+1][j]-=pivo*matriz[0][j];
            printf("\nREALIZANDO OP NA LINH1A %d\n", t+2);
        }
        puts("Estado atual da Matriz:");
        print_matriz(matriz, infos);
    }
    flag=10;
    if(flag>0){ //solucao por retroatividade
        for(int i= infos[0]-1; i>=0; i--){
            //printf("I = %d\n",i );
            if(i==infos[0]-1){
                //printf("matriz[i][infos[1]] = %.2f -- /matriz[i][infos[1]-1]: %.2f\n", matriz[i][infos[1]-1], matriz[i][infos[1]-2]);
                result[i]=matriz[i][infos[1]-1] / matriz[i][infos[1]-2];
                printf("Resultado da Linha %d eh: %.2f\n\n", i+1, result[i]);
            }
            else if(i==infos[0]-2){
                //printf("matriz[i][infos[1]-1]: %.2f - matriz[i][infos[1]-2]): %.2f\n / matriz[i][infos[1]-3]:%.2f\n\n", matriz[i][infos[1]-1], matriz[i][infos[1]-2], matriz[i][infos[1]-3]);
                result[i]=((matriz[i][infos[1]-1] - (matriz[i][infos[1]-2]*result[i+1]))/ matriz[i][infos[1]-3]);
                printf("Resultado da Linha %d eh: %.2f\n\n", i+1, result[i]);
            }
            else{
                //printf("((matriz[i][infos[1]-1] - (matriz[i][infos[1]-2]*result[i+2]) - (matriz[i][infos[1]-3]*result[i+1])) : %.2f - %.2f - %.2f / matriz[i][infos[1]-4]): %.2f", matriz[i][infos[1]-1], matriz[i][infos[1]-2]*result[i+2], matriz[i][infos[1]-3]*result[i+1], matriz[i][infos[1]-4]);
                result[i]=((matriz[i][infos[1]-1] - (matriz[i][infos[1]-2]*result[i+2]) - (matriz[i][infos[1]-3]*result[i+1]))/ matriz[i][infos[1]-4]);
                printf("Resultado da Linha %d eh: %.2f\n\n", i+1, result[i]);
            }

        }
    } 

    return 0;
}



int main (int argc, char** argv){

    int *infos =  system_def();
    float **matriz =aloca_matriz(infos);

    print_matriz(matriz, infos);
    puts("Escolha o metodo de Resolucao:\n 1- Direto: Gauss\n 2- Iterativo: Jacobi\n");
    int op;
    scanf("%d", &op);
    if(op==1){
       int status=gauss(matriz, infos);
    }
    else if (op==2){

    }
    else puts("Opção Inexistente");

    return 0;
}