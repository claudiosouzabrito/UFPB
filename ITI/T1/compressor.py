import binascii
import copy

K = 9

def fileToBinaryText(path):
    file = open(path).read()
    return ' '.join(format(ord(i), 'd') for i in file).split() #alterar 0:08b

codificacao = fileToBinaryText("input.txt")
print(codificacao)

next = pow(2,8) #256

dicionario = {}
for i in range(0,256):
    dicionario[str(i)] = [str(i)] #alterar "{0:08b}".format(i)

fim = ''
indice = 0

while indice < len(codificacao):
    i = codificacao[indice]
    print('Byte da vez: ' + i)
    bigKey = i
    bigFreq = 1
    for j,k in dicionario.items():
         if i == k[0]:
            print('\tencontrou correspondente para em: %s -> [%s]' % (j,','.join(map(str,k))))
            freq = 1
            for l in range(1,len(k)):
                if indice + l != len(codificacao) and codificacao[indice+l] == k[l]:
                    freq += 1
                else:
                    print('\t\tacabou a coincidencia em %d' % freq)
                    break
            print('\tfreq = %d' % freq)
            if freq > bigFreq:
                bigFreq = freq
                bigKey = j
    fim = fim + bigKey + ' '
    if (indice + 1) != len(codificacao):
        new = str(next)     #alterar "{0:08b}".format(i)
        dicionario[new] = copy.deepcopy(dicionario[bigKey])
        dicionario[new].append(codificacao[indice + len(dicionario[bigKey])])
        print('novo indice no dicionario: %s -> [%s]' % (new, ','.join(map(str,dicionario[new]))))
        next += 1
    indice += len(dicionario[bigKey])


print(fim)
    




        # if i in dicionario.values():
        #     # print('tem ' + i +' no dicionario')
        #     fim = fim + i

# print('fim = ' + fim)
