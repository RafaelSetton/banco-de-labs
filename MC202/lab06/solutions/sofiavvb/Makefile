CFLAGS=-std=c99 -Wall -Werror -Wvla -g

all: livros

livros: livros.o lista.o
	gcc livros.o lista.o -lm -o livros

livros.o: livros.c lista.h
	gcc $(CFLAGS) -c livros.c

lista.o: lista.c lista.h
	gcc $(CFLAGS) -c lista.c