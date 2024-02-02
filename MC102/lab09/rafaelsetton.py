class Robo:
    def __init__(self, matriz):
        self.x = 0
        self.y = 0
        self.pos = (0, 0)
        self.ultima_visitada = (0, 0)
        self.proxima_a_visitar = (0, 1)

        self.matriz = matriz
        self.altura = len(matriz)
        self.largura = len(matriz[0])
        self.pos_final = (self.altura-1, self.largura-1) if self.altura % 2 else (self.altura-1, 0)

    def mover(self, dx, dy):
        self.mover_para(self.x + dx, self.y + dy)

    def mover_para(self, x, y):
        self.matriz[self.x][self.y] = '.'
        self.x = x
        self.y = y
        self.matriz[self.x][self.y] = 'r'
        self.pos = (self.x, self.y)
        for linha in self.matriz:
            print(*linha, sep=' ')
        print()

        if self.pos == self.proxima_a_visitar:
            self.ultima_visitada = self.pos
            delta_proxima = self.acha_proxima()
            self.proxima_a_visitar = (self.x + delta_proxima[0], self.y + delta_proxima[1])

    def adjacentes(self):
        possiveis = ((self.x, self.y - 1), (self.x - 1, self.y), (self.x, self.y + 1), (self.x + 1, self.y))
        return [(x, y) for x, y in possiveis if 0 <= x < self.altura and 0 <= y < self.largura]

    def acha_proxima(self):
        if self.pos == self.pos_final:
            while self.y < self.largura - 1:
                self.mover(0, 1)
            exit()
        elif (self.y == 0 and self.x % 2) or (self.y == self.largura - 1 and not self.x % 2):
            return 1, 0
        elif self.x % 2:
            return 0, -1
        else:
            return 0, 1

    def limpar(self, x: int, y: int):
        proxima = self.proxima_a_visitar
        self.mover_para(x, y)
        if (x, y) == proxima:
            return
        for x, y in self.adjacentes():
            if 0 <= x < self.altura and 0 <= y < self.largura:
                if self.matriz[x][y] == 'o':
                    self.limpar(x, y)
                    break

        self.retornar_ao_escaneamento()

    def retornar_ao_escaneamento(self):
        while self.y < self.ultima_visitada[1]:
            self.mover(0, 1)
            for x, y in self.adjacentes():
                if self.matriz[x][y] == 'o':
                    self.limpar(x, y)
                    break
        while self.y > self.ultima_visitada[1]:
            self.mover(0, -1)
            for x, y in self.adjacentes():
                if self.matriz[x][y] == 'o':
                    self.limpar(x, y)
                    break
        while self.x > self.ultima_visitada[0]:
            self.mover(-1, 0)
            for x, y in self.adjacentes():
                if self.matriz[x][y] == 'o':
                    self.limpar(x, y)
                    break


def main():
    altura = int(input())
    matriz = [input().split() for _ in range(altura)]
    largura = len(matriz[0])
    robo = Robo(matriz)
    robo.mover(0, 0)

    while robo.pos != robo.pos_final:
        for x, y in robo.adjacentes():
            if matriz[x][y] == 'o':
                robo.limpar(x, y)
                break
        else:
            robo.mover_para(*robo.proxima_a_visitar)

    if altura % 2 == 0:
        while robo.y < largura - 1:
            robo.mover(0, 1)


if __name__ == '__main__':
    main()
