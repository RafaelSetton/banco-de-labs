def main() -> None:
    #inteiro N
    linhas = int(input())
    comodo = [input().split() for i in range(linhas)]
    #posição inicial do robo
    posicao_atual = [0,0]
    imprime_comodo(comodo)
    sair = False
    
    while not sair:
        escaneia_ambiente(comodo, posicao_atual)
        e_ultima_linha = posicao_atual[0] == len(comodo) - 1
        e_ultima_coluna = posicao_atual[1] == len(comodo[0]) - 1
        e_primeira_coluna = posicao_atual[1] == 0
        indice_linha_par = posicao_atual[0] % 2 == 0
        #quando o robo estiver na ultima posicao do comodo, ele sai do loop
        sair = e_ultima_linha and ((e_ultima_coluna and indice_linha_par) or (e_primeira_coluna and not indice_linha_par))
    
    if len(comodo) % 2 == 0:
        finalizar(comodo, posicao_atual)


def imprime_comodo(comodo: list[list]) -> None:
    '''Printa o comodo formatado de maneira correta'''
    for linha in comodo:
        print(" ".join(linha))
    print()


def proxima_posicao(comodo: list[list], posicao: list[int]) -> list[int]:
    '''Pega a proxima posicao do robo baseado no caminho que ele deveria seguir'''
    linha, coluna = posicao
    # se a linha for par: esquerda pra direita
    if linha % 2 == 0:
        coluna += 1        
    else:
        coluna -= 1
    
    #se o robo extrapola pela direita
    if coluna >= len(comodo[0]):
        linha += 1
        coluna -= 1
    #se o robo extrapola pela esquerda
    elif coluna < 0:
        linha += 1
        coluna += 1
    
    return [linha, coluna]
 
               
def checar(comodo: list[list], posicao: list[int]) -> list[int]:
    '''Retorna a posição da sujeira se achar.
    Caso contrário, retorna a posição atual do robo'''
    linha, coluna = posicao
    if coluna != 0:
        if comodo[linha][coluna - 1] == "o":
            return [linha, coluna - 1]
    if linha != 0:
        if comodo[linha - 1][coluna] == "o":
            return [linha - 1, coluna]
    if coluna != len(comodo[linha]) - 1:
        if comodo[linha][coluna + 1] == "o":
            return [linha, coluna + 1]
    if linha != len(comodo) - 1:
        if comodo[linha + 1][coluna] == "o":
            return [linha + 1, coluna]
    
    return posicao


def escaneia_ambiente(comodo: list[list], posicao: list[int]) -> None:
    '''Procura sujeira nas adjacencias do robo. Se encontrar, entra no modo "limpando".
    Caso contrário, anda o robo e mostra a configuração atual do comodo.

    Para procurar sujeira nas adjacencias, o robo segue a ordem: esquerda, cima, direita e embaixo.
    '''
    linha, coluna = posicao
    posicao_sujeira = checar(comodo, posicao)
    prox_posicao = proxima_posicao(comodo, posicao)
    #se não encontrar sujeira, ou se ela já estiver no percurso natural
    #o robo anda normalmente
    if posicao_sujeira == posicao or posicao_sujeira == prox_posicao:
        linha_n, coluna_n = prox_posicao
        comodo[linha][coluna] = "."
        comodo[linha_n][coluna_n] = "r"
        posicao[0] = linha_n
        posicao[1] = coluna_n
        imprime_comodo(comodo)
    #seu percurso muda
    else:
        limpando(comodo, posicao, posicao_sujeira, posicao)
        
        
def limpando(comodo: list[list], posicao_atual: list[int],
            posicao_sujeira: list[int], posicao_inicial: list[int]) -> list[int]:
    '''Limpa as sujeiras, movendo o robo para posicao que estava a sujeira limpada.
    
    Se tiver sujeira nas adjacências, o robo continua nesse processo, até que a posicao_sujeira,
    devido ao "checar", seja igual a posicao atual do robo.'''
    if posicao_sujeira != posicao_atual:
        #tira o robo da posicao antiga
        posicao_antiga = posicao_atual
        comodo[posicao_antiga[0]][posicao_antiga[1]] = "."

        #coloca o robo na posicao atual
        posicao_atual = posicao_sujeira
        comodo[posicao_sujeira[0]][posicao_sujeira[1]] = "r"
        
        #procura sujeira a partir de sua nova posicao
        posicao_sujeira = checar(comodo, posicao_atual)
        imprime_comodo(comodo)
        posicao_atual = limpando (comodo, posicao_atual, posicao_sujeira, posicao_inicial)
    
    #quando nao tem mais sujeira nas adjacencias, faz o robo retornar
    #a primeira posicao que o limpando foi ativado.
    if posicao_inicial != posicao_atual:
        retornar_escaneamento(comodo, posicao_inicial, posicao_atual)
        posicao_atual = posicao_inicial
    
    return posicao_atual

 
def retornar_escaneamento(comodo, posicao_inicial, posicao_atual):
    '''Volta o robo para a posicao inicial antes de acionar o limpando.
    Se encontrar sujeira nas adjacencias, chama o limpando novamente.
    '''
    while posicao_inicial[1] != posicao_atual[1]:
        comodo[posicao_atual[0]][posicao_atual[1]] = "."
        if posicao_atual[1] > posicao_inicial[1]:
            posicao_atual[1] -= 1
        else:
            posicao_atual[1] += 1

        comodo[posicao_atual[0]][posicao_atual[1]] = "r"
        imprime_comodo(comodo)
        posicao = checar(comodo, posicao_atual)
        #se checar retorna uma posição diferente da atual: posicao recebe a posicao da sujeira encontrada
        if posicao != posicao_atual:
            #entra aqui quando encontra uma sujeira nas adjacências no caminho de volta
            posicao_atual = limpando(comodo, posicao_atual, posicao, posicao_inicial)
            
    while posicao_inicial[0] != posicao_atual[0]:
        comodo[posicao_atual[0]][posicao_atual[1]] = "."
        if posicao_atual[0] > posicao_inicial[0]:
            posicao_atual[0] -= 1
        else:
            posicao_atual[0] += 1
                
        comodo[posicao_atual[0]][posicao_atual[1]] = "r"
        imprime_comodo(comodo)
        posicao = checar(comodo, posicao_atual)
        #se checar retorna uma posição diferente da atual: posicao recebe a posicao da sujeira encontrada
        if posicao != posicao_atual:
            #entra aqui quando encontra uma sujeira nas adjacências no caminho de volta
            posicao_atual = limpando(comodo, posicao_atual, posicao, posicao_inicial)


def finalizar(comodo: list[list], posicao: list[int]) -> None:
    '''Quando temos uma quantidade de linhas pares, essa funcao mostra o robo retornando
    para a ultima posicao da matriz'''
    while not posicao[1] == len(comodo[0]) - 1:
        posicao[1] += 1
        comodo[posicao[0]][posicao[1] - 1] = "."
        comodo[posicao[0]][posicao[1]] = "r"
        imprime_comodo(comodo)


if __name__ == "__main__":
    main()
