class Entity:
    def __init__(self, initial_position, matrix_size):
        self._position = initial_position
        self._matrix_size = matrix_size

    @property
    def pos(self):
        return self._position

    @property
    def x(self):
        return self._position[0]

    @property
    def y(self):
        return self._position[1]

    @x.setter
    def x(self, value):
        self._position = (value, self.y)

    @y.setter
    def y(self, value):
        self._position = (self.x, value)

    def render(self, matrix: list[list[str]]):
        raise NotImplementedError()

    def _is_position_valid(self, x, y):
        return 0 <= x < self._matrix_size[0] and 0 <= y < self._matrix_size[1]

    def __repr__(self):
        return f"{self.__class__.__name__} at {self.pos}"


class Character(Entity):
    def __init__(self, hp, atk_points, initial_position, matrix_size):
        super().__init__(initial_position, matrix_size)
        self._hp = int(hp)
        self.atk_points = int(atk_points)

    @property
    def hp(self):
        return self._hp

    @hp.setter
    def hp(self, value):
        self._hp = max(0, value)

    @property
    def alive(self):
        return self.hp > 0

    def attack(self, other):
        old = other.hp
        other.hp -= self.atk_points
        return old - other.hp

    def move(self):
        raise NotImplementedError()

    def render(self, matrix: list[list[int]]):
        raise NotImplementedError()


class Hero(Character):
    def __init__(self, hp, atk_points, initial_position, target_position, matrix_size):
        super().__init__(hp, atk_points, initial_position, matrix_size)
        self.target_position = target_position
        self._reached_last_line = False

    def get_life_item(self, x):
        self.hp += x

    def get_atk_item(self, x):
        self.atk_points = max(1, self.atk_points + x)

    def move(self):
        if not self._reached_last_line:
            self.x += 1
            if self.x == self._matrix_size[0] - 1:
                self._reached_last_line = True
        elif self.x % 2 and self.y < self._matrix_size[1]-1:
            self.y += 1
        elif self.x % 2 == 0 and self.y > 0:
            self.y -= 1
        else:
            self.x -= 1

    def render(self, matrix: list[list[int]]):
        matrix[self.target_position[0]][self.target_position[1]] = '*'
        char = 'P' if self.alive else 'X'
        matrix[self.x][self.y] = char


class Monster(Character):
    def __init__(self, hp, atk, monster_type, pos, matrix_size):
        pos = tuple(map(int, pos.split(',')))
        super().__init__(hp, atk, pos, matrix_size)
        self.type = monster_type

    def move(self):
        deltas = {
            'L': (0, -1),
            'R': (0, 1),
            'U': (-1, 0),
            'D': (1, 0),
        }
        dx, dy = deltas[self.type]
        new_pos = (self.x + dx, self.y + dy)
        if self._is_position_valid(*new_pos):
            self._position = new_pos

    def render(self, matrix: list[list[int]]):
        if matrix[self.x][self.y] not in 'PX*':
            matrix[self.x][self.y] = self.type


class Item(Entity):
    def __init__(self, name, item_type, pos, status, matrix_size):
        pos = tuple(map(int, pos.split(',')))
        super().__init__(pos, matrix_size)
        self.name = name
        self.type = item_type
        self.status = int(status)

    def render(self, matrix: list[list[str]]):
        if matrix[self.x][self.y] in '.dv':
            matrix[self.x][self.y] = self.type


def display(n: int, m: int, *entities: Entity):
    matrix = [['.'] * m for _ in range(n)]
    for entity in entities:
        entity.render(matrix)

    for line in matrix:
        print(*line)
    print()


def main():
    vp, dp = map(int, input().split())
    n, m = map(int, input().split())
    initial_position = tuple(map(int, input().split(',')))
    target_position = tuple(map(int, input().split(',')))
    q_monsters = int(input())

    monsters: list[Monster] = []
    for _ in range(q_monsters):
        monsters.append(Monster(*input().split(), (n, m)))

    q_items = int(input())
    items: list[Item] = []
    for _ in range(q_items):
        items.append(Item(*input().split(), (n, m)))

    link = Hero(vp, dp, initial_position, target_position, (n, m))

    display(n, m, link, *monsters, *items)

    while link.alive and link.pos != link.target_position:
        link.move()
        for item in items.copy():
            if item.pos == link.pos:
                if item.type == 'v':
                    link.get_life_item(item.status)
                else:
                    link.get_atk_item(item.status)
                print(f"[{item.type}]Personagem adquiriu o objeto {item.name} com status de {item.status}")
                items.remove(item)

        for monster in monsters:
            monster.move()
            if monster.pos == link.pos and link.alive and link.pos != link.target_position:
                print(f"O Personagem deu {link.attack(monster)} de dano ao monstro na posicao {monster.pos}")
                if monster.alive:
                    print(f"O Monstro deu {monster.attack(link)} de dano ao Personagem. Vida restante = {link.hp}")
        monsters = list(filter(lambda monst: monst.alive, monsters))

        display(n, m, link, *monsters, *items)

    if link.alive:
        print("Chegou ao fim!")


if __name__ == '__main__':
    main()
