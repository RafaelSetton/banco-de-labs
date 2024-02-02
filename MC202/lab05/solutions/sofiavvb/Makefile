CFLAGS=-std=c99 -Wall -Werror -Wvla -g

all: batmemory

batmemory: batmemory.o batimplementation.o
	gcc batmemory.o batimplementation.o -lm -o batmemory

batmemory.o: batmemory.c batmemory.h
	gcc $(CFLAGS) -c batmemory.c

batimplementation.o: batimplementation.c batmemory.h
	gcc $(CFLAGS) -c batimplementation.c