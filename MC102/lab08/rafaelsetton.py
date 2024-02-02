from typing import Dict, List, Generator

CATEGORIAS_SIMPLES = ["filme que causou mais bocejos",
                      "filme que foi mais pausado",
                      "filme que mais revirou olhos",
                      "filme que não gerou discussão nas redes sociais",
                      "enredo mais sem noção"]

# {filme: { categoria: [avaliacoes, soma_das_notas], ... }, ... }
pontuacoes: Dict[str, Dict[str, List[int]]] = dict()


def main():
    n_filmes = int(input())
    filmes = [input() for _ in range(n_filmes)]
    qtd_avaliacoes = int(input())

    global pontuacoes
    pontuacoes = {filme: dict() for filme in filmes}

    for _ in range(qtd_avaliacoes):
        _, categoria, filme, nota = input().split(', ')
        nota = int(nota)

        if pontuacoes[filme].get(categoria) is None:
            # Cria a categoria dentro desse filme
            pontuacoes[filme][categoria] = [1, nota]
        else:
            # Apenas altera os valores
            pontuacoes[filme][categoria][0] += 1
            pontuacoes[filme][categoria][1] += nota

    print("#### abacaxi de ouro ####", "categorias simples", sep="\n\n")

    vencedores = list(vencedores_simples())
    for categ, filme in zip(CATEGORIAS_SIMPLES, vencedores):
        print(f"categoria: {categ}\n- {filme}")
    print("\ncategorias especiais\nprêmio pior filme do ano")
    vencedores = vencedores_especiais(vencedores)
    print(f"- {vencedores[0]}")
    
    nao_merecia = ", ".join(vencedores[1]) if vencedores[1] else "sem ganhadores"
    print(f"prêmio não merecia estar aqui\n- {nao_merecia}")


def vencedores_especiais(vencedores: List[str]):
    return [pior_filme_do_ano(vencedores), nao_merecia_estar_aqui()]


def avaliacoes_do_filme(filme: str) -> int:
    return sum([pontuacoes[filme][categ][0] for categ in pontuacoes[filme]])


def pior_filme_do_ano(vencedores: List[str]):
    vencedor, pontuacao, desempate = "", 0, 0
    for filme in set(vencedores):
        contagem = vencedores.count(filme)
        avals = sum([data[1] / data[0] for _, data in pontuacoes[filme].items()])
        if contagem > pontuacao or \
                (contagem == pontuacao and avals > desempate):
            vencedor, pontuacao, desempate = filme, contagem, avals
    return vencedor


def nao_merecia_estar_aqui():
    vencedores = []
    for filme in pontuacoes:
        if avaliacoes_do_filme(filme) == 0:
            vencedores.append(filme)
    return vencedores


def vencedores_simples() -> Generator[str, None, None]:
    for categoria in CATEGORIAS_SIMPLES:
        vencedor, pontuacao, desempate = "", 0, 0
        for filme, dados in pontuacoes.items():
            try:
                pontos = dados[categoria][1] / dados[categoria][0]
            except KeyError:
                pass
            else:
                if pontos > pontuacao or \
                        (pontos == pontuacao and dados[categoria][0] > desempate):
                    vencedor = filme
                    pontuacao = pontos
                    desempate = dados[categoria][0]
        yield vencedor


if __name__ == '__main__':
    main()
