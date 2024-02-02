CFLAGS=-std=c99 -Wall -Werror -Wvla -g

all: cozinha

cozinha: cozinha.o fila_prioridade.o 
	gcc cozinha.o fila_prioridade.o -lm -o cozinha

cozinha.o: cozinha.c
	gcc $(CFLAGS) -c cozinha.c

fila_prioridade.o: fila_prioridade.c fila_prioridade.h
	gcc $(CFLAGS) -c fila_prioridade.c