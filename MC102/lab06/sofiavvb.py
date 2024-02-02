def main() -> None:
    lista_vetor = input().split(',')
    vetor = inteira_vetor(lista_vetor)

    while True:
        operacao = input()

        if operacao == "soma_vetores":
            lista_vetor2 = input().split(',')
            vetor2 = inteira_vetor(lista_vetor2)
            vetor = soma_vetores(vetor, vetor2)
            print(vetor)

        elif operacao == "subtrai_vetores":
            lista_vetor2 = input().split(',')
            vetor2 = inteira_vetor(lista_vetor2)
            vetor = subtrai_vetores(vetor, vetor2)
            print(vetor)

        elif operacao == "multiplica_vetores":
            lista_vetor2 = input().split(',')
            vetor2 = inteira_vetor(lista_vetor2)
            vetor = multiplica_vetores(vetor, vetor2)
            print(vetor)

        elif operacao == "divide_vetores":
            lista_vetor2 = input().split(',')
            vetor2 = inteira_vetor(lista_vetor2)
            vetor = divide_vetores(vetor, vetor2)
            print(vetor)

        elif operacao == "multiplicacao_escalar":
            escalar = int(input())
            vetor = multiplicacao_escalar(vetor, escalar)
            print(vetor)

        elif operacao == "n_duplicacao":
            n = int(input())
            vetor = n_duplicacao(vetor, n)
            print(vetor)

        elif operacao == "soma_elementos":
            vetor = [soma_elementos(vetor)]
            print(vetor)

        elif operacao == "produto_interno":
            lista_vetor2 = input().split(',')
            vetor2 = inteira_vetor(lista_vetor2)
            vetor = [produto_interno(vetor, vetor2)]
            print(vetor)

        elif operacao == "multiplica_todos":
            lista_vetor2 = input().split(',')
            vetor2 = inteira_vetor(lista_vetor2)
            vetor = multiplica_todos(vetor, vetor2)
            print(vetor)

        elif operacao == "correlacao_cruzada":
            lista_mascara = input().split(',')
            mascara = inteira_vetor(lista_mascara)
            vetor = correlacao_cruzada(vetor, mascara)
            print(vetor)

        elif operacao == "fim":
            break


def inteira_vetor(lista_vetor: list[str]) -> list[int]:
    ''' Transforma os elementos de uma lista de str para int.

    Parâmetros:
    lista_vetor -- lista de strings

    Retorno:
    vetor -- lista de inteiros
    '''
    vetor = []
    for i in lista_vetor:
        vetor.append(int(i))
    return vetor


def adiciona_zero(vetor1: list[int], vetor2: list[int]) -> list[int]:
    ''' Adiciona 0's no menor vetor,
    para equiparar vetores de tamanhos diferentes.

    Parâmetros:
    vetor1 -- lista de inteiros
    vetor2 -- lista de inteiros

    Retorno:
    vetor1 ou vetor2 -- listas de inteiros
    '''
    if len(vetor1) < len(vetor2):
        for k in range(len(vetor2) - len(vetor1)):
            vetor1.append(0)
        return vetor1
    elif len(vetor1) > len(vetor2):
        for k in range(len(vetor1) - len(vetor2)):
            vetor2.append(0)
        return vetor2
    return vetor1


def adiciona_um(vetor1: list[int], vetor2: list[int]) -> list[int]:
    ''' Adiciona 1's no menor vetor, para
    equiparar vetores de tamanhos diferentes.

    Parâmetros:
    vetor1 -- lista de inteiros
    vetor2 -- lista de inteiros

    Retorno:
    vetor1 ou vetor2 -- listas de inteiros
    '''
    if len(vetor1) < len(vetor2):
        for k in range(len(vetor2) - len(vetor1)):
            vetor1.append(1)
        return vetor1
    elif len(vetor1) > len(vetor2):
        for k in range(len(vetor1) - len(vetor2)):
            vetor2.append(1)
        return vetor2
    return vetor1


def soma_vetores(vetor1: list[int], vetor2: list[int]) -> list[int]:
    '''Realiza a soma de elemento a elemento de dois vetores.

    Caso os vetores tenham tamanhos diferentes, adiciona 0's
    ao final do menor vetor, usando a função "adiciona_zero".

    Parâmetros:
    vetor1 -- lista de inteiros
    vetor2 -- lista de inteiros

    Retorno:
    resultado -- listas de inteiros
    '''
    resultado = []
    if len(vetor1) > len(vetor2):
        vetor2 = adiciona_zero(vetor1, vetor2)
    elif len(vetor1) < len(vetor2):
        vetor1 = adiciona_zero(vetor1, vetor2)

    for i in range(len(vetor1)):
        resultado.append(vetor1[i] + vetor2[i])
    return resultado


def subtrai_vetores(vetor1: list[int], vetor2: list[int]) -> list[int]:
    '''Realiza a subtração de elemento a elemento de dois vetores.

    Caso os vetores tenham tamanhos diferentes, adiciona 0's
    ao final do menor vetor, usando a função "adiciona_zero".

    Parâmetros:
    vetor1 -- lista de inteiros
    vetor2 -- lista de inteiros

    Retorno:
    resultado -- listas de inteiros
    '''
    resultado = []
    if len(vetor1) > len(vetor2):
        vetor2 = adiciona_zero(vetor1, vetor2)
    elif len(vetor1) < len(vetor2):
        vetor1 = adiciona_zero(vetor1, vetor2)

    for i in range(len(vetor1)):
        resultado.append(vetor1[i] - vetor2[i])
    return resultado


def multiplica_vetores(vetor1: list[int], vetor2: list[int]) -> list[int]:
    '''Realiza a multiplicação elemento a elemento de dois vetores.

    Caso os vetores tenham tamanhos diferentes, adiciona 1's
    ao final do menor vetor, usando a função "adiciona_um".

    Parâmetros:
    vetor1 -- lista de inteiros
    vetor2 -- lista de inteiros

    Retorno:
    resultado -- listas de inteiros
    '''
    resultado = []
    if len(vetor1) > len(vetor2):
        vetor2 = adiciona_um(vetor1, vetor2)
    elif len(vetor1) < len(vetor2):
        vetor1 = adiciona_um(vetor1, vetor2)

    for i in range(len(vetor1)):
        multiplica = vetor1[i] * vetor2[i]
        resultado.append(multiplica)
    return resultado


def divide_vetores(vetor1: list[int], vetor2: list[int]) -> list[int]:
    '''Realiza a divisão inteira (//) elemento a elemento de dois vetores.

    Caso os vetores tenham tamanhos diferentes, adiciona 0's ao
    final se o vetor1 for o menor, usando a função "adiciona_zero".
    Se o vetor2 for menor, adiciona 1's ao  final, usando a função
    "adiciona_um".

    Parâmetros:
    vetor1 -- lista de inteiros
    vetor2 -- lista de inteiros

    Retorno:
    resultado -- listas de inteiros
    '''
    resultado = []
    if len(vetor1) > len(vetor2):
        vetor2 = adiciona_um(vetor1, vetor2)
    elif len(vetor1) < len(vetor2):
        vetor1 = adiciona_zero(vetor1, vetor2)

    for i in range(len(vetor1)):
        resultado.append(vetor1[i] // vetor2[i])
    return resultado


def multiplicacao_escalar(vetor: list[int], escalar: int) -> list[int]:
    '''Multiplica cada elemento por um escalar.

    Parâmetros:
    vetor -- lista de inteiros
    escalar -- escalar inteiro

    Retorno:
    resultado -- listas de inteiros
    '''
    resultado = []
    for i in range(len(vetor)):
        resultado.append(vetor[i] * escalar)
    return resultado


def n_duplicacao(vetor: list[int], n: int) -> list[int]:
    '''Duplica o vetor n ≥ 0 vezes.

    Se n for zero, retorna uma lista vazia.

    Parâmetros:
    vetor -- lista de inteiros
    n -- escalar inteiro

    Retorno:
    resultado -- listas de inteiros
    '''
    resultado: list[int] = []
    if n == 0:
        return resultado
    else:
        resultado.extend(vetor * n)
    return resultado


def soma_elementos(vetor: list[int]) -> int:
    '''Soma todos os elementos do um vetor.

    Parâmetros:
    vetor -- lista de inteiros

    Retorno:
    soma -- número inteiro
    '''
    soma = 0
    for i in range(len(vetor)):
        soma += vetor[i]
    return soma


def produto_interno(vetor1: list[int], vetor2: list[int]) -> int:
    '''Multiplica elemento a elemento e depois soma o resultado.

    Caso os vetores tenham tamanhos diferentes, adiciona 1's
    ao final do vetor menor, usando a função "adiciona_um".

    Parâmetros:
    vetor1 -- lista de inteiros
    vetor2 -- lista de inteiros

    Retorno:
    resultado --  número inteiro
    '''
    produto = 0
    resultado = 0
    if len(vetor1) > len(vetor2):
        vetor2 = adiciona_um(vetor1, vetor2)
    elif len(vetor1) < len(vetor2):
        vetor1 = adiciona_um(vetor1, vetor2)

    for i in range(len(vetor1)):
        produto = vetor1[i] * vetor2[i]
        resultado += produto
    return resultado


def multiplica_todos(vetor1: list[int], vetor2: list[int]) -> list[int]:
    '''Multiplica cada elemento do primeiro vetor por todos os elementos
    do segundo vetor e soma o resultado.

    Parâmetros:
    vetor1 -- lista de inteiros
    vetor2 -- lista de inteiros

    Retorno:
    resultado --  lista de inteiros
    '''
    resultado = []
    for i in range(len(vetor1)):
        produto, soma = 0, 0
        for j in range(len(vetor2)):
            produto = vetor1[i] * vetor2[j]
            soma += produto
        resultado.append(soma)
    return resultado


def correlacao_cruzada(vetor1: list[int], mascara: list[int]) -> list[int]:
    '''Utiliza uma máscara (um vetor menor), que
    caminha pelo vetor calculando um produto interno.

    O vetor resultante tem um tamanho menor que
    a entrada.

    Parâmetros:
    vetor1 -- lista de inteiros
    mascara -- lista de inteiros

    Retorno:
    resultado --  lista de inteiros
    '''
    resultado = []
    for i in range(len(vetor1) - len(mascara) + 1):
        resultado.append(produto_interno(vetor1[i:len(mascara) + i], mascara))
    return resultado


if __name__ == "__main__":
    main()
