def writeFile(path, texto):
    file = open(path, "wb")
    file.write(texto)

def binaryTextTofile(text):
    textArray = bytearray(text, "utf8")
    byteList = []
    for byte in textArray:
        byteList.append(bin(byte))
    return byteList

arr = [97]                 #ISSO AQUI VAI SER MASSA NO FUTURO KKKKK IMAGINA TRUNKS CHEGANDO COM UM ARRAY DE 98 CASAS PRA MATAR O CELL 
format = bytearray(arr)    
writeFile("outoputo.txt", format)

# decodificacao = binaryTextTofile(codificacao)
# print(decodificacao)