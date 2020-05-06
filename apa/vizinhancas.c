#include "vizinhancas.h"

void exchange(veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda,int *count){
    printf("exchange !!\n");
    int i, j, j2, l, l2, m;
    int ver1, atualdif = 0;
    vnd dif;
    dif.custo = 0;
    int flagMelhora = 0;
    int jaVisitados[description.vehicles];
    for(i = 0; i < description.vehicles; i++){
    //    printf("carro: %d\n", i);
        if(count[i] >= 3){
            for(j = 1; j < count[i]; j++){
            //    printf("\tvertice de posicao %d: %d\n",j, car[i].rota[j]);
                for(l = 1; l < count[i] ; l++){
                //    printf("\t\tvertice de posicao %d: %d\n", l, car[i].rota[l]);
                    if( j != l){
                        j2 = car[i].rota[j];// vertice em questao
                        l2 = car[i].rota[l];

                        //ALTERAR A ROTA DE ORIGEM
                        ver1 = car[i].custo;
                        if (l2 == car[i].rota[j+1]){
                        //    printf("\t\t\tcaso fudido 1\n");
                            ver1 -= matriz[car[i].rota[j-1]][j2];
                            ver1 -= matriz[l2][car[i].rota[l+1]];
                            ver1 += matriz[car[i].rota[j-1]][l2];
                            ver1 += matriz[j2][car[i].rota[l+1]];
                        }
                        else if (j2 == car[i].rota[l+1]){
                        //    printf("\t\t\tcaso fudido 2\n");
                            ver1 -= matriz[car[i].rota[l-1]][l2];
                            ver1 -= matriz[j2][car[i].rota[j+1]];
                            ver1 += matriz[car[i].rota[j+1]][l2];
                            ver1 += matriz[j2][car[i].rota[l-1]];
                        }
                        else{
                        //    printf("\t\t\telse\n");
                            ver1 -= matriz[car[i].rota[j-1]][j2];
                            ver1 -= matriz[j2][car[i].rota[j+1]];

                            ver1 -= matriz[car[i].rota[l-1]][l2];
                            ver1 -= matriz[l2][car[i].rota[l+1]];

                            ver1 += matriz[car[i].rota[j-1]][l2];
                            ver1 += matriz[l2][car[i].rota[j+1]];

                            ver1 += matriz[car[i].rota[l-1]][j2];
                            ver1 += matriz[j2][car[i].rota[l+1]];
                        }

                        atualdif = (car[i].custo) - (ver1);
                     //   printf("\t\t\tcar[i].custo: %d - ver1: %d\n", car[i].custo, ver1);
                    //    printf("\t\t\tdif: %d vs atualdif: %d\n", dif.custo, atualdif);
                        if(atualdif > dif.custo){
                            flagMelhora = 1;
                            dif.custo = atualdif;
                            dif.carro1 = i;
                            dif.posiVertice2 = l;
                            dif.vertice2 = l2;
                            dif.posiVertice = j;
                            dif.vertice = j2;
                        }
                    }
                }
                
            }
        }
    }
 //   printf("teste\n");
    if(flagMelhora){
    //    printf("melhora exchange!!\n");
    //    printf("carro %d, vertice %d e vertice %d\n", dif.carro1, dif.vertice, dif.vertice2 );
        car[dif.carro1].custo = 0;

        m = car[dif.carro1].rota[dif.posiVertice];
        car[dif.carro1].rota[dif.posiVertice] = car[dif.carro1].rota[dif.posiVertice2];
        car[dif.carro1].rota[dif.posiVertice2] = m;

        for(m = 0; m < count[dif.carro1]; m++){
            car[dif.carro1].custo += matriz[car[dif.carro1].rota[m]][car[dif.carro1].rota[m+1]];
        }
        /*
        int custoSoma = 0;
        
        
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
        */
        shift(car,description, numVertices, matriz, demanda, count);

    }
}


void swap(veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda,int *count){
    printf("swap!\n");
    int i, j, j2, k, l, l2, m;
    int ver1, ver2, atualdif = 0;
    vnd dif;
    dif.custo = 0;
    int flagMelhora = 0;
    int jaVisitados[description.vehicles];
    for(i = 0; i < description.vehicles; i++){
    //    printf("carro: %d\n", i);
        for(j = 1; j < count[i]; j++){
        //    printf("\tvertice de posicao %d: %d\n",j, car[i].rota[j]);
            for(k = 0; k < description.vehicles; k++){
            //    printf("\t\tcarro: %d\n", k);
                for(l = 1; l < count[k] ; l++){
                //    printf("\t\t\tcarro: %d, vertice de posicao %d: %d, carro: %d, vertice de posicao %d: %d\n", i, j, car[i].rota[j], k, l, car[k].rota[l]);
                //    printf("\t\t\tdemanda do vertice do carro : %d vs capacidade do carro: %d\n", demanda[car[i].rota[j]]  ,  (car[k].cap + demanda[car[k].rota[l]]));
                //    printf("\t\t\tdemanda do vertice do carro : %d vs capacidade do carro: %d\n", demanda[car[k].rota[l]], (car[i].cap + demanda[car[i].rota[j]]));
                    if(i != k && demanda[car[i].rota[j]] <= (car[k].cap + demanda[car[k].rota[l]]) && demanda[car[k].rota[l]] <= (car[i].cap + demanda[car[i].rota[j]]) ){    
                        j2 = car[i].rota[j];// vertice em questao
                        l2 = car[k].rota[l];

                        //ALTERAR A ROTA DE ORIGEM
                        ver1 = car[i].custo;
                        ver1 -= matriz[car[i].rota[j-1]][j2];
                        ver1 -= matriz[j2][car[i].rota[j+1]];
                        ver1 += matriz[car[i].rota[j-1]][l2];
                        ver1 += matriz[l2][car[i].rota[j+1]];
                        

                        //ALTERAR A ROTA DE DESTINO
                        ver2 = car[k].custo;
                        ver2 -= matriz[car[k].rota[l-1]][l2];
                        ver2 -= matriz[l2][car[k].rota[l+1]];
                        ver2 += matriz[car[k].rota[l-1]][j2];
                        ver2 += matriz[j2][car[k].rota[l+1]];

                        atualdif = (car[i].custo + car[k].custo) - (ver2 + ver1);
                    //    printf("dif: %d vs atualdif: %d\n", dif.custo, atualdif);
                        if(atualdif > dif.custo){
                            flagMelhora = 1;
                            dif.custo = atualdif;
                            dif.carro1 = i;
                            dif.carro2 = k;
                            dif.posiVertice2 = l;
                            dif.vertice2 = l2;
                            dif.posiVertice = j;
                            dif.vertice = j2;
                        }
                    }
                }
            }
        }
    }
 //   printf("teste\n");
    if(flagMelhora){
    //    printf("melhora swap!!\n");
    //    printf("carro %d vertice %d e carro %d vertice %d\n", dif.carro1, dif.vertice, dif.carro2, dif.vertice2 );
        car[dif.carro1].cap = description.capacity;
        car[dif.carro2].cap = description.capacity;
        car[dif.carro1].custo = 0;
        car[dif.carro2].custo = 0;

        m = car[dif.carro1].rota[dif.posiVertice];
        car[dif.carro1].rota[dif.posiVertice] = car[dif.carro2].rota[dif.posiVertice2];
        car[dif.carro2].rota[dif.posiVertice2] = m;

        for(m = 0; m < count[dif.carro1]; m++){
            car[dif.carro1].cap -= demanda[car[dif.carro1].rota[m+1]];
            car[dif.carro1].custo += matriz[car[dif.carro1].rota[m]][car[dif.carro1].rota[m+1]];
        }

        for(m = 0; m < count[dif.carro2]; m++){
            car[dif.carro2].cap -= demanda[car[dif.carro2].rota[m+1]];
            car[dif.carro2].custo += matriz[car[dif.carro2].rota[m]][car[dif.carro2].rota[m+1]];
        }
        /*
        int custoSoma = 0;
        
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
        */
        shift(car,description, numVertices, matriz, demanda, count);

    }
    else exchange(car,description, numVertices, matriz, demanda, count);
}


void shift(veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda,int *count){
   printf("shift!!\n");
    int i, j, j2, k, l, l2, m;
    int ver1, ver2, atualdif = 0;
    vnd dif;
    dif.custo = 0;
    int flagMelhora = 0;
    for(i = 0; i < description.vehicles; i++){
     //   printf("carro: %d\n", i);
        for(j = 1; j < count[i]; j++){
        //    printf("\tvertice de posicao %d: %d\n",j, car[i].rota[j]);
            for(k = 0; k < description.vehicles; k++){
         //       printf("\t\tcarro: %d, demanda do vertice: %d vs capacidade do carro: %d\n", k, demanda[car[i].rota[j]], car[k].cap);
                if(i != k && demanda[car[i].rota[j]] <= car[k].cap){
                    for(l = 0 , l2 = 1; l2 < count[k] ; l++, l2++){
            //            printf("carro: %d, vertice de posicao %d: %d, carro: %d, demanda do vertice: %d vs capacidade do carro: %d, aresta %d - %d\n", i, j, car[i].rota[j], k, demanda[car[i].rota[j]], car[k].cap, car[k].rota[l], car[k].rota[l2]);

                        j2 = car[i].rota[j];// vertice em questao

                        //ALTERAR A ROTA DE ORIGEM
                        ver1 = car[i].custo;
                        ver1 -= matriz[car[i].rota[j-1]][j2];
                        ver1 -= matriz[j2][car[i].rota[j+1]];
                        ver1 += matriz[car[i].rota[j-1]][car[i].rota[j+1]];
                        

                        //ALTERAR A ROTA DE DESTINO
                        ver2 = car[k].custo;
                        ver2 -= matriz[car[k].rota[l]][car[k].rota[l2]];
                        ver2 += matriz[car[k].rota[l]][j2];
                        ver2 += matriz[j2][car[k].rota[l2]];

                        atualdif = (car[i].custo + car[k].custo) - (ver2 + ver1);
                //        printf("dif: %d vs atualdif: %d\n", dif.custo, atualdif);
                        if(atualdif > dif.custo){
                            
                            flagMelhora = 1;
                            dif.custo = atualdif;
                            dif.carro1 = i;
                            dif.carro2 = k;
                            dif.posiAresta1 = l;
                            dif.posiAresta2 = l2;
                            dif.posiVertice = j;
                            dif.vertice = j2;
                        }
                    }
                }
            }
        }
    }
 //   printf("teste\n");
    if(flagMelhora){
        printf("melhora shift!!\n");
    //    printf("carro %d vertice %d e carro %d em aresta %d-%d\n",dif.carro1, dif.posiVertice, dif.carro2, car[dif.carro2].rota[dif.posiAresta1], car[dif.carro2].rota[dif.posiAresta2] );
        car[dif.carro1].cap = description.capacity;
        car[dif.carro2].cap = description.capacity;
        car[dif.carro1].custo = 0;
        car[dif.carro2].custo = 0;
        for(m = dif.posiVertice; m <= count[dif.carro1]-1; m++){
        //    printf("vertice indo embora: %d\n", car[dif.carro1].rota[m] );
            car[dif.carro1].rota[m] = car[dif.carro1].rota[m+1];
        } 
        count[dif.carro1]--;

        for(m = 0; m < count[dif.carro1]; m++){
            car[dif.carro1].cap -= demanda[car[dif.carro1].rota[m+1]];
            car[dif.carro1].custo += matriz[car[dif.carro1].rota[m]][car[dif.carro1].rota[m+1]];
        }

        for(m = count[dif.carro2]+1; m > dif.posiAresta2; m--){
            car[dif.carro2].rota[m] = car[dif.carro2].rota[m-1];
        }
        car[dif.carro2].rota[m] = dif.vertice; 
        count[dif.carro2]++;

        for(m = 0; m < count[dif.carro2]; m++){
            car[dif.carro2].cap -= demanda[car[dif.carro2].rota[m+1]];
            car[dif.carro2].custo += matriz[car[dif.carro2].rota[m]][car[dif.carro2].rota[m+1]];
        }
        
        
        
        shift(car,description, numVertices, matriz, demanda, count);

    }
    else swap(car,description, numVertices, matriz, demanda, count);
    /*
    int custoSoma = 0;
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
    */
}
