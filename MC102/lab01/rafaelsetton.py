shei = input()
reg = input()

if shei == reg:
    print("empate")
    exit(0)

opts = ["tesoura", "papel", "pedra", "lagarto", "spock"]
wins = [opts[opts.index(shei)-4], opts[opts.index(shei)-2]]

if reg in wins:
    print("Interestelar")
else:
    print("Jornada nas Estrelas")
