
# -- coding: UTF-8 --
import copy
import unicodedata
import time



def fileToBinaryText(path):
    file = open(path, encoding='ISO-8859-1').read()
    #file2 = unicodedata.normalize('NFKD', file).encode('ascii','ignore').decode('utf-8')
    return ' '.join(format(ord(i), 'd') for i in file).split() #alterar 08b

mensagem = fileToBinaryText("input.txt")
#print(mensagem)

def Kfunction(K, codificado, codif, tempo):
    tamanhoK = len(codificado)
    print('K =', K)
    print('tamanho %d -> %d' % (len(codif),tamanhoK))
    print('tempo de %f horas' %tempo)
    
    print('mensagem codificada:')
    print(codificado)

    #print(type(codificado_k))
    #print(type(codificado))
    
    #arquivo = open("output_k%s.txt" %K, "w")
    #arquivo.write(codificado_k)
    #arquivo.close()

K = 9
start = time.time()
codificado = []
indice = 0
nex = pow(2,8) #256
dicionario = {}
for i in range(0,256):
    dicionario[str(i)] = [str(i)] #alterar "{0:08b}".format(i)

while indice < len(mensagem):
    letra = mensagem[indice]
#    print('Byte da vez: ' + letra)
    bigKey = letra #chave
    bigFreq = 1 #frequencia de coincidencia 
    for key,valor in dicionario.items(): #eh pra achar coincidencias dentro do dicionario
         if letra == valor[0]:
        #    print('\tencontrou correspondente para em: %s -> [%s]' % (key,','.join(map(str,valor))))
            freq = 1
            for l in range(1,len(valor)): # l = numero entra 1 e o tamanho do valor atual no dicionario
                if indice + l != len(mensagem) and mensagem[indice+l] == valor[l]:  #se eu n to na ultima letra da mensagem
                     #a proxima letra da mensagem = proxima letra do valor no dicionario
                    freq += 1   # ma = ma
                else:
                    freq = 1
        #            print('\t\tacabou a coincidencia em %d' % freq)
                    break
        #    print('\tfreq = %d' % freq)
            if freq > bigFreq:
                bigFreq = freq
                bigKey = key
    codificado.append(int(bigKey))  #LEMBRAR DE TIRAR O ' ' DEPOIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    #print("%d + %d != %d and %d < %d" %(indice, len(dicionario[bigKey]), len(mensagem), len(dicionario), pow(2,K)))
    if ((indice + len(dicionario[bigKey])) != len(mensagem)) and (len(dicionario) < pow(2,K)): #se a mensagem nao acabou e dicionario nao ta cheio
        #adicionar novos elementos no dicionario
        new = str(nex)     #alterar "{0:08b}".format(i)
        dicionario[new] = copy.deepcopy(dicionario[bigKey]) #M
        dicionario[new].append(mensagem[indice + len(dicionario[bigKey])])  #append A
    #    print('novo indice no dicionario: %s -> [%s]' % (new, ','.join(map(str,dicionario[new]))))
        nex += 1
    indice += len(dicionario[bigKey]) 

end = time.time()
tempo = (end - start)/3600 

#ISSO AQUI EH SO PRINT
#print('dicionario apos 255:')
#listadict = []
#for i in dicionario.keys():
#    if int(i) >= 256:
#        listadict.append(i)
#listadict.sort()
#for i in listadict:
#    print('%s -> %s' %(i, ','.join(map(str,dicionario[i]))))
if(K == 9):
    Kfunction(9, codificado, mensagem, tempo)
if(K == 10):
    Kfunction(10, codificado, mensagem, tempo)
if(K == 11):
    Kfunction(11, codificado, mensagem, tempo)
if(K == 12):
    Kfunction(12, codificado, mensagem, tempo)
if(K == 13):
    Kfunction(13, codificado, mensagem, tempo)
if(K == 14):
    Kfunction(14, codificado, mensagem, tempo)
if(K == 15):
    Kfunction(15, codificado, mensagem, tempo)
if(K == 16):
    Kfunction(16, codificado, mensagem, tempo)
    

K += 1 