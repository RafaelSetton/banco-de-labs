class Entidade:
    def __init__(self, posicao: list):
        self._posicao = posicao

    @property
    def posicao(self):
        return self._posicao.copy()

    @property
    def x(self):
        return self._posicao[0]

    @property
    def y(self):
        return self._posicao[1]

    @x.setter
    def x(self, valor):
        self._posicao[0] = valor

    @y.setter
    def y(self, valor):
        self._posicao[1] = valor


class SerVivo(Entidade):
    def __init__(self, posicao: list, vida: int, dano: int):
        super().__init__(posicao)
        self._vida = vida
        self._dano = dano

    @property
    def vida(self):
        return self._vida

    @property
    def dano(self):
        return self._dano

    @vida.setter
    def vida(self, valor):
        if valor < 0:
            self._vida = 0
        else:
            self._vida = valor

    @dano.setter
    def dano(self, valor):
        self._dano = valor

    def vivo(self):
        '''Checa se ta vivo, retorna True para esse caso'''
        if self._vida != 0:
            return True
        else:
            return False

    def ataque(self, obj):
        '''Realiza o ataque de Link ao monstro e vice versa'''
        total_dano = min(obj._vida, self.dano)
        obj._vida -= total_dano
        return total_dano


class Personagem(SerVivo):
    def __init__(self, posicao: list, vida: int, dano: int, nome: str, posicao_final: list):
        super().__init__(posicao, vida, dano)
        self._nome = nome
        self._posicao_final = posicao_final

    @property
    def posicao_final(self):
        return self._posicao_final

    def andar_maldicao(self):
        ''' Link anda ate a ultima linha'''
        self.x += 1

    def andar(self, mapa):
        '''Movimenta a posicao de Link, baseado na paridade da linha que ele está'''
        # se a linha for par:
        if self.x % 2 == 0:
            if self.y == 0:
                self.x -= 1
            else:
                self.y -= 1
        # se a linha for impar:
        else:
            if self.y == (mapa._colunas - 1):
                self.x -= 1
            else:
                self.y += 1

    def pegar_objeto(self, objeto):
        '''Recolhe o objeto'''
        if objeto.tipo == "v":
            self._vida += objeto.status
            objeto._disponivel = False
            print(f"[{objeto.tipo}]Personagem adquiriu o objeto {objeto.nome} com status de {objeto.status}")
        elif objeto.tipo == "d":
            self._dano += objeto.status
            objeto._disponivel = False
            print(f"[{objeto.tipo}]Personagem adquiriu o objeto {objeto.nome} com status de {objeto.status}")


class Monstro(SerVivo):
    def __init__(self, posicao: list, vida: int, dano: int, tipo: str):
        super().__init__(posicao, vida, dano)
        self._tipo = tipo

    @property
    def tipo(self):
        return self._tipo

    def andar(self, mapa):
        '''Atualiza a posicao do monstro baseado no padrao de movimentacao dele (tipo).
        Garante tambem que o monstro nao vai extrapolar os limites do mapa.
        '''
        if self.tipo == "U" and self.x != 0:
                self.x -= 1
        elif self.tipo == "D" and self.x != (mapa._linhas - 1):
                self.x += 1
        elif self.tipo == "R" and self.y != (mapa._colunas - 1):
                self.y += 1
        elif self.tipo == "L" and self.y != 0:
                self.y -= 1


class Objeto(Entidade):
    def __init__(self, posicao: list, nome: int, tipo: int, status: int):
        super().__init__(posicao)
        self._nome = nome
        self._tipo = tipo
        self._status = status
        self._disponivel = True

    @property
    def nome(self):
        return self._nome

    @property
    def tipo(self):
        return self._tipo

    @property
    def status(self):
        return self._status

    @property
    def disponivel(self):
        return self._disponivel

    @disponivel.setter
    def disponivel(self, valor):
        self._disponivel = valor


class Mapa:
    def __init__(self, linhas: int, colunas: int, numero_monstro: int, numero_objeto: int,
                 link: Personagem, monstros: list[Monstro], objetos: list[Objeto]):
        self._linhas = linhas
        self._colunas = colunas
        self._numero_de_monstros = numero_monstro
        self._numero_de_objetos = numero_objeto
        self._link = link
        self._monstros = monstros
        self._objetos = objetos
        self._mapa = None

    def renderizar(self):
        '''renderiza o mapa atualizando-o com as posicoes novas, de acordo com a ordem de prioridade dada'''
        self._mapa = [["." for j in range(self._colunas)] for i in range(self._linhas)]

        for objeto in self._objetos:
            if objeto.disponivel:
                self._mapa[objeto.x][objeto.y] = objeto.tipo

        for monstro in self._monstros:
            if monstro.vivo():
                self._mapa[monstro.x][monstro.y] = monstro.tipo

        self._mapa[self._link.posicao_final[0]][self._link.posicao_final[1]] = "*"

        if self._link.posicao == self._link.posicao_final:
            self._mapa[self._link.posicao_final[0]][self._link.posicao_final[1]] = "P"

        if self._link.vivo():
            self._mapa[self._link.x][self._link.y] = "P"
        else:
            self._mapa[self._link.x][self._link.y] = "X"

        for linha in self._mapa:
            print(" ".join(linha))
        print()

def organizar_monstros(numero_monstros: int):
    '''Monta uma lista de objetos da classe Monstro'''
    monstros = []
    for _ in range(numero_monstros):
        vida, dano, tipo, posicao = input().split()
        vida, dano = int(vida), int(dano)
        posicao = posicao.split(",")
        posicao = list(map(int, posicao))

        monstro = Monstro(posicao, vida, dano, tipo)
        monstros.append(monstro)
    return monstros


def organizar_objetos(numero_objetos: int):
    '''Monta uma lista de objetos da classe Objeto'''
    objetos = []
    for _ in range(numero_objetos):
        nome, tipo, posicao, status = input().split()
        status = int(status)
        posicao = posicao.split(",")
        posicao = list(map(int, posicao))

        objeto = Objeto(posicao, nome, tipo, status)
        objetos.append(objeto)
    return objetos


def combate(link: Personagem, monstro: Monstro):
    '''Link ataca, monstro ataca'''
    if link.posicao != link.posicao_final:
        if link.vivo():
            total_dano_link = link.ataque(monstro)
            print(f"O Personagem deu {total_dano_link} de dano ao monstro na posicao {monstro.x, monstro.y}")
        if monstro.vivo():
            total_dano_monstro = monstro.ataque(link)
            print(f"O Monstro deu {total_dano_monstro} de dano ao Personagem. Vida restante = {link.vida}")


def monstros_andam(monstros: list[Monstro], mapa):
    '''Atualiza as posicoes dos monstros'''
    for monstro in monstros:
        monstro.andar(mapa)


def main():
    #entradas
    vida, dano = map(int, input().split())
    n_linhas, n_colunas = map(int, input().split())
    posicao_link = list(map(int, (input().split(","))))
    posicao_saida = list(map(int, (input().split(","))))
    n_monstros = int(input())
    monstros: list[Monstro] = organizar_monstros(n_monstros)
    n_objetos = int(input())
    objetos: list[Objeto] = organizar_objetos(n_objetos)
    # instanciando os objetos
    link = Personagem(posicao_link, vida, dano, "link", posicao_saida)
    mapa = Mapa(n_linhas, n_colunas, n_monstros, n_objetos, link, monstros, objetos)

    # estado inicial
    mapa.renderizar()
    # inicio da jornada: maldicao
    while link.x != (n_linhas - 1) and link.vivo():
        link.andar_maldicao()
        monstros_andam(monstros, mapa)
        for objeto in objetos:
            if link.posicao == objeto.posicao and objeto.disponivel:
                link.pegar_objeto(objeto)
        for monstro in monstros:
            if link.posicao == monstro.posicao and link.vivo():
                combate(link, monstro)
        mapa.renderizar()

    #dps de descer ate a ultima linha 
    while link.posicao != link.posicao_final and link.vivo():
        link.andar(mapa)
        monstros_andam(monstros, mapa)
        
        for objeto in objetos:
            if link.posicao == objeto.posicao and objeto.disponivel:
                link.pegar_objeto(objeto)
        for monstro in monstros:
            if link.posicao == monstro.posicao and link.vivo():
                combate(link, monstro)
        mapa.renderizar()

    if link.posicao == link.posicao_final:
        print("Chegou ao fim!\n")


if __name__ == "__main__":
    main()
