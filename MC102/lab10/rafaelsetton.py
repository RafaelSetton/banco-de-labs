class Part:
    def __init__(self, name, weakness, max_damage, critic_spot):
        self.name = name
        self.weakness = weakness
        self.max_damage = max_damage
        self.critic_spot = critic_spot


class Arrow:
    def __init__(self, target_part, arrow_type, hit_spot):
        self.target_part = target_part
        self.type = arrow_type
        self.hit_spot = hit_spot


class Monster:
    def __init__(self, hp, atk_points, parts):
        self.hp = hp
        self.atk_points = atk_points
        self.parts: list[Part] = parts
        self.critics = {part.critic_spot: 0 for part in parts}

    @property
    def alive(self):
        return self.hp > 0

    def get_part(self, name):
        for part in self.parts:
            if part.name == name:
                return part

    def attack(self, player: "Player"):
        player.hp -= self.atk_points


class Player:
    def __init__(self, max_hp, arrows: dict):
        self.max_hp = max_hp
        self.hp = max_hp
        self.quiver = arrows
        self.arrows_used = {arrow_type: 0 for arrow_type in arrows.keys()}

    @property
    def has_arrows(self):
        return sum(self.quiver.values()) > sum(self.arrows_used.values())

    @property
    def alive(self):
        return self.hp > 0

    def reset(self):
        self.hp = min(self.max_hp, self.hp + self.max_hp // 2)
        self.arrows_used = {arrow_type: 0 for arrow_type in self.quiver.keys()}

    def print(self, monsters: list[Monster]):
        print(f"Vida após o combate = {self.hp}")

        print("Flechas utilizadas:")
        for arrow_type in self.quiver.keys():
            if self.arrows_used[arrow_type] > 0:
                print(f"- {arrow_type}: {self.arrows_used[arrow_type]}/{self.quiver[arrow_type]}")

        first = True
        for idx, monster in enumerate(monsters):
            if monster.critics:
                if first:
                    print("Críticos acertados:")
                    first = False

                print(f"Máquina {idx}:")
                for part in monster.parts:
                    count = monster.critics[part.critic_spot]
                    if count:
                        print(f"- {part.critic_spot}: {count}x")

    def attack(self, arrow, monster: Monster):
        self.arrows_used[arrow.type] += 1

        target_part = monster.get_part(arrow.target_part)
        distance = manhattan_distance(target_part.critic_spot, arrow.hit_spot)
        damage = max(target_part.max_damage - distance, 0)
        if arrow.type != target_part.weakness and target_part.weakness != 'todas':
            damage //= 2
        monster.hp -= damage

        if distance == 0:  # Critic
            monster.critics[target_part.critic_spot] += 1

        return not monster.alive


def manhattan_distance(point1, point2):
    return abs(point1[0] - point2[0]) + abs(point1[1] - point2[1])


def get_monsters(n_monsters):
    monsters = []
    for i in range(n_monsters):
        hp, atk_points, n_parts = (int(x) for x in input().split())
        parts = []
        for _ in range(n_parts):
            name, weakness, max_damage, cx, cy = input().split(', ')
            parts.append(Part(name, weakness, int(max_damage), (int(cx), int(cy))))
        monsters.append(Monster(hp, atk_points, parts))
    return monsters


def main():
    max_hp = int(input())
    arrows_list = input().split()
    arrows = {tipo: int(qtd) for tipo, qtd in zip(arrows_list[::2], arrows_list[1::2])}
    total_monsters = int(input())
    defeated = 0
    aloy = Player(max_hp, arrows)
    monsters: list[Monster] = []
    combat = 0

    while defeated < total_monsters and aloy.alive and aloy.has_arrows:
        print(f"Combate {combat}, vida = {aloy.hp}")

        simultaneous_monsters = int(input())
        monsters = get_monsters(simultaneous_monsters)

        while any([monster.alive for monster in monsters]) and aloy.has_arrows and aloy.alive:
            target, target_part, arrow_type, fx, fy = input().split(', ')
            target = int(target)
            if aloy.attack(Arrow(target_part, arrow_type, (int(fx), int(fy))), monsters[target]):
                print(f"Máquina {target} derrotada")

            if sum(aloy.arrows_used.values()) % 3 == 0:
                for monster in monsters:
                    if monster.alive:
                        monster.attack(aloy)

        if aloy.alive and aloy.has_arrows:
            defeated += simultaneous_monsters
            aloy.print(monsters)
            aloy.reset()
            combat += 1

    if not aloy.alive:
        print("Vida após o combate = 0")
        print("Aloy foi derrotada em combate e não retornará a tribo.")
    elif any([monster.alive for monster in monsters]):
        print(f"Vida após o combate = {aloy.hp}")
        print("Aloy ficou sem flechas e recomeçará sua missão mais preparada.")
    else:
        print("Aloy provou seu valor e voltou para sua tribo.")


if __name__ == '__main__':
    main()
