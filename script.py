# executar no terminal (Ctrl+Alt+T)
# python3 script.py
import dolfin as df
from dolfin import *
import numpy as np
from mshr import *
import matplotlib.pyplot as plt

# definição do dominio
L = 50.0
H = 10.0
R  = Rectangle(Point(  0.0,    0.0      ), Point(L,      H))
R1 = Rectangle(Point(2/8*L,  ), Point(1/2*L,1/2*H))
R2 = Rectangle(Point(0.0,0.0      ), Point(1/2*L,1/2*H))

E3 = Circle(Point((2/8*L,1/3*H)), 2/8*H)
E4 = Circle(Point((6/8*L,1/2*H)), 2/8*H)

omega = R - E3 - E4
malha = generate_mesh(omega, 164)
#plot(malha) # para ver a malha de elementos
#plt.show() # para ver a malha de elementos


# definição de classes para dizer onde estão as fronteiras
class fronteira_esq(SubDomain):
	def inside(self, x, on_boundary):
		return on_boundary and near(x[0],0)
class fronteira_dir(SubDomain):
	def inside(self, x, on_boundary):
		return on_boundary and near(x[0],L)
class fronteira_parede(SubDomain):
	def inside(self, x, on_boundary):
		paredes=near(x[1],0) or near(x[1],H) or (0.0<x[0] and x[0]<L)
		return on_boundary and paredes

# define objetos e marca com uma etiqueta
marca={"fronteira_parede": 1, "fronteira_esq": 2, "fronteira_dir":3}
fronteira = MeshFunction("size_t", malha, 1)
fronteira_esq=fronteira_esq()
fronteira_esq.mark(fronteira,marca["fronteira_esq"])
fronteira_dir=fronteira_dir()
fronteira_dir.mark(fronteira,marca["fronteira_dir"])
fronteira_parede=fronteira_parede()
fronteira_parede.mark(fronteira,marca["fronteira_parede"])

# parametros do MEF (não mudar)
ContinuousGalerkin="CG"
V=VectorElement(ContinuousGalerkin,triangle,2)
P=FiniteElement(ContinuousGalerkin,triangle,1)
W=FunctionSpace(malha,V*P)
w=Function(W)

# define os valores da velocidade e pressão na fronteira
velocidade_zero=Constant((0.0,0.0))
condicao_parede=DirichletBC(W.sub(0),velocidade_zero,fronteira,marca["fronteira_parede"])
pressao_esq=Constant(8.0)
condicao_esq=DirichletBC(W.sub(1),pressao_esq,fronteira,marca["fronteira_esq"])
pressao_dir=Constant(0.0)
condicao_dir=DirichletBC(W.sub(1),pressao_dir,fronteira,marca["fronteira_dir"])
condicao_fronteira=[condicao_parede, condicao_esq, condicao_dir]

# parametros do MEF (não mudar)
(u,p)=TrialFunctions(W)
(v,q)=TestFunctions(W)
dx=Measure("dx", domain=malha, subdomain_data=fronteira)
ds=Measure("ds", domain=malha, subdomain_data=fronteira)
n=FacetNormal(malha)
force=Constant((0.0,0.0))
a=inner(grad(u),grad(v))*dx - p*div(v)*dx + q*div(u)*dx
L=inner(force,v)*dx-pressao_esq*inner(n,v)*ds(marca["fronteira_esq"])-pressao_dir*inner(n,v)*ds(marca["fronteira_dir"])

# cálculo da solução (não mudar)
solve(a==L,w,condicao_fronteira)
(u,p)=w.split(True)

# grava em arquivos a velocidade e pressao
plot(u,title="Velocidade")
plt.savefig('vel.png')
plot(p,title="Pressao")
plt.savefig('press.png')

def magnitude(vec):
	return sqrt(vec**2)

plot(magnitude(u),title="Modulo da velocidade") # Object cannot be plotted directly, projecting to piecewise linears.
#plt.show()
plt.savefig('nvel.png')
