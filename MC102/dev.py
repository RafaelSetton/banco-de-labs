import os
from colorama import init, Fore

init()

N_LABS = 13

def adiciona():
    nome = input("Digite seu nome: ")

    for n in range(1, N_LABS+1):
        try:
            os.rename(f"lab{n:02}.py", f"lab{n:02}\\{nome}.py")
        except FileNotFoundError:
            print(Fore.RED, f"Arquivo lab{n:02}.py não encontrado")
        else:
            print(Fore.GREEN, f"Arquivo lab{n:02}.py adicionado")

def checa():
    nome = input("Digite seu nome: ")

    for n in range(1, N_LABS+1):
        if os.path.isfile(f"./lab{n:02}/{nome}.py"):
            print(Fore.GREEN, f"lab{n:02} encontrado")
        else:
            print(Fore.RED, f"lab{n:02} não encontrado")

if __name__ == '__main__':
    checa()