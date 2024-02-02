import os
from sys import argv
from colorama import init, Fore
from inspect import isfunction

init()

N_LABS = 13

def adiciona():
    nome = input("Digite seu nome: ")

    for n in range(1, N_LABS+1):
        try:
            os.rename(f"lab{n:02}.py", os.path.join(f"lab{n:02}",f"{nome}.py"))
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

def enunciados():
    for n in range(1, N_LABS+1):
        try:
            os.rename(f"Lab {n:02}.pdf", os.path.join(f"lab{n:02}","enunciado.pdf"))
        except FileNotFoundError:
            print(Fore.RED, f"Arquivo Lab {n:02}.pdf não encontrado")
        else:
            print(Fore.GREEN, f"Arquivo Lab {n:02}.pdf adicionado")

if __name__ == '__main__':
    if len(argv) < 2:
        print("Escolha o modo")
    else:
        exec(f"{argv[1]}()")