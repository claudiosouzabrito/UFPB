#ifndef HEURISTICA_H
#define HEURISTICA_H
#include "vizinhancas.h"
#include <time.h>

void ILS(  veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda, int *count);
void pertubacaoNivel1(  veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda, int *count);
int pertubacaoNivel2(  veiculo *car, info_test description, int numVertices, int matriz[][numVertices], int *demanda, int *count);

#endif