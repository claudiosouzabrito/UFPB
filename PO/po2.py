'''
DISCIPLINA DE PESQUISA OPERACIONAL: PROJETO 2
PROFESSOR: TEOBALDO LEITE BULHOES JUNIOR"
ALUNOS:
  Caio Victor do Amaral Cunha Sarmento - 20170021332
  Claudio Souza Brito - 20170023696
  Gabriel Teixeira Patrício - 20170170889

Formato do input:

n =  num de Fabricas
m = numero de cidades
k = centro de distribuição intermediario
P = preço por tonelada
CC = custo de transporte centro -> cidade e fábrica -> cidade
CF = custo de transporte fábrica -> centro
distance_cf = Tabela capital/ fabrica
distance_cef = Tabela centro/ fabrica
distance_cc = Tabela capital/ centro
capMax = Capacidades maximas das fabricas, todas em uma linha
fcosts = Custos de producao, por tonelada, das fabricas, todos em uma linha
demMax = Demandas maximas das cidades, uma por linha
ccosts = Custos de usos dos centros, todos em uma linha
'''
from mip import Model, xsum, MAXIMIZE, BINARY, INTEGER, maximize

file = open("input4.txt", "r")
lines = file.readlines()

n = int(lines[0])
m = int(lines[1])
k = int(lines[2])
p = float(lines[3])
cc = float(lines[4])
cf = float(lines[5])

distance_cf = [] #distancia cidade-fabrica
distance_cef = [] #distancia centro-fabrica
distance_cc = [] #distancia cidade-centro

#Matrizes das distancias
# capital/ fabrica
for line in lines[6:(6+m)]:
    columns = [float(x) for x in line.split()]
    var_column = []
    for column in columns:
        var_column.append(column)
    distance_cf.append(var_column)

# centro/ fabrica
for line in lines[(6+m):(6+m+k)]:
    columns = [float(x) for x in line.split()]
    var_column = []
    for column in columns:
        var_column.append(column)
    distance_cef.append(var_column)

# capital/ centro
for line in lines[(6+m+k):(6+k + 2*m)]:
    columns = [float(x) for x in line.split()]
    var_column = []
    for column in columns:
        var_column.append(column)
    distance_cc.append(var_column)


capMax = []
capMax = list(map(float,lines[(6+k + 2*m)].split()))


fcosts = []
fcosts = list(map(float,lines[(7+k + 2*m)].split()))



demMax = []
for line in lines[(8+k + 2*m):(8+k + 3*m)]:
    demMax.append(float(line))


ccosts = []
ccosts = list(map(float,lines[(8+k + 3*m)].split()))


CMAX = 0
for i in range(n):
    CMAX = CMAX + capMax[i]

DMAX = 0
for j in range(m):
    DMAX = DMAX + demMax[j]

model = Model(sense=MAXIMIZE)


capReal = [0 for i in range(n)]                       #restricao 1
for i in range(n):                                                            #array de toneladas que deixa a fabrica [0,capMax]     
    capReal[i] = model.add_var(var_type=INTEGER, lb=0, ub=capMax[i])

demReal = [0 for j in range(m)]                       #restricao 2
for j in range(m):                                                           #array de toneladas que entram na cidade [0, demMax]  
    demReal[j] = model.add_var(var_type=INTEGER, lb=0, ub=demMax[j])

#matriz de toneladas fabrica -> cidade [0,capMax]     #restricao 3 parte 1
tonCF = [[model.add_var(var_type=INTEGER, lb=0, ub=capMax[i]) for i in range(n)] for j in range(m)]
#matriz de toneladas centro -> cidade [0, demMax]     #restricao 3 parte 2
tonCC = [[model.add_var(var_type=INTEGER, lb=0, ub=demMax[j]) for l in range(k)] for j in range(m)]
#matriz de toneladas fabrica -> centro [0,capMax]     #restricao 3 parte 3
tonCeF = [[model.add_var(var_type=INTEGER, lb=0, ub=capMax[i]) for i in range(n)] for l in range(k)]

cflag = [0 for l in range(k)]                         #restricao 4
for l in range(k):                                                           #array de flags dos centros [0,1]
    cflag[l] = model.add_var(var_type=INTEGER, lb=0, ub=1)                                           

for i in range(n):                                    #restricao 5
    model += xsum(tonCF[j][i] for j in range(m)) + xsum(tonCeF[l][i] for l in range(k) ) == capReal[i]

for j in range(m):                                    #restricao 6
    model += xsum(tonCF[j][i] for i in range(n)) + xsum(tonCC[j][l] for l in range(k) ) == demReal[j]

for l in range(k):                                    #restricao 7
    model += xsum(tonCeF[l][i] for i in range(n)) - xsum(tonCC[j][l] for j in range(m)) == 0

for l in range(k):                                    #restricao 8
    model += xsum(tonCeF[l][i] for i in range(n)) <= CMAX*cflag[l]

for l in range(k):                                    #restricao 9
    model += xsum(tonCC[j][l] for j in range(m))  <= DMAX*cflag[l]

#funcao objetivo 
model.objective = maximize(
    p*xsum(demReal[j] for j in range(m))                                            # Preco por tonelada * A demanda real de todas as cidades
    - xsum(capReal[i]*fcosts[i] for i in range(n))                                  # Custo de produção por tonelada de todas fabricas * Capacidade real na fabrica 
    - cc*xsum(tonCF[j][i]*distance_cf[j][i] for i in range(n) for j in range(m))    # Quantidades total de toneladas * a distancia dos trajetos fabrica -> cidade  * custo de transporte por caminhao
    - cc*xsum(tonCC[j][l]*distance_cc[j][l] for l in range(k) for j in range(m))    # Quantidades total de toneladas * a distancia dos trajetos centro -> cidade  * custo de transporte por caminhao
    - cf*xsum(tonCeF[l][i]*distance_cef[l][i] for i in range(n) for l in range(k))  # Quantidades total de toneladas * a distancia dos trajetos fabrica -> centro  * custo de transporte por caminhao
    - xsum(ccosts[l]*cflag[l] for l in range(k)))                                   # Flag * Custo do uso do centro

model.optimize()
print('Valor da solucao: ', model.objective_value)
print('')

for i in range(n):
    for j in range(m):
        print("toneladas da fabrica ", i, " para a cidade ", j, ": ", tonCF[j][i].x)
        print("custo de trajeto da fabrica", i, " para a cidade ", j, ": ", tonCF[j][i].x * distance_cf[j][i] * cc)
        print("")

for i in range(n):
    for l in range(k):
        print("toneladas da fabrica ", i, " para o centro ", l, ": ", tonCeF[l][i].x)
        print("custo de trajeto da fabrica ", i, " para o centro ", l, ": ", tonCeF[l][i].x * distance_cef[l][i] * cf)
        print("")

for l in range(k):
    for j in range(m):
        print("toneladas do centro ", l, " para a cidade ", j, ": ", tonCC[j][l].x)
        print("custo de trajeto do centro ", l, " para a cidade ", j, ": ", tonCC[j][l].x * distance_cc[j][l] * cc)
        print("")

for i in range(n):
    print("capacidade utilizada pela fabrica", i, " vs capacidade maxima:", capReal[i].x, "/", capMax[i])
    print("custo de producao da fabrica", i,":", capReal[i].x * fcosts[i] )
    print("")

for j in range(m):
    print("demanda saciada pela cidade", j, " vs demanda maxima:", demReal[j].x, "/", demMax[j])
    print("")

for l in range(k):
    print("flag do centro", l, ":", cflag[l].x)
    print("custo de uso do centro", l, ":", cflag[l].x * ccosts[l])
    print("")