# -Wall -Werror -Wvla

all: halloween

halloween: halloween.o hash.o
	gcc -g halloween.o hash.o -lm -o halloween

halloween.o: halloween.c hash.h
	gcc -g -std=c99 -c halloween.c

hash.o: hash.c hash.h
	gcc -g -std=c99 -c hash.c

clean:
	rm -rf *.o