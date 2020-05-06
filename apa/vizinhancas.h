#ifndef VIZINHANCAS_H
#define VIZINHANCAS_H
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

typedef struct{
    int custo;
    int posiVertice;
    int posiVertice2;
    int carro1;
    int carro2;
    int posiAresta1;
    int posiAresta2;
    int vertice;
    int vertice2;
}vnd;

void exchange(veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda,int *count);
void swap(veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda,int *count);
void shift(veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda,int *count);
#endif