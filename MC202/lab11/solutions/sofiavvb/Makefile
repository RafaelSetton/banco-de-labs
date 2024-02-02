CFLAGS=-std=c99 -Wall -Werror -Wvla -g

all: halloween

halloween: halloween.o hashnopolis.o 
	gcc halloween.o hashnopolis.o -lm -o halloween

halloween.o: halloween.c
	gcc $(CFLAGS) -c halloween.c

hashnopolis.o: hashnopolis.c hashnopolis.h
	gcc $(CFLAGS) -c hashnopolis.c