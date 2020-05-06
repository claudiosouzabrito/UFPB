'''
GRAFICO DE GANHO DE TENSAO POR CLAUDIO DE SOUZA BRITO - 20170023696
'''



import math
import matplotlib.pyplot as plt

f1 = 20
f2 = 20000
Avmed = 200

f = [1, 20, 400, 8000, 20000, 160000] # essas serao as frequencias usadas para compor o eixo x

'''
essa eh a equacao modelo:

Av = Avmed / ( math.sqrt( 1 + (f1/f)**2 ) * math.sqrt( 1 + (f/f2)**2 ) )

esses sao os ganhos que compoem o eixo y:
'''

Av1 = Avmed / ( math.sqrt( 1 + (f1/1)**2 ) * math.sqrt( 1 + (1/f2)**2 ) )
Av2 = Avmed / ( math.sqrt( 1 + (f1/5)**2 ) * math.sqrt( 1 + (5/f2)**2 ) )
Av3 = Avmed / ( math.sqrt( 1 + (f1/10)**2 ) * math.sqrt( 1 + (10/f2)**2 ) )
Av4 = Avmed / ( math.sqrt( 1 + (f1/15)**2 ) * math.sqrt( 1 + (15/f2)**2 ) )
Av5 = Avmed / ( math.sqrt( 1 + (f1/20)**2 ) * math.sqrt( 1 + (20/f2)**2 ) )
Av6 = Avmed / ( math.sqrt( 1 + (f1/400)**2 ) * math.sqrt( 1 + (400/f2)**2 ) )
Av7 = Avmed / ( math.sqrt( 1 + (f1/8000)**2 ) * math.sqrt( 1 + (8000/f2)**2 ) )
Av8 = Avmed / ( math.sqrt( 1 + (f1/10000)**2 ) * math.sqrt( 1 + (10000/f2)**2 ) )
Av9 = Avmed / ( math.sqrt( 1 + (f1/12500)**2 ) * math.sqrt( 1 + (12500/f2)**2 ) )
Av10 = Avmed / ( math.sqrt( 1 + (f1/15000)**2 ) * math.sqrt( 1 + (15000/f2)**2 ) )
Av11 = Avmed / ( math.sqrt( 1 + (f1/17500)**2 ) * math.sqrt( 1 + (17500/f2)**2 ) )
Av12 = Avmed / ( math.sqrt( 1 + (f1/20000)**2 ) * math.sqrt( 1 + (20000/f2)**2 ) )

print(Av1)
print(Av2)
print(Av3)
print(Av4)
print(Av5)
print(Av6)
print(Av7)
print(Av8)
print(Av9)
print(Av10)
print(Av11)
print(Av12)


plt.plot(  [ 1,5,10,15, 20, 400, 8000,10000,12500,15000,17500, 20000] , [ Av1, Av2, Av3, Av4, Av5, Av6, Av7, Av8, Av9, Av10, Av11, Av12] )
plt.show()
