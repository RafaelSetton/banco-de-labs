def main() -> None: 

    quantidade = int(input())
    filmes = {}

    for _ in range(quantidade):
        filme = input()
        filmes[filme] = {"filme que causou mais bocejos": 0,
                         "filme que foi mais pausado": 0,
                         "filme que mais revirou olhos": 0,
                         "filme que não gerou discussão nas redes sociais": 0,
                         "enredo mais sem noção": 0}

    avaliacoes = int(input())
    somas = {}
    avaliadores = {}
    medias = {}

    for _ in range(avaliacoes):
        informacoes = input().split(",")
        categoria = informacoes[1].strip()
        filme = informacoes[2].strip()
        nota = int(informacoes[3])

    # dicionario que guarda as somas das notas que
    # cada filme recebe em cada categoria
        if categoria not in somas:
            somas[categoria] = {}

        if filme in somas[categoria]:
            somas[categoria][filme] += nota
        else:
            somas[categoria][filme] = nota
    # dicionario que guarda quantos avaliadores avaliaram cada filme
        if categoria not in avaliadores:
            avaliadores[categoria] = {}

        if filme in avaliadores[categoria]:
            avaliadores[categoria][filme] += 1
        else:
            avaliadores[categoria][filme] = 1

# dicionario que guarda as medias das notas recebidas por cada filme
    for categoria in somas:
        medias[categoria] = {}
        for filme in somas[categoria]:
            medias[categoria][filme] = somas[categoria][filme]

    for categoria in avaliadores:
        for filme in avaliadores[categoria]:
            medias[categoria][filme] /= avaliadores[categoria][filme]
# saidas
    print("#### abacaxi de ouro ####\n\ncategorias simples")
    print(f'''categoria: filme que causou mais bocejos\n- {ganhador_simples(medias,'filme que causou mais bocejos', avaliadores)}''')
    print(f'''categoria: filme que foi mais pausado\n- {ganhador_simples(medias,'filme que foi mais pausado', avaliadores)}''')
    print(f'''categoria: filme que mais revirou olhos\n- {ganhador_simples(medias,'filme que mais revirou olhos', avaliadores)}''')
    print(f'''categoria: filme que não gerou discussão nas redes sociais\n- {ganhador_simples(medias, 'filme que não gerou discussão nas redes sociais', avaliadores)}''')
    print(f'''categoria: enredo mais sem noção\n- {ganhador_simples(medias,'enredo mais sem noção', avaliadores)}\n''')
    print(f'''categorias especiais\nprêmio pior filme do ano\n- {pior_filme(filmes, medias, avaliadores)}''')
    print(f'''prêmio não merecia estar aqui\n- {nao_merecia_estar_aq(filmes, medias, avaliadores)}''')


def ganhador_simples(medias: dict, categoria: str, avaliadores: dict) -> str:
    '''Acha o filme vencedor da categoria: aquele que obtiver a maior
    média aritmética das notas que recebeu de cada avaliador.

    Em caso de empate, ganha o filme que obteve mais votos,
    ou seja, aquele avaliado pelo maior número de avaliadores.

    Parâmetros:
    medias -- dicionário
    categoria -- string
    avaliadores -- dicionário

    Retorno:
    vencedor -- str
    '''
    vencedor = max(medias[categoria].keys(), key=lambda k:
                   (medias[categoria][k],
                   avaliadores[categoria][k]))
    return vencedor


def pior_filme(filmes: dict, medias: dict, avaliadores: dict) -> str:
    '''Acha o filme que ganhou mais categorias simples.

    Em caso de empate, o vencedor é o filme que obteve a
    maior quantidade de pontos no total, ou seja, a soma das médias que ele
    alcançou em cada categoria onde foi avaliado por algum avaliador.

    Parâmetros:
    filmes -- dicionário
    medias -- dict
    avaliadores -- dicionário

    Retorno:
    ganhador -- str
    '''
    filmes = pegar_vencedores(filmes, medias, avaliadores)
    pontos = pegar_pontos(filmes, medias)
    final = {filme: sum(filmes[filme].values()) for filme in filmes}
    ganhador = max(final, key=lambda k: (final[k], pontos[k]))
    return ganhador


def pegar_vencedores(filmes: dict, medias: dict, avaliadores: dict) -> dict:
    '''Atualiza o dicionario "filmes" com as categorias que cada filme venceu.
    Se o filme ganhou a categoria, o seu valor associado é "1".

    Parâmetros:
    filmes -- dicionário
    medias -- dicionário
    avaliadores -- dicionário

    Retorno:
    filmes -- dicionário
    '''
    for filme in filmes:
        for premio in filmes[filme]:

            if ganhador_simples(medias, premio, avaliadores) == filme:
                filmes[filme][premio] += 1
    return filmes


def pegar_pontos(filmes: dict, medias: dict) -> dict:
    '''Pega a quantidade de pontos totais, isto é,
    a soma das médias que o filme alcançou nas categorias
    onde foi avaliado.

    Parâmetros:
    filmes -- dicionário
    medias -- dicionário

    Retorno:
    pontos -- dicionário
    '''
    pontos = {filme: 0 for filme in filmes}
    for filme in filmes:
        pontuacao = 0
        for categoria in filmes[filme]:

            if filme in medias[categoria]:
                pontuacao += medias[categoria][filme]
                pontos[filme] = pontuacao
    return pontos


def nao_merecia_estar_aq(filmes: dict, medias: dict, avaliadores: dict) -> str:
    '''Acha aqueles um ou mais filmes que
    não foram avaliados por nenhum avaliador.

    Caso todos os filmes tenham sido escolhidos,
    informa que nenhum filme venceu a categoria.

    Parâmetros:
    filmes -- dict
    medias -- dict
    avaliadores -- dict

    Retorno:
    ganhadores -- string
    ou "sem ganhadores" -- string
    '''
    filmes = pegar_vencedores(filmes, medias, avaliadores)
    pontos = pegar_pontos(filmes, medias)
    ganhadores = []

    for filme in filmes:
        for categoria in filmes[filme]:
            if filmes[filme][categoria] == 0:
                x = True
            else:
                x = False

        if x is True:
            if pontos[filme] != 0:
                x is False
            else:
                ganhadores.append(filme)

    if ganhadores == []:
        return "sem ganhadores"
    else:
        return ", ".join(ganhadores)


if __name__ == "__main__":
    main()
