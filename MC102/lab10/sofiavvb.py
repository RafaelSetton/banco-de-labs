import math


class Personagem:
    def __init__(self, nome: str, vida: int, flechas: dict):
        self._nome = nome 
        self._vida = vida
        self._flechas = flechas

    @property
    def nome(self):
        return self._nome

    @property
    def vida(self):
        return self._vida
    
    @property
    def flechas(self):
        return self._flechas
    
    @vida.setter
    def vida(self, valor):
        self._vida = valor
        if self._vida < 0:
            self.vida = 0
            
    
    @flechas.setter
    def flechas(self, valor):
        self._flechas = valor
    

    def viva(self):
        '''Checa se Aloy ta viva, retorna True para esse caso'''
        if self._vida != 0:
            return True
        else:
            return False


class Parte:
    def __init__(self, nome: str, fraqueza: str, dano_max: int, cx: int, cy: int):
        self._nome = nome
        self._fraqueza = fraqueza
        self._dano_max = dano_max
        self._cx = cx
        self._cy = cy
    
    @property
    def nome(self):
        return self._nome
    
    @property
    def fraqueza(self):
        return self._fraqueza
    
    @property
    def dano_max(self):
        return self._dano_max
    
    @property
    def cx(self):
        return self._cx
    
    @property
    def cy(self):
        return self._cy
     
    @property
    def ponto_critico(self):
        return (self._cx, self._cy)

      
class Maquina:
    def __init__(self, pontos_vida: int, pontos_ataque: int, numero_partes: int, partes: list[Parte]):
        self._pontos_vida = pontos_vida
        self._pontos_ataque = pontos_ataque 
        self._numero_partes = numero_partes
        self._partes = partes
        self._acertos_criticos = {parte.ponto_critico: 0 for parte in partes}

    @property
    def pontos_vida(self):
        return self._pontos_vida
    
    @property
    def pontos_ataque(self):
        return self._pontos_ataque

    @property
    def numero_partes(self):
        return self._numero_partes
    
    @property
    def partes(self):
        return self._partes
    
    @property
    def acertos_criticos(self):
        return self._acertos_criticos

    @pontos_vida.setter
    def pontos_vida(self, valor: int):
        if valor < 0:
            self._pontos_vida = 0
        else:
            self._pontos_vida = valor
  
    def atualiza_acertos_criticos(self, fx: int, fy: int):
        '''Atualiza a quantidade de vezes que determinado ponto critico da maquina foi atingido'''
        self._acertos_criticos[(fx, fy)] += 1


    def encontra_parte(self, nome_parte: str):
        '''Encontra a parte que Aloy está atacando da máquina'''
        for parte in self._partes:
            if parte.nome == nome_parte:
                return parte

    def morta(self):
        '''Checa se a maquina morreu, retorna True nesse caso'''
        if self._pontos_vida == 0:
            return True
        else:
            return False


def main():
    vida = int(input())
    flechas = input().split()
    #organizando em dicionário a entrada das flechas
    flechas = {flechas[i]: int (flechas[i+1])  for i in range(len(flechas)) if i % 2 == 0} #{tipo: quantidade}
    #essa copia será utilizada para termos o controle das flechas usadas no combate
    flechas_copia = flechas.copy()
    Aloy = Personagem("Aloy", vida, flechas)
    sem_flechas = False
    numero_monstros = int(input())
    combates = -1
    
    #a missao comecao aqui
    while numero_monstros != 0 and Aloy.viva() and not sem_flechas:
        combates += 1
        #reestarta as flechas de Aloy
        flechas_copia: dict = flechas.copy()
        numero_combatentes = int(input())
        maquinas_combatentes: list[Maquina] = organiza_combate(numero_combatentes)
        flechas_usadas = {} #{tipo: quantidade}
        
        print(f"Combate {combates}, vida = {Aloy.vida}")
        
        #combate comeca
        while numero_combatentes != 0 and Aloy.viva() and not sem_flechas:
            #fase de ataque
            ataques = 0
            while ataques < 3:
                ataques += 1
                unidade_alvo, nome_parte, tipo_flecha, fx, fy = input().split(', ')
                fx, fy = int(fx), int(fy)
                #separa a maquina que ela ta atacando e a parte especifica tb
                maquina_alvo = maquinas_combatentes[int(unidade_alvo)]
                parte_alvo = maquina_alvo.encontra_parte(nome_parte)
                
                ataque_Aloy(maquina_alvo, tipo_flecha, parte_alvo, fx, fy)
                if (fx,fy) == parte_alvo.ponto_critico:
                    maquina_alvo.atualiza_acertos_criticos(fx, fy)
  
                flechas_usadas = flechas_gastas(tipo_flecha, flechas_usadas)
                flechas_copia = atualiza_flechas(tipo_flecha, flechas_copia)
                sem_flechas = all(valor <= 0 for valor in flechas_copia.values())   
                #vamos checar se ela matou a maquina que atacou
                if maquina_alvo.morta():
                    print(f"Máquina {unidade_alvo} derrotada")
                    numero_monstros -= 1
                    numero_combatentes -= 1
                    #se não tem mais maquinas nesse combate
                    if numero_combatentes == 0:
                        break
                    
                if sem_flechas:
                    break    
            #volta ao inicio de um novo combate
            if numero_combatentes == 0:
                break
            #Aloy é atacada por todas as maquinas
            ataque_maquinas(maquinas_combatentes, Aloy)

        #fim de um combate
        print(f"Vida após o combate = {Aloy.vida}")
        #se Aloy for derrotada após o combate
        if not Aloy.viva():
            print("Aloy foi derrotada em combate e não retornará a tribo.")
            #acaba a missão
            break
        #se as flechas dela acabarem após o combate
        elif sem_flechas:
            print("Aloy ficou sem flechas e recomeçará sua missão mais preparada.")
            break
        #Aloy se cura
        else:
            Aloy.vida = Aloy.vida + math.floor(0.5 * vida)
            if Aloy.vida > vida:
                Aloy.vida = vida
        #mostrar quantidade de flechas de cada tipo usadas no combate
            print("Flechas utilizadas:")
            for tipo in list(flechas.keys()):
                if tipo in flechas_usadas:
                    print(f"- {tipo}: {flechas_usadas[tipo]}/{flechas[tipo]}")
        #mostrar os pontos críticos acertados e quantas vezes, se existem pontos criticos acertados.
            #checar se acertou algum ponto crítico de alguma maquina
            numero_criticos = sum([sum(maquina.acertos_criticos.values()) for maquina in maquinas_combatentes])
            if numero_criticos > 0:
                print("Críticos acertados:")
                for maquina in maquinas_combatentes:
                    #checar se acertou algum ponto crítico da maquina em questão
                    if not all((quantidade == 0 for quantidade in maquina.acertos_criticos.values())):
                        print(f"Máquina {maquinas_combatentes.index(maquina)}:")
                        for ponto_critico in maquina.acertos_criticos:
                            if maquina.acertos_criticos[ponto_critico] != 0:
                                print(f"- {ponto_critico}: {maquina.acertos_criticos[ponto_critico]}x")

    if Aloy.viva() and not sem_flechas:
        print("Aloy provou seu valor e voltou para sua tribo.")


def ataque_Aloy(maquina_alvo: Maquina, tipo_flecha: str, parte_alvo: str, fx: int, fy: int):
    '''Aloy ataca maquina'''
    if parte_alvo.fraqueza == tipo_flecha or parte_alvo.fraqueza == "todas":
        dano = calcular_dano(parte_alvo, fx, fy)
    else:
        dano = calcular_dano(parte_alvo, fx, fy) // 2 
    maquina_alvo.pontos_vida -= dano


def calcular_dano(parte_alvo: Parte, fx: int, fy: int):
    '''Calcula o dano que Aloy dará na maquina, baseado na fórmula dada'''
    dano = parte_alvo.dano_max - (abs(parte_alvo.cx - fx) + abs(parte_alvo.cy - fy))
    if dano < 0:
        dano = 0
    return dano


def organiza_combate(quantidade_maquinas: int):
    '''Instancia as maquinas envolvidas no combate e as partes que as compoem'''
    maquinas: list[Maquina] = []

    for i in range(quantidade_maquinas):
        partes: list[Parte] = []
        pontos_vida, pontos_ataque, numero_partes = input().split()
        pontos_vida, pontos_ataque, numero_partes = int(pontos_vida), int(pontos_ataque), int(numero_partes)
        
        for j in range(int(numero_partes)):
            nome, fraqueza, dano_max, cx, cy = input().split(', ')
            dano_max, cx, cy = int(dano_max), int(cx), int(cy)
            partes.append(Parte(nome, fraqueza, dano_max, cx, cy))
                
        maquinas.append(Maquina(pontos_vida, pontos_ataque, numero_partes, partes))
    return maquinas


def ataque_maquinas(maquinas: list[Maquina], Aloy: Personagem):
    '''Todas as maquinas envolvidas no combate atacam Aloy'''
    for maquina in maquinas:
        if not maquina.morta():
            Aloy.vida -= maquina.pontos_ataque


def flechas_gastas(tipo_flecha: str, flechas_usadas: dict):
    '''Monta um dicionario e atualiza ele com as flechas gastas e as suas quantidades'''
    if tipo_flecha not in flechas_usadas:
        flechas_usadas[tipo_flecha] = 0
        
    flechas_usadas[tipo_flecha] += 1 

    return flechas_usadas 


def atualiza_flechas(tipo: str, flechas: dict):
    '''Contabiliza as flechas usadas no combate'''
    flechas[tipo] -= 1
    return flechas

 
if __name__ == "__main__":
    main()
