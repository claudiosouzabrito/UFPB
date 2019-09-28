#include "heuristica.h"

void pertubacaoNivel1(  veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda, int *count){
//    printf("pertubacao nivel 1 !!\n");
    int i, j, j2, l = 0, i2, j3;
    int  custoSoma = 0;
    int flag;
    srand(time(NULL));
    for(i = 0; i < description.vehicles; i++){
    //    printf("carro: %d\n", i);
        count[i] = 1;
        for(j = 1; car[i].rota[j] != 0; j++) count[i]++;
        flag = 0;
        if(count[i] >= 3){
            int lista[count[i] - 1];
            for(j = 1, l = 0; j < count[i]; j++, l++){
            //    printf("\tvertice de posicao %d: %d\n",j, car[i].rota[j]);
                lista[l] = car[i].rota[j];
            }
            j = 1;
            /*
            for(l = 0; l < count[i] - 1; l++) printf("%d ", lista[l]);
            puts("");
            */
            while(flag < (count[i] - 1)){
                j2 = rand() % (count[i] - 1);
            //    printf("j2 = %d\n", j2);
                if(lista[j2] != -1){
                    flag++;
                    car[i].rota[j++] = lista[j2];
                    lista[j2] = -1;
                }
            }

        }
        car[i].rota[j] = 0;
    //    printf("tamanho da rota do carro %d: %d\n\n", i, count[i]);
    }
    for(i2 = 0; i2 < description.vehicles; i2++){
        car[i2].custo = 0;
        for(j3=0; j3 < count[i2]; j3++){
            car[i2].custo += matriz[car[i2].rota[j3]][car[i2].rota[j3+1]];
        }
    }
    /*
    for(i = 0; i < description.vehicles; i++){
        printf("carro [%d] - Vertices: ", i);
        for(j = 0; j <= count[i]; j++){
            printf("%d, ",car[i].rota[j]);
         //   printf("Trocando os de maiores custos...\n");
        }
        printf("tam: %d, custo: %lf, capacidade restante: %d\n",count[i], car[i].custo, car[i].cap);
        }
        */   
        for(i = 0; i < description.vehicles; i++){
            custoSoma += car[i].custo;
        }
    //    printf("custo final: %lf\n", custoSoma);
        
}

int pertubacaoNivel2(  veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda, int *count){
//    printf("pertubacao nivel 2 !!\n");
    int i, j , j2, l = 0, k, x, w;
    int custoSoma = 0;
    int flag = 0;
    srand(time(NULL));
    int lista[numVertices - 1];
    int menorDemanda = demanda[1];
//    printf("demanda 0 %d/%d\n", demanda[0], demanda[1]);
//    printf("desconstruindo\n");
    for(i = 0; i < description.vehicles; i++){
    //    printf("carro: %d\n", i);
        count[i] = 1;
        for(j = 1; car[i].rota[j] != 0; j++) count[i]++;
        car[i].cap = description.capacity;
        car[i].custo = 0;
        for(j = 1; j < count[i]; j++, l++){
        //    printf("\tvertice de posicao %d: %d\n",j, car[i].rota[j]);
            lista[l] = car[i].rota[j];
            car[i].rota[j] = 0;
        }
        count[i] = 1;
    }
    /*
    for(i = 0; i < (numVertices - 1); i++) printf("%d ", lista[i]);
    puts("");
    printf("construindo\n");
    */
    for(i = 0, l = 0; i < description.vehicles; i++){
    //    printf("carro: %d\n", i);
        j = 1;
        while(car[i].cap >= menorDemanda && flag < (numVertices - 1)){
            j2 = rand() % (numVertices - 1);
            if( lista[j2] != -1 && car[i].cap >= demanda[lista[j2]]){
                flag++;
            //    printf("colocando vertice %d\n", lista[j2]);
                w = lista[j2];
            //    printf("premiado: %d\n", w);
                car[i].rota[j++] = w;
                car[i].cap -= demanda[w];
                x = car[i].rota[count[i]-1];
                car[i].custo += matriz[x][w];
            //    printf("test\n");
                count[i]++;
            //    printf("test\n");
                lista[j2] = -1;
            //    printf("test\n");
            } 
            menorDemanda =  description.capacity;  
            for(k = 0; k < (numVertices - 1); k++){
            //    printf("testfor %d\n", flag);
                if(lista[k] != -1 && demanda[lista[k]] < menorDemanda && demanda[lista[k]] != 0 ){
                //    printf("testeif\n");
                    menorDemanda = demanda[lista[k]];
                } 
            }
        }
        car[i].rota[j] = 0;
        car[i].custo += matriz[car[i].rota[j]][car[i].rota[j-1]];
    //    printf("while %d      %d vs %d\n", flag, car[i].cap, menorDemanda );
    }
    int somaTam = 0;
    
    for(i = 0; i < description.vehicles; i++){
        somaTam += count[i];
    //    printf("carro [%d] - Vertices: ", i);
    //    for(j = 0; j <= count[i]; j++){
        //    printf("%d, ",car[i].rota[j]);
         //   printf("Trocando os de maiores custos...\n");
    //    }
    //    printf("tam: %d, custo: %lf, capacidade restante: %d\n",count[i], car[i].custo, car[i].cap);
    }
    
    for(i = 0; i < description.vehicles; i++){
        custoSoma += car[i].custo;
    }
//    printf("custo final: %lf\n", custoSoma);
    return somaTam;
}

void ILS(  veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda, int *count){
//    puts("ILS!!\n");
//    createRota( car, description, numVertices, matriz, demanda, count);
    shift(car,description, numVertices, matriz, demanda, count); // busca local????
    int i, j, flag = 0, somaTam;
    veiculo car2[description.vehicles];
    int count2[description.vehicles];
    veiculo car3[description.vehicles];
    int count3[description.vehicles];
    /*
    for(i = 0; i < description.vehicles; i++){
        printf("carro [%d] - Vertices: ", i);
        for(j = 0; j <= count[i]; j++){
            printf("%d, ",car[i].rota[j]);
         //   printf("Trocando os de maiores custos...\n");
        }
        printf("tam: %d, custo: %lf, capacidade restante: %d\n",count[i], car[i].custo, car[i].cap);
    }
    puts("==============================");
    */
    for(i =0; i < description.vehicles; i++){
        car2[i].rota = (int*)malloc(numVertices* sizeof(int));
        car3[i].rota = (int*)malloc(numVertices* sizeof(int));
        for(j = 0; j <= count[i]; j++ ){
            car2[i].rota[j] = car[i].rota[j];
            car3[i].rota[j] = car[i].rota[j];
        }
        car2[i].custo = car[i].custo;
        car2[i].cap = car[i].cap;
        count2[i] = count[i];
        car3[i].custo = car2[i].custo;
        car3[i].cap = car2[i].cap;
        count3[i] = count2[i];
    }
    /*
    for(i = 0; i < description.vehicles; i++){
        printf("carro [%d] - Vertices: ", i);
        for(j = 0; j <= count2[i]; j++){
            printf("%d, ",car2[i].rota[j]);
         //   printf("Trocando os de maiores custos...\n");
        }
        printf("tam: %d, custo: %lf, capacidade restante: %d\n",count2[i], car2[i].custo, car2[i].cap);
    }
    /*
    puts("==============================");
    for(i = 0; i < description.vehicles; i++){
        printf("carro [%d] - Vertices: ", i);
        for(j = 0; j <= count3[i]; j++){
            printf("%d, ",car3[i].rota[j]);
            printf("Trocando os de maiores custos...\n");
        }
       printf("tam: %d, custo: %lf, capacidade restante: %d\n",count3[i], car3[i].custo, car3[i].cap);
    }
    */
    int custoSoma = 0, custoSoma2 = 0;
    for(i = 0; i < description.vehicles; i++) custoSoma2 += car2[i].custo;
    custoSoma = custoSoma2;
    int contador = 0;
   // printf("custo final: %d\n", custoSoma);    
    while(contador++ < 100){
    //   printf("while = %lf\n", custoSoma2);
        custoSoma2 = 0;
        if(flag < 5){
            pertubacaoNivel1( car2, description, numVertices, matriz, demanda, count2);
        }
        else{
            while(1){
            //    puts("novo while");
                for(i =0; i < description.vehicles; i++){
                //    puts("corrigindo");
                    for(j = 0; j <= count2[i]; j++ ) car3[i].rota[j] = car2[i].rota[j];
                    car3[i].custo = car2[i].custo;
                    car3[i].cap = car2[i].cap;
                    count3[i] = count2[i];
                }
                for(i = 0; i < description.vehicles; i++){
                //    printf("carro [%d] - Vertices: ", i);
                    for(j = 0; j <= count2[i]; j++){
                    //    printf("%d, ",car2[i].rota[j]);
                    //   printf("Trocando os de maiores custos...\n");
                    }
            //        printf("tam: %d, custo: %lf, capacidade restante: %d\n",count2[i], car2[i].custo, car2[i].cap);
                }
            //    puts("==============================");
            /*
                for(i = 0; i < description.vehicles; i++){
                    printf("carro [%d] - Vertices: ", i);
                    for(j = 0; j <= count3[i]; j++){
                        printf("%d, ",car3[i].rota[j]);
                    //   printf("Trocando os de maiores custos...\n");
                    }
                //    printf("tam: %d, custo: %lf, capacidade restante: %d\n",count3[i], car3[i].custo, car3[i].cap);
                }
                */
                somaTam = pertubacaoNivel2( car3, description, numVertices, matriz, demanda, count3);
                if(somaTam == numVertices + description.vehicles - 1){
                //    puts("retornou certo\n");
                    break;
                }
            }
        //    puts("saiu do while");
            for(i =0; i < description.vehicles; i++){
                for(j = 0; j <= count3[i]; j++ ) car2[i].rota[j] = car3[i].rota[j];
                car2[i].custo = car3[i].custo;
                car2[i].cap = car3[i].cap;
                count2[i] = count3[i];
            }
            flag = 0;
        }
        shift(car2,description, numVertices, matriz, demanda, count2);
        for(i = 0; i < description.vehicles; i++) custoSoma2 += car2[i].custo;
        if(custoSoma2 >= custoSoma){
        //    printf("piora de busca local: %lf\n", custoSoma2 );
            flag++;
            for(i =0; i < description.vehicles; i++){
                for(j = 0; j <= count[i]; j++ ) car2[i].rota[j] = car[i].rota[j];
                car2[i].custo = car[i].custo;
                car2[i].cap = car[i].cap;
                count2[i] = count[i];
            }
            custoSoma2 = custoSoma;
        }
        else{
            flag = 0;
        //    printf("melhora de busca local: %lf\n", custoSoma2);
            for(i =0; i < description.vehicles; i++){
                for(j = 0; j <= count2[i]; j++ ) car[i].rota[j] = car2[i].rota[j];
                
                car[i].custo = car2[i].custo;
                car[i].cap = car2[i].cap;
                count[i] = count2[i];
            }
            custoSoma = custoSoma2;
        }
        printf("laco ILS\n");
    }
    printf("solucao otima?\n");
    custoSoma2 = 0;
    for(i = 0; i < description.vehicles; i++){
        car[i].cap = description.capacity;
        count[i] = 1;
        car[i].custo = 0;
        for(j = 1; car[i].rota[j] != 0; j++){
            count[i]++;
            car[i].cap -= demanda[car[i].rota[j]];
        }
        printf("carro [%d] - Vertices: ", i);
        for(j = 0; j <= count[i]; j++){
            if(j < count[i]) car[i].custo += matriz[car[i].rota[j]][car[i].rota[j+1]];
            printf("%d, ",car[i].rota[j]);
         //   printf("Trocando os de maiores custos...\n");
        }
        printf("tam: %d, custo: %d, capacidade restante: %d\n",count[i], car[i].custo, car[i].cap);
        custoSoma2 += car[i].custo;
    }
        
    printf("custo final: %d\n", custoSoma2);    
    
}

