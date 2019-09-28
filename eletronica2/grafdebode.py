'''
GRAFICO DE GANHO DE TENSAO EM DB POR CLAUDIO DE SOUZA BRITO - 20170023696
'''



import math
import matplotlib.pyplot as plt

f1 = 20
f2 = 2000000
Avmed = 150

f = [1, 5, 10, 15, 20, 400, 8000, 10000, 12500, 15000, 17500, 20000] # essas serao as frequencias usadas para compor o eixo x

'''
essa eh a equacao modelo:

Av = Avmed / ( math.sqrt( 1 + (f1/f)**2 ) * math.sqrt( 1 + (f/f2)**2 ) )

esses sao os ganhos que compoem o eixo y:
'''
'''
Av1 = Avmed / ( math.sqrt( 1 + (f1/0.1)**2 ) * math.sqrt( 1 + (0.1/f2)**2 ) )
Av1 = 20 * math.log10(Av1)

Av2 = Avmed / ( math.sqrt( 1 + (f1/0.2)**2 ) * math.sqrt( 1 + (0.2/f2)**2 ) )
Av2 = 20 * math.log10(Av2)

Av3 = Avmed / ( math.sqrt( 1 + (f1/0.5)**2 ) * math.sqrt( 1 + (0.5/f2)**2 ) )
Av3 = 20 * math.log10(Av3)
'''
Av4 = Avmed / ( math.sqrt( 1 + (f1/1)**2 ) * math.sqrt( 1 + (1/f2)**2 ) )
Av4 = 20 * math.log10(Av4)

Av5 = Avmed / ( math.sqrt( 1 + (f1/2)**2 ) * math.sqrt( 1 + (2/f2)**2 ) )
Av5 = 20 * math.log10(Av5)

Av6 = Avmed / ( math.sqrt( 1 + (f1/5)**2 ) * math.sqrt( 1 + (5/f2)**2 ) )
Av6 = 20 * math.log10(Av6)

Av7 = Avmed / ( math.sqrt( 1 + (f1/10)**2 ) * math.sqrt( 1 + (10/f2)**2 ) )
Av7 = 20 * math.log10(Av7)

Av8 = Avmed / ( math.sqrt( 1 + (f1/20)**2 ) * math.sqrt( 1 + (20/f2)**2 ) )
Av8 = 20 * math.log10(Av8)

Av9 = Avmed / ( math.sqrt( 1 + (f1/50)**2 ) * math.sqrt( 1 + (50/f2)**2 ) )
Av9 = 20 * math.log10(Av9)

Av10 = Avmed / ( math.sqrt( 1 + (f1/100)**2 ) * math.sqrt( 1 + (100/f2)**2 ) )
Av10 = 20 * math.log10(Av10)

Av11 = Avmed / ( math.sqrt( 1 + (f1/200)**2 ) * math.sqrt( 1 + (200/f2)**2 ) )
Av11 = 20 * math.log10(Av11)

Av12 = Avmed / ( math.sqrt( 1 + (f1/500)**2 ) * math.sqrt( 1 + (500/f2)**2 ) )
Av12 = 20 * math.log10(Av12)

Av13 = Avmed / ( math.sqrt( 1 + (f1/1000)**2 ) * math.sqrt( 1 + (1000/f2)**2 ) )
Av13 = 20 * math.log10(Av13)

Av14 = Avmed / ( math.sqrt( 1 + (f1/10000)**2 ) * math.sqrt( 1 + (10000/f2)**2 ) )
Av14 = 20 * math.log10(Av14)

Av15 = Avmed / ( math.sqrt( 1 + (f1/625000)**2 ) * math.sqrt( 1 + (625000/f2)**2 ) )
Av15 = 20 * math.log10(Av15)

Av16 = Avmed / ( math.sqrt( 1 + (f1/1000000)**2 ) * math.sqrt( 1 + (1000000/f2)**2 ) )
Av16 = 20 * math.log10(Av16)

Av17 = Avmed / ( math.sqrt( 1 + (f1/2000000)**2 ) * math.sqrt( 1 + (2000000/f2)**2 ) )
Av17 = 20 * math.log10(Av17)

Av18 = Avmed / ( math.sqrt( 1 + (f1/3000000)**2 ) * math.sqrt( 1 + (3000000/f2)**2 ) )
Av18 = 20 * math.log10(Av18)

Av19 = Avmed / ( math.sqrt( 1 + (f1/4000000)**2 ) * math.sqrt( 1 + (4000000/f2)**2 ) )
Av19 = 20 * math.log10(Av19)

Av20 = Avmed / ( math.sqrt( 1 + (f1/5000000)**2 ) * math.sqrt( 1 + (5000000/f2)**2 ) )
Av20 = 20 * math.log10(Av20)

Av21 = Avmed / ( math.sqrt( 1 + (f1/6000000)**2 ) * math.sqrt( 1 + (6000000/f2)**2 ) )
Av21 = 20 * math.log10(Av21)

Av22 = Avmed / ( math.sqrt( 1 + (f1/10000000)**2 ) * math.sqrt( 1 + (10000000/f2)**2 ) )
Av22 = 20 * math.log10(Av22)

'''
print(Av1)
print(Av2)
print(Av3)
'''
print(Av4)
print(Av5)
print(Av6)
print(Av7)
print(Av8)
print(Av9)
print(Av10)
print(Av11)
print(Av12)
print(Av13)
print(Av14)
print(Av15)
print(Av16)
print(Av17)
print(Av18)
print(Av19)
print(Av20)
print(Av21)
print(Av22)



plt.plot(  [  1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 10000, 625000, 1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 10000000] 
	     , [  Av4, Av5, Av6, Av7, Av8, Av9, Av10, Av11, Av12, Av13, Av14, Av15, Av16, Av17, Av18, Av19, Av20, Av21, Av22] )
plt.show()
