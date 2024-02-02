# -Wall -Werror -Wvla

all: redecomep

redecomep: redecomep.o grafo.o path.o fila.o
	gcc -g redecomep.o grafo.o path.o fila.o -lm -o redecomep

redecomep.o: redecomep.c grafo.h
	gcc -g -std=c99 -c redecomep.c

grafo.o: grafo.c grafo.h
	gcc -g -std=c99 -c grafo.c

fila.o: fila.c fila.h
	gcc -g -std=c99 -c fila.c

path.o: path.c path.h
	gcc -g -std=c99 -c path.c

clean:
	rm -rf *.o