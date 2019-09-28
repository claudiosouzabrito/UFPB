#include "construtiva.h"
#include <math.h>
int construtiva(veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda1, int *count){
    int i,j;
    int custoSoma = 0;

    /*
    veiculo car2[description.vehicles];
    int count2[description.vehicles];
    int custoSoma = 0, i, j;

    for(i =0; i < description.vehicles; i++){
        car2[i].rota = (int*)malloc(numVertices* sizeof(int));
    //    for(j = 0; j <= count[i]; j++ ) car2[i].rota[j] = car[i].rota[j];

    //    car2[i].custo = car[i].custo;
    //   car2[i].cap = car[i].cap;
    //    count2[i] = count[i];
    }
    */
    int somaTam = 0;
    description.vehicles = createRota( car, description, numVertices, matriz, demanda1, count);
    /*
    for(int i = 0; i < description.vehicles; i++) somaTam += count[i];
    while(somaTam != numVertices + description.vehicles - 1){
        somaTam = pertubacaoNivel2( car, description, numVertices, matriz, demanda1, count);
    }
    */
    for(i = 0; i < description.vehicles; i++){
        printf("carro [%d] - Vertices: ", i);
        for(j = 0; j <= count[i]; j++){
            printf("%d, ",car[i].rota[j]);
         //   printf("Trocando os de maiores custos...\n");
        }
        printf("tam: %d, custo: %d, capacidade restante: %d\n",count[i], car[i].custo, car[i].cap);
    }
    
    for(i = 0; i < description.vehicles; i++){
        custoSoma += car[i].custo;
    }
    printf("custo final: %d\n", custoSoma);
    custoSoma = 0;
//    Dijkstra(numVertices, vertices , car2, description, matriz, demanda1, count2);
//    shift(car,description, numVertices, matriz, demanda1, count);
    for(i = 0; i < description.vehicles; i++){
        printf("carro [%d] - Vertices: ", i);
        for(j = 0; j <= count[i]; j++){
            printf("%d, ",car[i].rota[j]);
         //   printf("Trocando os de maiores custos...\n");
        }
        printf("tam: %d, custo: %d, capacidade restante: %d\n",count[i], car[i].custo, car[i].cap);
    }
    
    for(i = 0; i < description.vehicles; i++){
        custoSoma += car[i].custo;
    }
    printf("custo final: %d\n", custoSoma);
    return description.vehicles;
}

int heuristica(veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda1, int *count){
    int  i, j;
    int custoSoma = 0;
    puts("==============================");
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            printf("%d ", matriz[i][j]);
        }
        puts("");
    }
    description.vehicles = createRota( car, description, numVertices, matriz, demanda1, count);
//    shift(car,description, numVertices, matriz, demanda1, count); // busca local????
    /*
    for(i = 0; i < description.vehicles; i++){
        printf("carro [%d] - Vertices: ", i);
        for(j = 0; j <= count[i]; j++){
            printf("%d, ",car[i].rota[j]);
         //   printf("Trocando os de maiores custos...\n");
        }
        printf("tam: %d, custo: %d, capacidade restante: %d\n",count[i], car[i].custo, car[i].cap);
    }
    */
    for(i = 0; i < description.vehicles; i++){
        custoSoma += car[i].custo;
    }
//    printf("custo final: %d\n", custoSoma);
    custoSoma = 0;
    /*
    for(int i = 0; i < description.vehicles; i++) somaTam += count[i];
    while(somaTam != numVertices + description.vehicles - 1){
        somaTam = pertubacaoNivel2( car, description, numVertices, matriz, demanda1, count);
    }
    */
//    ILS( car, description, numVertices, matriz, demanda1, count);
    /*
    for(i = 0; i < description.vehicles; i++){
        printf("carro [%d] - Vertices: ", i);
        for(j = 0; j <= count[i]; j++){
            printf("%d ",car[i].rota[j]);
        //    if(j != count[i]) printf(", ");
        }
        printf("tam: %d, custo: %d, capacidade restante: %d\n",count[i], car[i].custo, car[i].cap);
    //    printf(";");
    }
    puts("");
    
    for(i = 0; i < description.vehicles; i++){
        custoSoma += car[i].custo;
    }
    printf("custo final: %d\n", custoSoma);
    */
    return description.vehicles;
}
typedef struct{
  double x;
  double y;
}coordenada;
int main(void){
    clock_t tempo[2];
    tempo[0] = clock();
//    struct timeval stop, start;
//    gettimeofday(&start, NULL);
    info_test description;
    const char test1[] = "cvrp1.txt";
    const char test2[] = "cvrp2.txt";
    const char test3[] = "cvrp3.txt";
    const char test4[] = "P-n16-k8.txt";
    int arqint = 1;
    char nomeArq[14];

    FILE *file_test;
    if(arqint == 1){
        strcpy(nomeArq, test1);
    }  
    else if(arqint == 2){
        strcpy(nomeArq, test2);
    }  
    else if(arqint == 3){
        strcpy(nomeArq, test3);
    }
    else if(arqint == 4){
        strcpy(nomeArq, test4);
    }
    

    char vert[2];
    vert[0] = nomeArq[3];
    vert[1] = nomeArq[4];
    
    file_test = fopen(nomeArq,"r");

    if(file_test== NULL)
        printf("Erro ao abrir o arquivo: %s.", nomeArq);

    char *line = NULL;
    size_t len = 0;
    int i, j;
    char *aux = NULL;
    char *aux2 = NULL;
    int flagDeman = 0;
    int demanda[551], demanda1[550];
    int contDemanda = 0;
    int flagAd = 0;
    int matriz[550][550];
    coordenada vertice[550];
    int contLinha = 0;
    int contVertice = 0;
    int numVertices;
    int flagD = 1;
    double X, Y;
    while ((getline(&line, &len, file_test)) != -1) {
        //printf("linha: %s:\n", line);       
        if(line[0] == 'D' && flagD){
            aux = &line[11];
            aux[strlen(aux) - 1] = '\0';
            numVertices = atoi(aux);
        //    printf("DIMENSION: %d\n", numVertices);
            flagD = 0;
        }
        if (line[0] == 'V'){
            aux = &line[10];
            aux[strlen(aux) - 1] = '\0';
            description.vehicles = atoi(aux);
        //    printf("VEHICLES: %d\n", description.vehicles);
            
        }
        else if (line[0] == 'C'){
            aux = &line[10];
            aux[strlen(aux) - 1] = '\0';
            description.capacity = atoi(aux);
        //    printf("CAPACITY: %d\n", description.capacity);

        }
        //INICIO DA FORMACAO DO ARRAY DE DEMANDA
        else if(flagDeman){
        //    puts("pegando demanda");
            aux = &line[4];
            aux[strlen(aux) - 1] = '\0';
            demanda[contDemanda] = atoi(aux);
            contDemanda++;
            if (contDemanda > numVertices) flagDeman = 0;
        }
        else if (line[0] == 'D' && !flagD) flagDeman = 1;
        //FIM DO ARRAY DE DEMANDA

        //INICIO DA FORMACAO DE MATRIZ DE ADJACENCIA
        else if(flagAd){
        //    puts("pegando coordenadas");
            aux = &line[4];
        //    printf("aux: %s\n", aux);
            for(i = 5; line[i] != ' '; i++)// puts("caminhando 1");
            aux = &line[i+1];
            aux[strlen(aux) - 1] = '\0';
        //    printf("selecionado: %s\n", aux);
            vertice[contVertice].y = atoi(aux);
            aux = &line[4];
            aux[i] = '\0';
        //    printf("selecionado: %s\n", aux);
            vertice[contVertice].x = atoi(aux);   
            contVertice++;
            if (contVertice > numVertices) flagAd = 0;
        }
        else if (line[0] == 'N' && line[1] == 'O')  flagAd = 1;
        //FIM DA MATRIZ E ADJACENCIA
        
    }


    

//SO PRA PRINTAR MESMO
    for(i = 0; i < numVertices; i++){
        demanda1[i] = demanda[i+1];
    //   printf("vertice: %d, demanda: %d\n", i, demanda1[i]);
    }
//    puts("");
    
 //   for(i=0; i < numVertices; i++) printf("%d : %d\n", i, demanda1[i]);
 /*
    for(j=0; j < numVertices; j++){
        printf("%d: %d %d\n", j, vertice[j].x, vertice[j].y);
    }
    */
    puts("");
    for(i=0; i < numVertices; i++){
        for(j=0; j < numVertices; j++){
            X = vertice[j].x - vertice[i].x;
            Y = vertice[j].y - vertice[i].y;
            matriz[i][j] = round(sqrt(X*X + Y*Y));
           if(i < 10 && j < 10) printf("%d ",matriz[i][j]);   
        }
        if(i < 10) puts("");
    }
    
//   gettimeofday(&stop, NULL);
//   printf("%lu\n", stop.tv_usec - start.tv_usec);
//   puts("Todos os arquivos de leitura para testes foram fechados.");

    veiculo car[description.vehicles + 1];
    for(i =0; i < description.vehicles + 1; i++){
        car[i].rota = (int*)malloc(numVertices* sizeof(int));
    }    

    int count[description.vehicles +1];
    
//    description.vehicles = construtiva( car, description, numVertices, matriz, demanda1, count);
    description.vehicles =  heuristica(car, description, numVertices, matriz, demanda1, count);
//    printf("num de veiculos velhos %d\n", description.vehicles);




//    for(i = 0; i < description.vehicles; i++) free(car[i].rota);

    fclose(file_test);
    tempo[1] = clock();
    double tempoMicro = (tempo[1] - tempo[0]) * 1000000/ CLOCKS_PER_SEC;
//    printf("tempo em microsegundos: %lf\n", tempoMicro);
//    puts("a final");
   return 0;
   
}
