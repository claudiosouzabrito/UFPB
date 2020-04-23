#!/usr/bin/env python
# coding: utf-8

# In[1]:


arq = []
f = open("arq.txt", "r")
contfile = 0
q = f.read()
#print(q)
for i in q:
    contfile = contfile + 1
#print(contfile)
f = open("arq.txt", "r")
for i in range(contfile-1):
    q = f.readline()
   # print(q)
    if q != ' ' and q != '\n' and q != '':
        arq.append(int(q))


# In[2]:


#print(arq)


tam = arq.pop(0)
#print(tam)
#print(type(tam))
#arq


# In[3]:


quadros = []
faltas = 0
cont = 0
while len(arq) != 0 :
 #   print("quadros: ")
#    print(quadros)
    if (len(quadros) < tam) and not(arq[0] in quadros):
   #     print("falta de pagina: %d nao estava la" %arq[0])
   #     print("entrando: %d" %arq[0])
        quadros.append(arq.pop(0))
        faltas = faltas + 1
    else:
        if cont == tam: 
            cont = 0
   #         print("%d -> 0" %tam)
        if arq[0] in quadros:
    #        print("%d ja ta" %arq[0])
            arq.pop(0)
        else:
     #       print("falta de pagina: %d nao estava la" %arq[0])
            quadros[cont] = arq.pop(0)
            cont = cont + 1
            faltas = faltas + 1
    


# In[4]:


print("FIFO %d" %faltas)


# In[5]:


f = open("arq.txt", "r")
contfile = 0
q = f.read()
#print(q)
for i in q:
    contfile = contfile + 1
#print(contfile)
f = open("arq.txt", "r")
for i in range(contfile-1):
    q = f.readline()
#    print(q)
    if q != ' ' and q != '\n' and q != '':
        arq.append(int(q))

#print(arq)


tam = arq.pop(0)
#print(tam)
#print(type(tam))
#arq


# In[6]:


quadros = []
veri = []
faltas = 0
cont = 0
maxi = 0
posi = 0
while len(arq) != 0 :
  #  print("quadros: ")
  #  print(quadros)
    if (len(quadros) < tam) and not(arq[0] in quadros):
  #      print("falta de pagina: %d nao estava la" %arq[0])
  #      print("entrando: %d" %arq[0])
        quadros.append(arq.pop(0))
        faltas = faltas + 1
    else:
        if arq[0] in quadros:
   #         print("%d ja ta" %arq[0])
            arq.pop(0)
        else:
    #        print("falta de pagina: %d nao estava la" %arq[0])
     #       print(len(arq))
            for i in quadros:
                for j in arq:
                    if i == j:
                        break
                    cont = cont + 1
                veri.append(cont)
                cont = 0
      #      print(veri)
            for i in veri:
                if i > maxi:
                    maxi = i
                    posi = cont
                cont = cont + 1
            maxi = 0
            cont = 0
            quadros[posi] = arq.pop(0)
            faltas = faltas + 1
            del veri[0:len(veri)]


# In[7]:


print("OTM %d" %faltas)


# In[8]:


f = open("arq.txt", "r")
contfile = 0
q = f.read()
#print(q)
for i in q:
    contfile = contfile + 1
#print(contfile)
f = open("arq.txt", "r")
for i in range(contfile-1):
    q = f.readline()
 #   print(q)
    if q != ' ' and q != '\n' and q != '':
        arq.append(int(q))

#print(arq)


tam = arq.pop(0)
#print(tam)
#print(type(tam))
arq


# In[9]:


quadros = []
veri = []
faltas = 0
cont = 0
maxi = 0
posi = 0
while len(arq) != 0 :
    #print("quadros: ")
    #print(quadros)
    #print(veri)
    if (len(quadros) < tam) and not(arq[0] in quadros):
    #    print("falta de pagina: %d nao estava la" %arq[0])
    #    print("entrando: %d" %arq[0])
        veri.append(0)
        quadros.append(arq.pop(0))
        faltas = faltas + 1
    else:
        if arq[0] in quadros:
        #    print("%d ja ta" %arq[0])
            for i in quadros:
                if i == arq[0]:
                    break
                else: cont = cont + 1
            arq.pop(0)
            veri[cont] = 0
            cont = 0
        else:
        #    print("falta de pagina: %d nao estava la" %arq[0])
            for i in veri:
                if i > maxi:
                    maxi = i
                    posi = cont
                cont = cont + 1
            maxi = 0
            cont = 0
            quadros[posi] = arq.pop(0)
            veri[posi] = 0
            faltas = faltas + 1
    for i in veri: 
        veri[cont] = veri[cont] + 1
        cont = cont + 1
    cont = 0


# In[10]:


print("LRU %d" %faltas)


# In[ ]:





# In[ ]:




