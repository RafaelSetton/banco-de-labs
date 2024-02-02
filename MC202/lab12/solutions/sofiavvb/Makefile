CFLAGS=-std=c99 -Wall -Werror -Wvla -g

all: redecomep

redecomep: redecomep.o grafo.o fila.o
	gcc redecomep.o grafo.o fila.o -lm -o redecomep

redecomep.o: redecomep.c
	gcc $(CFLAGS) -c redecomep.c

grafo.o: grafo.c grafo.h
	gcc $(CFLAGS) -c grafo.c

fila.o: fila.c fila.h
	gcc $(CFLAGS) -c fila.c