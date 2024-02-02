genoma = input()

def reverter(params):
    global genoma
    i, j = map(int, params)
    if j > len(genoma):
        j = len(genoma)-1
    if i > len(genoma):
        return
    genoma = genoma[:i] + genoma[i:j+1][::-1] + genoma[j+1:]

def transpor(params):
    global genoma
    i, j, k = map(int, params)
    if k > len(genoma):
        k = len(genoma)-1
    if i > len(genoma) or j > len(genoma):
        return
    genoma = genoma[:i] + genoma[j+1:k+1] + genoma[i:j+1] + genoma[k+1:]

def combinar(params):
    global genoma
    g = params[0]
    i = int(params[1])
    genoma = genoma[:i] + g + genoma[i:]

def concatenar(params):
    global genoma
    g = params[0]
    genoma += g

def remover(params):
    global genoma
    i, j = map(int, params)
    genoma = genoma[:i] + genoma[j+1:]

def transpor_e_reverter(params):
    global genoma
    i, j, k = map(int, params)
    transpor([i, j, k])
    reverter([i, k])

def buscar(params):
    global genoma
    g = params[0]
    print(genoma.count(g))

def buscar_bidirecional(params):
    global genoma
    g = params[0]
    print(genoma.count(g) + genoma.count(g[::-1]))

def mostrar(params):
    print(genoma)

def sair(params):
    exit()

while True:
    comando, *parametros = input().split()
    exec(f"{comando}({parametros})")
        