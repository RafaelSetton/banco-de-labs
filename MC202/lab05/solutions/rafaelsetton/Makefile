all: batmemory

batmemory: batmemory.o dinamico.o
	gcc batmemory.o dinamico.o -lm -o batmemory

batmemory.o: batmemory.c dinamico.h
	gcc -std=c99 -Wall -Werror -Wvla -c batmemory.c

dinamico.o: dinamico.c dinamico.h
	gcc -std=c99 -Wall -Werror -Wvla -c dinamico.c

clean:
	rm -rf *.o