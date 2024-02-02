dias = int(input()) 
for dia in range(dias):
	pares = []
	procedimentos_solicitados = []
	procedimentos_disponiveis = []
	quantidades_disponiveis = []
	cachorros_atendidos = []
	nao_atendidos = []
	nao_disponiveis = []
	nao_existe = 0
	presente = -1
	brigas = 0

	#quantos pares de cachorros que brigam temos no dia
	numero_pares_brigam = int(input())   
	#recebe os pares e coloca numa lista
	for i in range(numero_pares_brigam):
		par = input().split()
		#lista de listas dos pares que brigam
		pares.append(par)
							
	
	procedimentos= input().split()
	#gera lista com os procedimentos disponíveis e outra com as quantidades disponíveis 
	for n in range(len(procedimentos)//2):
		procedimentos_disponiveis.append(procedimentos[2*n])
		quantidades_disponiveis.append(procedimentos[2*n+1])

	animais_presentes = int(input())

	for n in range(animais_presentes):
		animais_procedimentos = input().split()
		#lista com animais e os procedimentos solicitados
		procedimentos_solicitados.extend(animais_procedimentos) 

	#algoritmo que calcula o número de brigas:
	for lista in range(len(pares)):
		presente = -1
		for k in range(2):
			for j in range(0, len(procedimentos_solicitados), 2):
				if pares[lista][k] == procedimentos_solicitados[j]:
					presente = presente + 1
					break
			#primeiro cachorro não está presente, nem adianta ver se o segundo está.
			if presente == -1:    
				break
		if presente == 1:
			brigas += 1

	#algoritmo para achar os atendimentos
	for i in range(1, len(procedimentos_solicitados), 2):
		nao_existe = 0
		for j in range(len(procedimentos_disponiveis)):
			if (procedimentos_solicitados[i] == procedimentos_disponiveis[j]):
				nao_existe += 1
				if int(quantidades_disponiveis[j]) > 0:
					cachorros_atendidos.append(procedimentos_solicitados[i-1])
					quantidades_disponiveis[j] = int(quantidades_disponiveis[j]) - 1
					break
				else:
					nao_atendidos.append(procedimentos_solicitados[i-1])
					
		if nao_existe == 0:
			nao_disponiveis.append(procedimentos_solicitados[i-1])
	#saídas
	print(f'Dia: {dia+1}')
	print(f'Brigas: {brigas}')
	if cachorros_atendidos != []:
		print('Animais atendidos: ', end="")
		for i in cachorros_atendidos:
			if i == cachorros_atendidos[len(cachorros_atendidos) - 1]:
				print(f'{i}')
			else:
				print(f'{i}, ', end="")
							
	if nao_atendidos != []:
		print('Animais não atendidos: ', end="")
		for i in nao_atendidos:
			if i == nao_atendidos[len(nao_atendidos) - 1]:
				print(f'{i}')
			else:
				print(f'{i}, ', end="")	

	for i in nao_disponiveis:
		print(f'Animal {i} solicitou procedimento não disponível.')
	print()
	
