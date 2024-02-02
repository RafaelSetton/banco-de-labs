def join(lista):
    joined = ""
    for element in lista[:-1]:
        joined += element + ", "
    return joined + lista[-1]

dias = int(input())

for dia in range(dias):
    n_pares = int(input())
    brigas = [input().split() for par in range(n_pares)] 
    
    procedimentos_list = input().split()
    procedimentos = {procedimento: int(qtd) for procedimento, qtd in zip(procedimentos_list[::2], procedimentos_list[1::2])}

    n_pets = int(input())

    pets = [input().split() for pet in range(n_pets)]
    pet_names = [pet[0] for pet in pets]

    n_brigas = 0
    for animal1, animal2 in brigas:
        if animal1 in pet_names and animal2 in pet_names:
            n_brigas += 1
    
    atendimentos = ([], [], []) # (atendidos, nao atendidos, nao disponivel)

    for nome, procedimento in pets:
        if procedimento not in procedimentos.keys():
            atendimentos[2].append(nome)
            continue
        if procedimentos[procedimento] > 0:
            atendimentos[0].append(nome)
            procedimentos[procedimento] -= 1
        else:
            atendimentos[1].append(nome)


    print(f"Dia: {dia+1}")
    print(f"Brigas: {n_brigas}")
    if atendimentos[0]:
        print(f"Animais atendidos: {join(atendimentos[0])}")
    if atendimentos[1]:
        print(f"Animais não atendidos: {join(atendimentos[1])}")
    for pet in atendimentos[2]:
        print(f"Animal {pet} solicitou procedimento não disponível.")
    if dias > dia + 1:
        print()
