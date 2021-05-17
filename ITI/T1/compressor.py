import binascii
import copy

K = 9

def fileToBinaryText(path):
    file = open(path).read()
    return ' '.join(format(ord(i), 'd') for i in file).split() #alterar 0:08b

codificacao = fileToBinaryText("corpus16MB.txt")
# print(codificacao)

next = pow(2,8) #256

dicionario = {}
for i in range(0,256):
    dicionario[str(i)] = [str(i)] #alterar "{0:08b}".format(i)

# print(dicionario["4"])   #00000100 = 4 
fim = ''
indice = 0

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
                if indice + l != len(codificacao) and codificacao[indice+l] == valor[l]: 
                    #se eu n to na ultima letra da mensagem e a proxima letra da mensagem = proxima letra do valor no dicionario
                    freq += 1   # ma = ma
                else:
        #            print('\t\tacabou a coincidencia em %d' % freq)
                    break
        #    print('\tfreq = %d' % freq)
            if freq > bigFreq:
                bigFreq = freq
                bigKey = key
    fim = fim + bigKey + ' '  #LEMBRAR DE TIRAR O ' ' DEPOIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (indice + len(dicionario[bigKey])) != len(codificacao) and len(dicionario) < pow(2,K): #se a mensagem nao acabou e dicionario nao ta cheio
        #adicionar novos elementos no dicionario
        new = str(next)     #alterar "{0:08b}".format(i)
        dicionario[new] = copy.deepcopy(dicionario[bigKey]) #M
        dicionario[new].append(codificacao[indice + len(dicionario[bigKey])])  #append A
    #    print('novo indice no dicionario: %s -> [%s]' % (new, ','.join(map(str,dicionario[new]))))
        next += 1
    indice += len(dicionario[bigKey]) 

#ISSO AQUI EH SO PRINT
print('dicionario apos 255:')
listadict = []
for i in dicionario.keys():
    if int(i) >= 256:
        listadict.append(i)
listadict.sort()
for i in listadict:
    print('%s -> %s' %(i, ','.join(map(str,dicionario[i]))))
print('mensagem final: %s' % fim)  