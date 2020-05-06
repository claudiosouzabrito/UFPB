#include "construtiva.h"

int construtiva(veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda1, int *count, vertice *vertices){
    int custoSoma = 0, i,j;

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
    shift(car,description, numVertices, matriz, demanda1, count);
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

int heuristica(veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda1, int *count, int ideal){
    int custoSoma = 0, i, j;
    description.vehicles = createRota( car, description, numVertices, matriz, demanda1, count);
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
    /*
    for(int i = 0; i < description.vehicles; i++) somaTam += count[i];
    while(somaTam != numVertices + description.vehicles - 1){
        somaTam = pertubacaoNivel2( car, description, numVertices, matriz, demanda1, count);
    }
    */
    ILS( car, description, numVertices, matriz, demanda1, count, ideal);
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

int main(void){
    clock_t tempo[2];
    tempo[0] = clock();
//    struct timeval stop, start;
//    gettimeofday(&start, NULL);
    info_test description;

    const char test2[] = "P-n19-k2.txt";
    const char test1[] = "P-n16-k8.txt";
    const char test3[] = "P-n20-k2.txt";
    const char test4[] = "P-n23-k8.txt"; 
    const char test5[] = "P-n45-k5.txt";
    const char test6[] = "P-n50-k10.txt"; 
    const char test7[] = "P-n51-k10.txt"; 
    const char test8[] = "P-n55-k7.txt";
    int arqint = 4;
    char nomeArq[14];
    int ideal;

    FILE *file_test;
    if(arqint == 1){
        strcpy(nomeArq, test1);
        ideal = 450;
    }  
    else if(arqint == 2){
        strcpy(nomeArq, test2);
        ideal = 212;
    }  
    else if(arqint == 3){
        strcpy(nomeArq, test3);
        ideal = 216;
    }
    else if(arqint == 4){
        strcpy(nomeArq, test4);
        ideal = 529;
    }
    else if(arqint == 5){
        strcpy(nomeArq, test5);
        ideal = 510;
    }
    else if(arqint == 6){
        strcpy(nomeArq, test6);
        ideal = 696;
    }  
    else if(arqint == 7){
        strcpy(nomeArq, test7);
        ideal = 741;
    }
    else{
        strcpy(nomeArq, test8);
        ideal = 568;
    }

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
        //printf("linha: %s:\n", line);       
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


    

//SO PRA PRINTAR MESMO
    vertice vertices[numVertices];
    for(i = 0; i < numVertices; i++){
        demanda1[i] = demanda[i+1];
        vertices[i].demanda = demanda[i+1];
    //   printf("vertice: %d, demanda: %d\n", i, demanda1[i]);
    }
    puts("");
    /*
    for(i = 0; i < numVertices; i++){
        for(j = 0; j < numVertices; j++){
            printf("%d ", matriz[i][j]);
        }
        puts("\n");
    }
*/
    
//   gettimeofday(&stop, NULL);
//   printf("%lu\n", stop.tv_usec - start.tv_usec);
//   puts("Todos os arquivos de leitura para testes foram fechados.");

    veiculo car[description.vehicles + 1];
    for(i =0; i < description.vehicles + 1; i++){
        car[i].rota = (int*)malloc(numVertices* sizeof(int));
    }    

    int count[description.vehicles +1];
    
 //   description.vehicles = construtiva( car, description, numVertices, matriz, demanda1, count, vertices);
    description.vehicles =   heuristica(car, description, numVertices, matriz, demanda1, count, ideal);
    printf("num de veiculos velhos %d\n", description.vehicles);




//    for(i = 0; i < description.vehicles; i++) free(car[i].rota);

    fclose(file_test);
    tempo[1] = clock();
    double tempoMicro = (tempo[1] - tempo[0]) * 1000000/ CLOCKS_PER_SEC;
    printf("tempo em microsegundos: %lf\n", tempoMicro);
    puts("a final");
   return 1;
}
