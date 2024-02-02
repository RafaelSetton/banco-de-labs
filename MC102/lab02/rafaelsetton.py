print(
    "Este é um sistema que irá te ajudar a escolher a sua próxima Distribuição Linux. Responda a algumas poucas perguntas para ter uma recomendação.")


def new(ask, two=False):
    valids = [0, 1] + [2] * two
    choices = "(0) Não\n(1) Sim" + ("\n(2) Sim, realizo testes e invasão de sistemas" if two else "") + '\n'
    try:
        resps.append(int(input(ask + '\n' + choices)))
    except ValueError:
        print("Opção inválida, recomece o questionário.")
        exit(0)
    else:
        if resps[-1] not in valids:
            print("Opção inválida, recomece o questionário.")
            exit(0)


resps = []
new("Seu SO anterior era Linux?")
if resps[-1] == 0:
    new("Seu SO anterior era um MacOS?")
else:
    new("É programador/ desenvolvedor ou de áreas semelhantes?", True)
    if resps[-1] == 1:
        new("Gostaria de algo pronto para uso ao invés de ficar configurando o SO?")
        if resps[-1] == 0:
            new("Já utilizou Arch Linux?")
        else:
            new("Já utilizou Debian ou Ubuntu?")

opts = [
    [
        "Ubuntu Mate, Ubuntu Mint, Kubuntu, Manjaro",
        "ElementaryOS, ApricityOS"

    ],
    [
        "Ubuntu Mint, Fedora",
        [
            [
                "Antergos, Arch Linux",
                "Gentoo, CentOS, Slackware"
            ],
            [
                "OpenSuse, Ubuntu Mint, Ubuntu Mate, Ubuntu",
                "Manjaro, ApricityOS"
            ]
        ],
        "Kali Linux, Black Arch"
    ]
]

if resps[0] == 1 and resps[-1] == 1:
    print("Suas escolhas te levaram a um caminho repleto de desafios, para você recomendamos as distribuições: ",
          end='')
elif resps[0] == 1:
    print(
        "Ao trilhar esse caminho, um novo guru do Linux irá surgir, as distribuições que servirão de base para seu "
        "aprendizado são: ",
        end='')
else:
    print(
        "Você passará pelo caminho daqueles que decidiram abandonar sua zona de conforto, as distribuições "
        "recomendadas são: ",
        end='')

for i in resps:
    opts = opts[i]

print(opts, end='.\n')
