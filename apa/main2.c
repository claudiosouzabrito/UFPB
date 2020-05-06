   
#include <stdio.h> 
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

typedef struct{
  int vehicles;
  int capacity;
}info_test;

typedef struct{
    int *rota;
    int custo;
    int cap;
}veiculo;

//MOVIMENTO DE VIZINHANCA AINDA NAO FINALIZADO
/*
void shift(veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda,int *count){
    int i, j, j2, k, l, l2, m;
    int ver1, ver2;
    for(i = 0; i < description.vehicles; i++){
        for(j = 1; j < count[i]; j++){
            for(k = 0; k < description.vehicles; k++){
                if(i != k && demanda[j] <= car[k].cap){
                    if(count[k] != 2){
                        for(l = 1 , l2 = 2; l2 < count[k] ; l++, l2++){
                        
                            //ALTERAR A ROTA DE ORIGEM
                            
                            ver1 = car[i].custo;
                            j2 = car[i].rota[j];
                            ver1 -= matriz[car[i].rota[j-1]][j2];//antes
                            ver1 -= matriz[j2][car[i].rota[j+1]];//dps
                            ver1 += matriz[car[i].rota[j-1]][car[i].rota[j+1]];
                            for(m = j; m < count[i]-1; m++){
                                car[i].rota[m] = car[i].rota[m+1];
                            } 
                            count[i]--;
                            //ALTERAR A ROTA DE DESTINO
                            
                            ver2 = car[k].custo;
                            ver2 -= matriz[car[k].rota[l]][car[k].rota[l2]];
                            ver2 += matriz[car[k].rota[l]][j2];
                            ver2 += matriz[j2][car[k].rota[l2]];
                                         
                        }
                    }
                    else{
                            
                    }
                  
                }
            }
        }
    }
}
*/
typedef struct{
    int pai;
    int key;
    int demanda;
}vertice;

void Dijkstra(int numVertices, vertice *vertice, veiculo *car, info_test description, int matriz[][numVertices], int *demanda, int *count){
    int Q[numVertices];
    int help=0;
    int w = 0, i = 0, x = 0, j = 0, melhorOP=0;
    int min = 200, max = 0, k = 0, flag=0;
    int QVPR[description.vehicles];//Quantidade de vértices por rota para cada carro 
    for (i = 0; i < numVertices;i++){
        if(i==0)
            vertice[i].key = 0;//raiz
        vertice[i].key = 1000;
        vertice[i].pai = NULL;
        QVPR[i] = 0;
        Q[i] = i;
    }
    for (i = 0; i < description.vehicles;i++){
        car[i].cap = description.capacity;
        car[i].custo = 0;
    }
        for (i = 0; i < description.vehicles; i++){
            flag=0;
            w=0;
            printf("Carro [%d]: \n", i);
            car[i].rota[0] = 0;
            //QVPR[i]=0;
            //printf("%d<%d\n", w, numVertices);
            //printf("%d<=%d\n", vertice[w].demanda, car[i].cap);
            while ((w < numVertices) && (demanda[w]<= car[i].cap)){
                if (w == 0 || flag==0){
                    car[i].rota[0] = 0;
                    printf("Inicializando o Deposito\n\n");
                }

               // x = car[i].rota[QVPR[i] - 1];
               // printf("W=%d\n", w);
                min = 20000;
                j=1;   //seta p valor alto;
                for (j = 1; j <= numVertices-1;j++){        //seleciona o vertice de menor peso partindo do anterior
                    //printf("%d, %d!=%d, %d<%d\n", Q[w], j, w, vertice[j].demanda, car[i].cap);
                    //ADICIONAR COND P ELE N FAZER CICLO (1->2) (2_>1)!!!
                    if((Q[j]!=-1) && (j!=w) && (demanda[j] <= car[i].cap)){//condicao de demanda
                        //se existir um vertice de ligacao e ele n exceder a demanda, 
                        printf("Analisando a aresta [%d]-[%d]\n", w, j);
                        if(w==0 || flag==0){
                            vertice[j].pai = 0;
                            vertice[j].key = matriz[0][j];
                            //QVPR[i]++;
                            
                        }
                        else{
                            vertice[j].pai = w;
                            //printf("meu pai eh: %d\n", vertice[j].pai);
                            printf("Definindo o Key como sendo %d + %d = %d\n",vertice[car[i].rota[QVPR[i]]].key, matriz[j][w], matriz[j][w]+vertice[car[i].rota[QVPR[i]]].key);
                            vertice[j].key = matriz[j][w]+vertice[melhorOP].key;
                            //printf("meu peso de %d (eu) p %d (pai) eh: %d\n", j, vertice[j].pai, vertice[j].key);
                            /*for (k = (j-1); k >= 0;j--){
                                //calcular custo de modo retroativo
                                vertice[j].key += vertice[j].pai ;
                                printf(" peso de %d p %d eh: %d\n", j-1,j , vertice[j].key);
                            }*/
                        }
                        if(vertice[j].key<min){
                            min = vertice[j].key;
                            melhorOP = j;
                            printf("Rota min entre [%d]->[%d] = %d\n", w, j, min);
                            printf("MelhorOP: %d, cujo custo eh: %d\n", melhorOP, vertice[j].key);
                        }
                        else{
                            printf("Peso entre [%d]->[%d] =(%d) eh maior q o min (%d)\n", w, j, vertice[j].key, min);
                        }
                        //car[i].custo += matriz[x][w];
                        //car[i].cap -= vertice[w].demanda;
                        
                    }
                    puts("");
                    
            }
            flag=1;
            puts("");
            puts("");
            printf("Vertice retirado da lista[%d] \n", melhorOP);
            ++QVPR[i];
            printf("nmero QVPR[i] = %d\n",QVPR[i]);
            car[i].custo=vertice[melhorOP].key;
            printf("Custo total: %d\n", car[i].custo);
            printf("Capacidade Restante do carro[%d]: %d - %d = ", i,car[i].cap,demanda[melhorOP]);
            car[i].cap-=demanda[melhorOP];
            printf("%d\n\n", car[i].cap);            
            Q[melhorOP] = -1;
            car[i].rota[QVPR[i]] = melhorOP;
            w=melhorOP;
           
        }
        melhorOP=0;
        //printf("Rota do Carro %d\n",i);
        //for(int h=0; h<=QVPR[i];h++){
        //printf("%d - ", car[i].rota[h]);
   // }
    }
    //Rearranja os vertices que sobraram para os que anda possuem capacidade, mesmo sem ser 
    //o menor caminho
    for(int carro=0; carro<description.vehicles;carro++){
        for(i=1;i<numVertices;i++){
            if(Q[i]!=-1){
                printf("a");
                if(demanda[i] <= car[carro].cap){
                    printf("b");
                    ++QVPR[carro];
                    car[carro].rota[QVPR[carro]] = i;
                    //car[carro].custo+=matriz[car[carro].rota[QVPR[carro]-1]][car[carro].rota[QVPR[carro]]];
                }
            }
        }
    }

    
    for (i = 0; i < description.vehicles; i++){
        int aux=QVPR[i];
        count[i]=0;
         printf("Rota do Carro %d\n",i);
         for(int h=0; h<=aux; h++){
             count[i]++;
            printf("%d - ", car[i].rota[h]);
            if(h==aux){
                ++QVPR[i];
                car[i].rota[h+1]=0;
                car[i].custo+=matriz[car[i].rota[h]][0];
                count[i]++;
                printf("%d - ", car[i].rota[h+1]);
            }
         }
        puts("");
        printf("Quantidade de verticies alocados no veiculo %d: %d\n", i, --count[i]);
    }            
}
//CRIANDO ROTA INICIAL, E CHAMANDO AS FUNCOES DE MOVIMENTO DE VIZINHANCA
void createRota(  veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda, int *count){
    int disp[numVertices];
    int contRota = 0;
    int i = 0, j, x, w = 1;

    for(i = 0; i < numVertices; i++) disp[i] = 1; //ARRAY DE VERTICES DISPONIVEIS, 1 = DISPONIVEL

    for(i = 0; i < description.vehicles; i++){
        car[i].cap = description.capacity;
        car[i].rota[0] = 0;
        count[i] = 1;
        car[i].custo = 0;
    }
    i = 0;
  
    while (i < description.vehicles){ //UM VEICULO EH PREENCHIDO POR VEZ
        printf("Carro[%d]: ", i);
        while(w < numVertices){ //A SEQUENCIA DE VERTICES QUE ENTRAM NA ROTA DO VEICULO EH A MESMA DAS INSTANCIAS
          
            if(disp[w] && demanda[w] <= car[i].cap){ 
                car[i].rota[count[i]] = w;
                disp[w] = 0;
                x = car[i].rota[count[i]-1];
                car[i].custo += matriz[x][w]; // CALCULANDO NOVO CUSTO
              
                car[i].cap = car[i].cap - demanda[w]; // CALCULADO CAPACIDADE ATUAL
               
                count[i]++; // ARRAY QUE CORRESPONDE AO TAMANHO DE VERTICES NA ROTA EH INCREMENTADO 
            }
            w++;
        }
        puts("");
        w = 1;
        i++;
    }
  
    for(i = 0; i < description.vehicles; i++){
      //TODAS AS ROTAS ACABAM EM 0
        car[i].rota[count[i]] = 0; 
        car[i].custo += matriz[car[i].rota[count[i]-1]][0];
    } 
    
    //SO PRA PRINTAR MESMO
    for(i = 0; i < description.vehicles; i++){
        printf("carro [%d] - Vertices: ", i);
        for(j = 0; j <= count[i]; j++){
            printf("%d, ",car[i].rota[j]);
        }
        printf(" custo: %d, capacidade restante: %d\n", car[i].custo, car[i].cap);
    }
  //  shift(car,description, numVertices, matriz, demanda, count, maior);

}



//MAIN: LEITURA DO ARQUIVO

int main(void){
//    struct timeval stop, start;
//    gettimeofday(&start, NULL);
    info_test description;

    FILE *file_test;

    const char test1[] = "P-n19-k2.txt";
    const char test2[] = "P-n16-k8.txt";
    const char test3[] = "P-n20-k2.txt";
    const char test4[] = "P-n23-k8.txt"; 
    const char test5[] = "P-n45-k5.txt";
    const char test6[] = "P-n50-k10.txt"; 
    const char test7[] = "P-n51-k10.txt"; 
    const char test8[] = "P-n55-k7.txt";

    char nomeArq[14];
    strcpy(nomeArq, test1);
    char vert[2];
    vert[0] = nomeArq[3];
    vert[1] = nomeArq[4];
    int numVertices = atoi(vert);
    file_test = fopen(nomeArq,"r");

    if(file_test== NULL)
        printf("Erro ao abrir o arquivo: %s.", nomeArq);

    char *line = NULL;
    size_t len = 0;
    int i, j;
    char *aux = NULL;
    int flagDeman = 0;
    int demanda[numVertices+1], demanda1[numVertices];
    int contDemanda = 0;
    int flagAd = 0;
    int matriz[numVertices][numVertices];
    int contLinha = 0;
    int contColun = 0;
    
    while ((getline(&line, &len, file_test)) != -1) {
        if (line[0] == 'V'){
            aux = &line[10];
            aux[11] = '\0';
            description.vehicles = atoi(aux);
        }
        else if (line[0] == 'C'){
            aux = &line[10];
            aux[13] = '\0';
            description.capacity = atoi(aux);

        }
        //INICIO DA FORMACAO DO ARRAY DE DEMANDA
        else if(flagDeman){
            if(line[5] == ' '){
                aux = &line[6];
                aux[7] = '\0';
                demanda[contDemanda] = atoi(aux);
            }
            else{
                aux = &line[5];
                aux[7] = '\0';
                demanda[contDemanda] = atoi(aux);
            }
            contDemanda++;
            if (contDemanda > numVertices) flagDeman = 0;
        }
        else if (line[0] == 'D')
            flagDeman = 1;
        //FIM DO ARRAY DE DEMANDA

        //INICIO DA FORMACAO DE MATRIZ DE ADJACENCIA
        else if(flagAd){
            for(contColun = 0; contColun <= numVertices-1; contColun++){
                if (contLinha == contColun) 
                    matriz[contLinha][contColun] = 0;
                else if(contColun == 0){
                    if(line[2] == ' '){
                        aux = &line[3];
                        aux[1] = '\0';
                        matriz[contLinha][contColun] = atoi(aux);
                    
                    }
                    else{
                        aux = &line[2];
                        aux[2] = '\0';
                        matriz[contLinha][contColun] = atoi(aux);
                    }
                }
                else{
                    if(line[7 + 5*(contColun-1)] == ' '){//Numero de 1 digito
                        aux = &line[8 + 5*(contColun-1)];
                        aux[1] = '\0';
                        matriz[contLinha][contColun] = atoi(aux);
                    
                    }
                    else{
                        aux = &line[7 + 5*(contColun-1)];//numero de dois digitos
                        aux[2] = '\0';
                        matriz[contLinha][contColun] = atoi(aux);
                    }
                }
                
            }
            contColun = 0;
            contLinha++;
            if (contLinha >= numVertices) flagAd = 0;
        }
        else if (line[0] == 'E')  flagAd = 1;
        //FIM DA MATRIZ E ADJACENCIA
        
    }

veiculo car[description.vehicles];
    for(i =0; i <= description.vehicles; i++){
        car[i].rota = (int*)malloc(numVertices* sizeof(int));
    }    

    int count[description.vehicles];
    //createRota( car, description, numVertices, matriz, demanda1, count);

    vertice vertice[numVertices];
    

//SO PRA PRINTAR MESMO

    for(i = 0; i < numVertices; i++){ //EXITE UM ERRO NA LEITURA  DO ARRAY DE DEMANDAS, ISSO CONSERTA
        demanda1[i] = demanda[i+1];

    }
    puts("\n");
    
    fclose(file_test);
 
    //CRIACAO DO ARRAY QUE MOSTRA OS VERTICES DE CADA ROTA
    
    //CHAMADA DO DIJKSTRA TEM Q VIR SO DPS DA ATUALIZAÇÃO DA DEMANDA
    Dijkstra(numVertices, vertice, car,description, matriz, demanda1, count);



    for(i = 0; i < description.vehicles; i++) free(car[i].rota);
   return 0;
}

