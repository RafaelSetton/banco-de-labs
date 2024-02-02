CFLAGS=-std=c99 -Wall -Werror -Wvla -g

all: expressoes

expressoes: expressoes.o arvore.o pilha.o 
	gcc expressoes.o arvore.o pilha.o -lm -o expressoes

expressoes.o: expressoes.c
	gcc $(CFLAGS) -c expressoes.c

pilha.o: pilha.c pilha.h
	gcc $(CFLAGS) -c pilha.c

arvore.o: arvore.c arvore.h
	gcc $(CFLAGS) -c arvore.c