CFLAGS=-std=c99 -Wall -Werror -Wvla -g

all: dracarys

dracarys: dracarys.o arvore.o 
	gcc dracarys.o arvore.o -lm -o dracarys

dracarys.o: dracarys.c
	gcc $(CFLAGS) -c dracarys.c

arvore.o: arvore.c arvore.h
	gcc $(CFLAGS) -c arvore.c