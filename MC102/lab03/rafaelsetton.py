j = int(input())
retirados = list(map(int, input().split()))
intervalos = list(map(int, input().split()))

n_primeiro_grupo = j // 2 + j % 2
pontos = []

for i in range(j):
    ponto_jogador = intervalos[2*i+1] - intervalos[2*i]
    if i < n_primeiro_grupo:
        ponto_jogador *= retirados[i]
    else:
        ponto_jogador += retirados[i]
    pontos.append(ponto_jogador)

maior = max(pontos)
if pontos.count(maior) > 1:
    print("Rodada de cerveja para todos os jogadores!")
else:
    print(f"O jogador número {pontos.index(maior) + 1} vai receber o melhor bolo da cidade pois venceu com {maior} ponto(s)!")