def calcula_chave(texto_codificado: str, operador: str,
                  operando1: str, operando2: str) -> int:
    """
    Calcula o valor da chave de decodificação

    Parâmetros:
        texto_codificado: str - O texto a ser decodificado

    Retorno:
        int - O valor da chave calculada
    """
    index1 = 0
    index2 = 0

    for i in range(len(texto_codificado)):
        if texto_codificado[i] in operando1:
            index1 = i
            break
    for i in range(index1, len(texto_codificado)):
        if texto_codificado[i] in operando2:
            index2 = i
            break
    return int(eval(f"{index1}{operador}{index2}"))


def get_matches_for(operando: str) -> str:
    """
    Retorna os valores que devem ser buscados baseado no operando fornecido

    Parâmetros:
        operando: str - Uma string de um caractere, ou que esteja entre
        as seguintes possibilidades: "numero", "vogal", "consoante"

    Retorno:
        str: Uma string com todos os caracteres que devem ser buscados
    """
    mapeia = {
        "numero": "0123456789",
        "vogal": "aeiouAEIOU",
        "consoante": "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ"
    }

    return operando if len(operando) == 1 else mapeia[operando]


def main() -> None:
    operador = input()
    operando1 = get_matches_for(input())
    operando2 = get_matches_for(input())

    n_linhas = int(input())
    linhas = [input() for _ in range(n_linhas)]
    texto = "".join(linhas)
    tamanhos = [0]
    for linha in linhas:
        tamanhos.append(tamanhos[-1] + len(linha))

    chave = calcula_chave(texto, operador, operando1, operando2)
    print(chave)
    chave = chave % 95

    decodificado = ""
    for c in texto:
        new_ascii = ord(c) + chave
        if new_ascii > 126:
            # chave é positiva, então não acontece overflow por baixo
            new_ascii -= 95
        decodificado += chr(new_ascii)

    for i in range(1, len(tamanhos)):
        # Quebra as linhas com o mesmo tamanho das linhas de entrada
        print(decodificado[tamanhos[i-1]:tamanhos[i]])


if __name__ == '__main__':
    main()
