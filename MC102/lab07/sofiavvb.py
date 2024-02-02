def main():
    operacao = input()
    operando1 = input()
    operando2 = input()
    numero_linhas = int(input())
    lista_mensagem = []
    tamanho_linhas = []
    
    #organizando as entradas
    for i in range(numero_linhas):
        mensagem = list(input())
        lista_mensagem.extend(mensagem)
        tamanho_linhas.append(len(mensagem))

    chave = acha_chave(operando1, operando2, operacao, lista_mensagem)
    mensagem = list(descriptografa(lista_mensagem, chave))
    onde_quebrar = quebras_de_linha(tamanho_linhas)

    '''essa iteração é para ser possível quebrar as linhas da mensagem 
    decodificada'''
    for indice in onde_quebrar:
        mensagem[indice - 1:indice] = [mensagem[indice - 1], "\n"]

    print(chave)
    print("".join(mensagem))


def quebras_de_linha(lista: list[int]):
    '''Utiliza uma lista com os tamanhos das linhas
    de entrada para criar outra com os indices onde
    devemos inserir uma quebra de linha.

    Parâmetros:
    lista -- lista de inteiros

    Retorno:
    onde_quebrar --  lista de inteiros
    '''
    onde_quebrar = [0]*len(lista)
    onde_quebrar[0] = lista[0]
    for i in range(1, len(lista)):
        onde_quebrar[i] = onde_quebrar[i-1] + lista[i] + 1
    return onde_quebrar


def acha_operando(operando: str, lista_mensagem: list[str]):
    '''Dado as entradas, acha o operando com base nos
    marcadores dados(vogal, consoante, numero) ou os
    próprios caracteres

    Parâmetros:
    operando -- string
    lista_mensagem -- lista de strings

    Retorno:
    operando -- string
    '''
    vogais = "AaEeIiOoUu"
    numeros = "0123456789"
    consoantes = "BbCcDdFfGgHhJjKkLlMmNnPpQqRrSsTtVvWwXxYyZz"
    if operando == "vogal":
        for i in lista_mensagem:
            if i in vogais:
                return i
    elif operando == "numero":
        for i in lista_mensagem:
            if i in numeros:
                return i
    elif operando == "consoante":
        for i in lista_mensagem:
            if i in consoantes:
                return i
    else:
        return operando


def acha_chave(operando1: str, operando2: str,
               operacao: str, lista: list[str]):
    '''Calcula a chave baseado na operacao dada

    Parâmetros:
    operando1 -- string
    operando2 -- string
    operacao -- string
    lista_mensagem -- lista de strings

    Retorno:
    chave -- int
    '''
    index1 = lista.index(acha_operando(operando1, lista))
    index2 = lista.index(acha_operando(operando2, lista), index1)

    if operacao == "+":
        chave = index1 + index2
    elif operacao == "-":
        chave = index1 - index2
    else:
        chave = index1 * index2
    return chave


def descriptografa(lista: list[str], chave: int):
    '''Realiza a parte de decodificar a mensagem

    Parâmetros:
    lista -- lista de strings
    chave - int

    Retorno:
    mensagem - str
    '''
    mensagem = []
    for i in lista:
        decodifica = (ord(i) - 32 + chave) % 95 + 32
        revela = chr(decodifica)
        mensagem.append(revela)
    return "".join(mensagem)


if __name__ == "__main__":
    main()
