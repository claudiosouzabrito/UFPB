#ifndef CONSTRUTIVA_H
#define CONSTRUTIVA_H
#include "heuristica.h"

typedef struct{
    int pai;
    int key;
    int demanda;
}vertice;

int createRota(  veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda, int *count);
void Dijkstra(int numVertices, vertice *vertice, veiculo *car, info_test description, int matriz[][numVertices], int *demanda, int *count);
#endif