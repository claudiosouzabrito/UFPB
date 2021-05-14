import binascii
def fileToBinaryText(path):
    file = open(path).read()
    return ''.join(format(ord(i), '08b') for i in file)

def binaryTextTofile(text):
    textArray = bytearray(text, "utf8")
    byteList = []
    for byte in textArray:
        byteList.append(bin(byte))
    return byteList

def writeFile(path, texto):
    file = open(path, "wb")
    file.write(texto)

codificacao = fileToBinaryText("input.txt")
print(codificacao)
decodificacao = binaryTextTofile(codificacao)
print(decodificacao)

arr = [97] #COLOCAR EM NUMEROS
format = bytearray(arr)
writeFile("output.txt", format)

