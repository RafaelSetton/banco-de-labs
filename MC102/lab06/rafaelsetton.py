from typing import List, Iterator

# Funções Auxiliares


def le_vetor() -> List[int]:
    return list(map(int, input().split(",")))


def zip_(list1: List[int], list2: List[int], fill_list1: int = 0,
         fill_list2: int = 0) -> Iterator[tuple[int, int]]:
    if len(list1) < len(list2):
        list1 += [fill_list1] * (len(list2) - len(list1))
    else:
        list2 += [fill_list2] * (len(list1) - len(list2))
    return zip(list1, list2)


def sum_(lista: List[int]) -> int:
    s = 0
    for x in lista:
        s += x
    return s


# Funções Lab06


def soma_vetores(vetor1: List[int], vetor2: List[int]) -> List[int]:
    return [x + y for x, y in zip_(vetor1, vetor2)]


def subtrai_vetores(vetor1: List[int], vetor2: List[int]) -> List[int]:
    return [x - y for x, y in zip_(vetor1, vetor2)]


def multiplica_vetores(vetor1: List[int], vetor2: List[int]) -> List[int]:
    return [x * y for x, y in zip_(vetor1, vetor2, 1, 1)]


def divide_vetores(vetor1: List[int], vetor2: List[int]) -> List[int]:
    return [x // y for x, y in zip_(vetor1, vetor2, 0, 1)]


def multiplicacao_escalar(vetor: List[int], n: int) -> List[int]:
    return [x * n for x in vetor]


def n_duplicacao(vetor: List[int], n: int) -> List[int]:
    return vetor * n


def soma_elementos(vetor: List[int]) -> int:
    return sum_(vetor)


def produto_interno(vetor1: List[int], vetor2: List[int]) -> int:
    return sum_([x * y for x, y in zip_(vetor1, vetor2, 1, 1)])


def multiplica_todos(vetor1: List[int], vetor2: List[int]) -> List[int]:
    soma_v2 = sum_(vetor2)
    return [x * soma_v2 for x in vetor1]


def correlacao_cruzada(vetor: List[int], mascara: List[int]) -> List[int]:
    novo_vetor = []
    for i in range(len(vetor)-len(mascara)+1):
        correlacao = [vetor[i+j]*mascara[j] for j in range(len(mascara))]
        novo_vetor.append(sum_(correlacao))
    return novo_vetor


if __name__ == '__main__':
    vetor_atual = le_vetor()
    param: int | List[int]
    retorno: int | List[int] = vetor_atual

    while True:
        comando = input()
        if comando == "fim":
            exit()
        elif comando == "soma_elementos":
            exec(f"retorno = {comando}(vetor_atual)")
        else:
            if comando in ["multiplicacao_escalar", "n_duplicacao"]:
                param = int(input())
            else:
                param = le_vetor()

            exec(f"retorno = {comando}(vetor_atual, param)")

        if type(retorno) is int:
            vetor_atual = [retorno]
        else:
            assert type(retorno) is list
            vetor_atual = retorno

        print(vetor_atual)
