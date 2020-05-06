#include "construtiva.h"

int createRota(  veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda, int *count){
//    printf("construcao de rota\n");
    int disp[numVertices];
    int contRota = 0;
    int i = 0, j, x, w = 1;
    puts("==============================");
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            printf("%d ", matriz[i][j]);
        }
        puts("");
    }
    puts("==============================");

    for(i = 0; i < numVertices; i++) disp[i] = 1;

    for(i = 0; i < description.vehicles; i++){
        car[i].cap = description.capacity;
        car[i].rota[0] = 0;
        count[i] = 1;
        car[i].custo = 0;
    }
    i = 0;
    while (i < description.vehicles){
        printf("Carro[%d]\n", i);
        while(w < numVertices){
            //printf("demanda do vertice: %d vs capacidade do veiculo %d: %d\n", demanda[w], i, cap[i]);

            if(disp[w] && demanda[w] <= car[i].cap){ 
                car[i].rota[count[i]] = w;
                disp[w] = 0;
                x = car[i].rota[count[i]-1];
                printf(" aresta%d-%d: %d + %d = %d\n",x, w, matriz[x][w], car[i].custo, car[i].custo + matriz[x][w]);
                car[i].custo += matriz[x][w];
                //printf("cap do veiculo %d antes %d\n",i, car[i].cap);
                car[i].cap = car[i].cap - demanda[w];
                //printf("cap do veiculo %d depois %d\n",i, car[i].cap);
            //  printf("carro[%d].rota[%d] = %d \n",i, count[i], car[i].rota[count[i]]);
            //   puts("");
            /*
                if(matriz[x][w]>maior[i][0]){
                    maior[i][0]=matriz[x][w];
                    maior[i][1]=x;
                    maior[i][2]=w;
                    printf("Maior peso: %d, arestas: %d-%d\n", maior[i][0], maior[i][1], maior[i][2]);

                }
                */
                count[i]++;
                
                    

                
            }
            w++;
        }
 //       puts("");
        w = 1;
        i++;
    }
    int somaTam = 0;
    for(i = 0; i < description.vehicles; i++){
        somaTam += count[i];
        car[i].rota[count[i]] = 0;
        car[i].custo += matriz[car[i].rota[count[i]-1]][0];
    } 
    if( somaTam != numVertices + description.vehicles - 1){
        car[i].cap = description.capacity;
        car[i].custo = 0;
        car[i].rota[0] = 0;
        j = 1;
        count[i] = 1;
        description.vehicles++;
        printf("num de veiculos novos %d\n", description.vehicles);
        for(w = 1; w < numVertices; w++){
            if(disp[w]){
            //    puts("a");
                disp[w] = 0;
                car[i].custo += matriz[w][car[i].rota[j-1]];
                car[i].rota[j++] = w;
                count[i]++;
                car[i].cap -= demanda[w];
            }
        }
        car[i].rota[j] = 0;
        car[i].custo += matriz[0][car[i].rota[j-1]];
    }
    //SO PRA PRINTAR MESMO
    
    for(i = 0; i < description.vehicles; i++){
        printf("carro [%d] - Vertices: ", i);
        for(j = 0; j <= count[i]; j++){
            printf("%d, ",car[i].rota[j]);
         //   printf("Trocando os de maiores custos...\n");
        }
        printf("tam: %d, custo: %d, capacidade restante: %d\n",count[i], car[i].custo, car[i].cap);
    }
    int custoSoma = 0;
    for(i = 0; i < description.vehicles; i++){
        custoSoma += car[i].custo;
    }
    printf("custo final: %d\n", custoSoma);
    custoSoma = 0;
    
   return description.vehicles;
}
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
        //    printf("Carro [%d]: \n", i);
            car[i].rota[0] = 0;
            //QVPR[i]=0;
            //printf("%d<%d\n", w, numVertices);
            //printf("%d<=%d\n", vertice[w].demanda, car[i].cap);
            while ((w < numVertices) && (demanda[w]<= car[i].cap)){
                if (w == 0 || flag==0){
                    car[i].rota[0] = 0;
                //    printf("Inicializando o Deposito\n\n");
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
                    //    printf("Analisando a aresta [%d]-[%d]\n", w, j);
                        if(w==0 || flag==0){
                            vertice[j].pai = 0;
                            vertice[j].key = matriz[0][j];
                            //QVPR[i]++;
                            
                        }
                        else{
                            vertice[j].pai = w;
                            //printf("meu pai eh: %d\n", vertice[j].pai);
                       //     printf("Definindo o Key como sendo %d + %d = %d\n",vertice[car[i].rota[QVPR[i]]].key, matriz[j][w], matriz[j][w]+vertice[car[i].rota[QVPR[i]]].key);
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
                        //    printf("Rota min entre [%d]->[%d] = %d\n", w, j, min);
                        //    printf("MelhorOP: %d, cujo custo eh: %d\n", melhorOP, vertice[j].key);
                        }
                        else{
                          //  printf("Peso entre [%d]->[%d] =(%d) eh maior q o min (%d)\n", w, j, vertice[j].key, min);
                        }
                        //car[i].custo += matriz[x][w];
                        //car[i].cap -= vertice[w].demanda;
                        
                    }
                //    puts("");
                    
            }
            flag=1;
        //    puts("");
       //     puts("");
        //    printf("Vertice retirado da lista[%d] \n", melhorOP);
            ++QVPR[i];
        //    printf("nmero QVPR[i] = %d\n",QVPR[i]);
            car[i].custo=vertice[melhorOP].key;
        //    printf("Custo total: %d\n", car[i].custo);
        //    printf("Capacidade Restante do carro[%d]: %d - %d = ", i,car[i].cap,demanda[melhorOP]);
            car[i].cap-=demanda[melhorOP];
        //    printf("%d\n\n", car[i].cap);            
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
            //    printf("a");
                if(demanda[i] <= car[carro].cap){
                //    printf("b");
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
        // printf("Rota do Carro %d\n",i);
         for(int h=0; h<=aux; h++){
             count[i]++;
        //    printf("%d - ", car[i].rota[h]);
            if(h==aux){
                ++QVPR[i];
                car[i].rota[h+1]=0;
                car[i].custo+=matriz[car[i].rota[h]][0];
                count[i]++;
            //    printf("%d - ", car[i].rota[h+1]);
            }
         }
         count[i]--;
    //    puts("");
    //    printf("Quantidade de verticies alocados no veiculo %d: %d\n", i, --count[i]);
    }            
    int custoSoma = 0;
    for(i = 0; i < description.vehicles; i++){
    //    printf("carro [%d] - Vertices: ", i);
        for(j = 0; j <= count[i]; j++){
        //    printf("%d, ",car[i].rota[j]);
         //   printf("Trocando os de maiores custos...\n");
        }
    //    printf("tam: %d, custo: %d, capacidade restante: %d\n",count[i], car[i].custo, car[i].cap);
    }
    
    for(i = 0; i < description.vehicles; i++){
        custoSoma += car[i].custo;
    }
//    printf("custo final: %d\n", custoSoma);
}