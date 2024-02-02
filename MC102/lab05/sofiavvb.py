def main():
    genoma = input()
    while True:
        operacao = input().split()

        if operacao[0] == "reverter":
            i = min(int(operacao[1]), len(genoma))
            j = min(int(operacao[2]), len(genoma))
            genoma = reverter(genoma, i, j)

        elif operacao[0] == "transpor":
            i = min(int(operacao[1]), len(genoma))
            j = min(int(operacao[2]), len(genoma))
            k = min(int(operacao[3]), len(genoma))
            genoma = transpor(genoma, i, j, k)

        elif operacao[0] == "combinar":
            g = operacao[1]
            i = min(int(operacao[2]), len(genoma))
            genoma = combinar(genoma, g, i)

        elif operacao[0] == "concatenar":
            g = operacao[1]
            genoma = concatenar(genoma, g)

        elif operacao[0] == "remover":
            i = min(int(operacao[1]), len(genoma))
            j = min(int(operacao[2]), len(genoma))
            genoma = remover(genoma, i, j)

        elif operacao[0] == "transpor_e_reverter":
            i = min(int(operacao[1]), len(genoma))
            j = min(int(operacao[2]), len(genoma))
            k = min(int(operacao[3]), len(genoma))
            genoma = transpor_e_reverter(genoma, i, j, k)

        elif operacao[0] == "buscar":
            g = operacao[1]
            print(buscar(genoma, g))

        elif operacao[0] == "buscar_bidirecional":
            g = operacao[1]
            print(buscar_bidirecional(genoma, g))

        elif operacao[0] == "mostrar":
            mostrar(genoma)

        elif operacao[0] == "sair":
            break


def reverter(genoma, i, j):
    '''Reverte a subsequência [i, j] (de i até j, inclusive) do
genoma atual.

    Funciona para i e j sendo números inteiros positivos.

    Parâmetros:
    genoma -- string
    i -- número inteiro positivo
    j -- número inteiro positivo
    '''
    reversa = genoma[i:j+1]
    revertida = reversa[::-1]
    genoma = genoma[:i] + revertida + genoma[j+1:]
    return genoma


def transpor(genoma, i, j, k):
    '''Transpõe o genoma atual considerando os índices i, j, k, isto é, troca a
    posição da subsequência iniciada em i e terminada em j
    com a subsequência iniciada em j + 1 e terminada em k.

    Funciona para i, j e k sendo números inteiros positivos.

    Parâmetros:
    genoma -- string
    i -- número inteiro positivo
    j -- número inteiro positivo
    k -- número inteiro positivo
    '''
    subsequencia1 = genoma[i:j+1]
    subsequencia2 = genoma[j+1:k+1]
    genoma = genoma[:i] + subsequencia2 + subsequencia1 + genoma[k+1:]
    return genoma


def combinar(genoma, g, i):
    '''Combina o genoma atual com um novo genoma informado, inserindo esse
na i-ésima posição do atual.

    Funciona para i sendo número inteiro positivo.

    Parâmetros:
    genoma -- string
    g -- string
    i -- número inteiro positivo
    '''
    genoma = genoma[:i] + g + genoma[i:]
    return genoma


def concatenar(genoma, g):
    '''Adiciona ao final do genoma atual um novo genoma informado.

    Parâmetros:
    genoma -- string
    g -- string
    '''
    genoma = genoma + g
    return genoma


def remover(genoma, i, j):
    '''Remove a subsequência [i, j] do genoma atual considerando dois índices
    i e j informados.

    Funciona para i e j sendo números inteiros positivos

    Parâmetros:
    genoma -- string
    i -- número inteiro positivo
    j -- número inteiro positivo
    '''
    genoma = genoma[:i] + genoma[j+1:]
    return genoma


def transpor_e_reverter(genoma, i, j, k):
    '''Transpõe o genoma considerando os índices i, j, k e, em seguida,
o reverte considerando os índices i e k.

    Funciona para i, j e k sendo números inteiros positivos.

    Parâmetros:
    genoma -- string
    i -- número inteiro positivo
    j -- número inteiro positivo
    k -- número inteiro positivo
    '''
    genoma = transpor(genoma, i, j, k)
    genoma = reverter(genoma, i, k)
    return genoma


def buscar(genoma, g):
    '''Dado um genoma de busca, exibir na tela o número de vezes em que ele
ocorre no genoma atual.

    O genoma atual não sofre alterações.

    Parâmetros:
    genoma -- string
    g -- string
    '''
    return genoma.count(g)
    

def buscar_bidirecional(genoma, g):
    '''Dado um genoma de interesse, busca quantas vezes ele ocorre
no genoma atual ou em sua reversão.

    O genoma atual não sofre alterações.

    Parâmetros:
    genoma -- string
    g -- string
    '''
    return buscar(genoma, g) + buscar(genoma[::-1], g)
    

def mostrar(genoma):
    '''Exibe o genoma atual para o usuário.

    Parâmetros:
    genoma -- string
    '''
    print(genoma)


if __name__ == "__main__":
    main()
