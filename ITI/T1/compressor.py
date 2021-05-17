# -- coding: UTF-8 --
import copy
import unicodedata
import time



def fileToBinaryText(path):
    file = open(path, encoding='ISO-8859-1').read()
    #file2 = unicodedata.normalize('NFKD', file).encode('ascii','ignore').decode('utf-8')
    return ' '.join(format(ord(i), 'd') for i in file).split() #alterar 08b

codificacao = fileToBinaryText("Disco Rígido Funcionando aberto.mp4")
#print(codificacao)

for K in range(9,17):
    start = time.time()
    fim = ''
    indice = 0
    nex = pow(2,8) #256
    dicionario = {}
    for i in range(0,256):
        dicionario[str(i)] = [str(i)] #alterar "{0:08b}".format(i)

    while indice < len(codificacao):
        letra = codificacao[indice]
    #    print('Byte da vez: ' + letra)
        bigKey = letra #chave
        bigFreq = 1 #frequencia de coincidencia 
        for key,valor in dicionario.items(): #eh pra achar coincidencias dentro do dicionario
             if letra == valor[0]:
            #    print('\tencontrou correspondente para em: %s -> [%s]' % (key,','.join(map(str,valor))))
                freq = 1
                for l in range(1,len(valor)): # l = numero entra 1 e o tamanho do valor atual no dicionario
                    if indice + l != len(codificacao) and codificacao[indice+l] == valor[l]:  #se eu n to na ultima letra da mensagem
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
        fim = fim + bigKey + ' '  #LEMBRAR DE TIRAR O ' ' DEPOIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        #print("%d + %d != %d and %d < %d" %(indice, len(dicionario[bigKey]), len(codificacao), len(dicionario), pow(2,K)))
        if ((indice + len(dicionario[bigKey])) != len(codificacao)) and (len(dicionario) < pow(2,K)): #se a mensagem nao acabou e dicionario nao ta cheio
            #adicionar novos elementos no dicionario
            new = str(nex)     #alterar "{0:08b}".format(i)
            dicionario[new] = copy.deepcopy(dicionario[bigKey]) #M
            dicionario[new].append(codificacao[indice + len(dicionario[bigKey])])  #append A
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
    #print('mensagem final: %s' % fim)
    if(K==9):
        tamanhoK9 = len(fim.split())
        print('K = 9')
        print('tamanho %d -> %d' % (len(codificacao),tamanhoK9))
        print('tempo de %f horas' %tempo)
    if(K==10):
        tamanhoK10 = len(fim.split())
        print('K = 10')
        print('tamanho %d -> %d' % (len(codificacao),tamanhoK10))
        print('tempo de %f horas' %tempo)
    if(K==11):
        tamanhoK11 = len(fim.split())
        print('K = 11')
        print('tamanho %d -> %d' % (len(codificacao),tamanhoK11))
        print('tempo de %f horas' %tempo)
    if(K==12):
        tamanhoK12 = len(fim.split())
        print('K = 12')
        print('tamanho %d -> %d' % (len(codificacao),tamanhoK12))
        print('tempo de %f horas' %tempo)
    if(K==13):
        tamanhoK13 = len(fim.split())
        print('K = 13')
        print('tamanho %d -> %d' % (len(codificacao),tamanhoK13))
        print('tempo de %f horas' %tempo)
    if(K==14):
        tamanhoK14 = len(fim.split())
        print('K = 14')
        print('tamanho %d -> %d' % (len(codificacao),tamanhoK14))
        print('tempo de %f horas' %tempo)
    if(K==15):
        tamanhoK15 = len(fim.split())
        print('K = 15')
        print('tamanho %d -> %d' % (len(codificacao),tamanhoK15))
        print('tempo de %f horas' %tempo)
    if(K==16):
        tamanhoK16 = len(fim.split())
        print('K = 16')
        print('tamanho %d -> %d' % (len(codificacao),tamanhoK16))
        print('tempo de %f horas' %tempo)
