import sys
sys.setrecursionlimit(100_000)


class Image(list):
    def __init__(self, source: list[list], max_value):
        super().__init__(source)
        self.max_value = max_value

    def spread(self, col, row, t, source=None, curr=None, exclude=None):
        if source is None:
            source = (row, col)
        if curr is None:
            curr = [source]

        deltas = [(x, y) for x in (-1, 0, 1) for y in (-1, 0, 1)]
        for dx, dy in deltas:
            x, y = row + dx, col + dy
            if not (0 <= x < len(self) and 0 <= y < len(self[0])):
                continue

            if (x, y) not in curr and abs(self[x][y] - self[source[0]][source[1]]) <= t and self[x][y] is not exclude:
                curr.append((x, y))
                self.spread(y, x, t, source, curr, exclude)

        return curr

    def cmask(self, t, col, row):
        mask = self.spread(col, row, t)
        for x in range(len(self)):
            for y in range(len(self[0])):
                try:
                    self[x][y] = 255 * ((x, y) not in mask)
                except IndexError:
                    print(x, y)
                    print(*self, sep='\n')

    def bucket(self, c, t, col, row):
        for x, y in self.spread(col, row, t, exclude=c):
            self[x][y] = c

    def negative(self, t, col, row):
        for x, y in self.spread(col, row, t):
            self[x][y] = self.max_value - self[x][y]

    def save(self, path):
        with open(path, 'w') as file:
            file.write("P2\n# Imagem criada pelo lab13\n")
            file.write(f"{len(self[0])} {len(self)}\n")
            file.write(f"{self.max_value}\n")
            for line in self:
                file.write(" ".join(map(str, line)) + '\n')


def get_image(path: str):
    with open(path) as file:
        data = file.read().strip().split('\n')
    max_value = int(data[3])
    image = [[int(x) for x in data[line].split()] for line in range(4, len(data))]
    return Image(image, max_value)


def main():
    input_path = input()
    image = get_image(input_path)
    n_operations = int(input())
    for _ in range(n_operations):
        command, *args = input().split()
        match command:
            case "bucket":
                c, t, col, row = [int(x) for x in args]
                image.bucket(c, t, col, row)
            case "negative":
                t, col, row = [int(x) for x in args]
                image.negative(t, col, row)
            case "cmask":
                t, col, row = [int(x) for x in args]
                image.cmask(t, col, row)
            case "save":
                path = args[0]
                image.save(path)


if __name__ == '__main__':
    main()
