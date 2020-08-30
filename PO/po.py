'''
DISCIPLINA DE PESQUISA OPERACIONAL: PROJETO 1
PROFESSOR: TEOBALDO LEITE BULHOES JUNIOR
ALUNOS:
  Caio Victor do Amaral Cunha Sarmento - 20170021332
  Claudio Souza Brito - 20170023696
  Gabriel Teixeira Patrício - 20170170889
'''

from __future__ import print_function
from ortools.linear_solver import pywraplp


file = open("instance5.txt", "r")							#Abre o arquivo de entrada

lines = file.readlines()

vertices = int(lines[0])
arcs = int(lines[1])
origins = int(lines[2])                                           
escoadores = int(lines[3])

start_nodes = []
end_nodes = []
capacities =  [] 
supplies = [0] * vertices
unit_costs = []
var_arcos = [0] * (arcs + 1)
constraint = [0] * vertices


for line in lines[4:]:
    line = list(map(int, line.split(' ',)))
    
    start_nodes.append(line[0])
    end_nodes.append(line[1])
    capacities.append(line[2])
    unit_costs.append(0)

#transformando em PFCM
start_nodes.append(escoadores)
end_nodes.append(origins)
capacities.append(10000)  #"infinito kkkk"
unit_costs.append(-1)


# Adaptando para modelagem de programacao linear, e uso do solver de programacao linear
solver = pywraplp.Solver('LinearProgrammingExample',
                          pywraplp.Solver.GLOP_LINEAR_PROGRAMMING)

# Criando as variaveis(arcos) e limitando entre 0 e capacidade maxima (definida no problema).
for i in range(len(var_arcos)):
  var_arcos[i] = solver.NumVar(0, capacities[i], str(i))

# Definindo as restricoes, a soma dos fluxos que entra em um vertice eh igual a soma dos fluxoes que saem
for i in range(vertices):
  constraint[i] = solver.Constraint(0,0) 
  for j in range(len(start_nodes)):
    if(start_nodes[j] == i):
      constraint[i].SetCoefficient(var_arcos[j], -1)

  for k in range(len(end_nodes)):
    if(end_nodes[k] == i):
      constraint[i].SetCoefficient(var_arcos[k], 1)

# Criando funcao objetiva: somatorio de todos os fluxos dos arcos vezes o custo deles
objective = solver.Objective()
for i in range(len(var_arcos)):
  objective.SetCoefficient(var_arcos[i], unit_costs[i])
objective.SetMinimization()

solver.Solve()

opt_solution = 0
print("arcos nao nulos:")
for i in range(len(var_arcos)):
  opt_solution = opt_solution + unit_costs[i]*var_arcos[i].solution_value()
  if(var_arcos[i].solution_value() != 0):
    print("arco: ", start_nodes[i], "-> ", end_nodes[i], ": ", var_arcos[i].solution_value())

print('Solucao otimizada =', -1*opt_solution)

