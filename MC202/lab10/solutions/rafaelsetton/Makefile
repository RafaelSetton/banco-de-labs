# -Wall -Werror -Wvla

all: cozinha

cozinha: cozinha.o sobrevivente.o fila.o prato.o
	gcc -g cozinha.o sobrevivente.o fila.o prato.o -lm -o cozinha

cozinha.o: cozinha.c sobrevivente.h fila.h prato.h
	gcc -g -std=c99 -c cozinha.c

prato.o: prato.c prato.h
	gcc -g -std=c99 -c prato.c

fila.o: fila.c fila.h prato.h sobrevivente.h
	gcc -g -std=c99 -c fila.c

sobrevivente.o: sobrevivente.c sobrevivente.h
	gcc -g -std=c99 -c sobrevivente.c

clean:
	rm -rf *.o