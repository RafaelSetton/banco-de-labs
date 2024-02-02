numero_jogadores = int(input())
numeros_retirados = input().split()
intervalos = input().split()
pontos = []

#cálculo das pontuações de cada jogador considerando as regras do jogo
for i in range(len(numeros_retirados)):
        if i < len(numeros_retirados)/2:    
            pontuacao = (int(intervalos[2*i + 1]) - int(intervalos[2*i])) * int(numeros_retirados[i])
            pontos.append(pontuacao)
        else: 
            pontuacao = (int(intervalos[2*i + 1]) - int(intervalos[2*i])) + int(numeros_retirados[i])
            pontos.append(pontuacao)
    
#achar a maior pontuação e de quem foi a maior pontuação ou se foi houve empate
maior_jogador = 0
maior_pontuacao = -1
for j in range(len(pontos)):
    if pontos[j] > maior_pontuacao:
        maior_pontuacao = pontos[j]
        maior_jogador = j + 1
    elif pontos[j] == maior_pontuacao:
        maior_jogador = 0
            
if maior_jogador == 0:
    print('Rodada de cerveja para todos os jogadores!')
else:
    print(f'O jogador número {maior_jogador} vai receber o melhor bolo da cidade pois'
f' venceu com {maior_pontuacao} ponto(s)!')