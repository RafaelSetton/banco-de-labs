CFLAGS=-std=c99 -Wall -Werror -Wvla -g

all: simulador

simulador: simulador.o esteira.o pilha.o funcionario.o peca.o
	gcc simulador.o esteira.o pilha.o funcionario.o peca.o -lm -o simulador

simulador.o: simulador.c
	gcc $(CFLAGS) -c simulador.c

pilha.o: pilha.c pilha.h
	gcc $(CFLAGS) -c pilha.c

esteira.o: esteira.c esteira.h
	gcc $(CFLAGS) -c esteira.c

funcionario.o: funcionario.c funcionario.h
	gcc $(CFLAGS) -c funcionario.c

peca.o: peca.c peca.h
	gcc $(CFLAGS) -c peca.c


