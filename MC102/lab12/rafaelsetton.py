# 63 + 9 + 20
class Card:
    CARDS_ORDER = [val + suit for val in list('A23456789') + ['10'] + list("JQK") for suit in 'OECP']

    def __init__(self, string):
        self._string = string

    @property
    def string(self):
        return self._string

    @property
    def value(self):
        return self._string[:-1]

    @property
    def suit(self):
        return self._string[-1]

    def __eq__(self, other):
        return self.string == other.string

    def __lt__(self, other):
        return self.CARDS_ORDER.index(self.string) < self.CARDS_ORDER.index(other.string)

    def __gt__(self, other):
        return self.CARDS_ORDER.index(self.string) > self.CARDS_ORDER.index(other.string)

    def __le__(self, other):
        return self < other or self == other

    def __ge__(self, other):
        return self > other or self == other

    def __repr__(self):
        return self._string

    def __str__(self):
        return self._string


def order(hand: list[Card]):
    for i in range(len(hand)):
        big = i
        for j in range(i+1, len(hand)):
            if hand[j] > hand[big]:
                big = j
        hand[big], hand[i] = hand[i], hand[big]
    return hand


def binary_search(array: list, item):
    left, right = 0, len(array)-1
    while left < right:
        mid = (left+right)//2
        if array[mid] > item:
            left = mid + 1
        else:
            right = mid
    return left


def get_play(min_pow: str, hand: list[Card]):
    if hand[0] < Card(min_pow+'O'):
        idx_max = binary_search(hand, Card(hand[-1].value + 'P'))
        return hand[idx_max:], f"{len(hand)-idx_max} carta(s) {min_pow}"

    idx_min = binary_search(hand, Card(min_pow + 'O'))
    if hand[idx_min] < Card(min_pow+'O'):
        idx_min -= 1
    idx_max = binary_search(hand, Card(hand[idx_min].value + 'P'))
    return hand[idx_max:idx_min+1], f"{idx_min-idx_max+1} carta(s) {hand[idx_max].value}"


def duvida(duvidou: int, duvidado: int, play: list[Card], play_description: str):
    suposta = play_description.split()[-1]
    if play[0].value == suposta:
        return duvidou
    return duvidado


def main():
    n_players = int(input())
    hands: list[list[Card]] = [list(map(Card, input().split(', '))) for _ in range(n_players)]
    pile: list[Card] = []
    round_duration = int(input())

    play: list[Card] = []
    play_description: str = ''

    turn = 0
    while all(map(len, hands)):
        hands = list(map(order, hands))
        for i, hand in enumerate(hands):
            print(f"Jogador {i+1}")
            print("Mão:", *hand)
        print("Pilha:", *pile)
        min_pow = 'A'

        for _ in range(round_duration):
            if not hands[turn - 1]:
                return print(f"Jogador {turn if turn else n_players} é o vencedor!")

            play, play_description = get_play(min_pow, hands[turn])
            pile += play[::-1]
            hands[turn] = list(filter(lambda c: c not in play, hands[turn]))
            print(f"[Jogador {turn+1}] {play_description}")
            print("Pilha:", *pile)
            turn = (turn + 1) % n_players
            min_pow = play_description.split()[-1]
        print(f"Jogador {turn+1} duvidou.")
        compra = duvida(turn, (turn-1) % n_players, play, play_description)
        hands[compra] += pile
        pile = []

    hands = list(map(order, hands))
    for i, hand in enumerate(hands):
        print(f"Jogador {i + 1}")
        print("Mão:", *hand)
    print("Pilha:", *pile)
    return print(f"Jogador {hands.index([])+1} é o vencedor!")


if __name__ == '__main__':
    main()
