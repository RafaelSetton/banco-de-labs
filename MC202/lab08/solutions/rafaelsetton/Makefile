all: expressoes

expressoes: expressoes.o no.o stack.o
	gcc -g expressoes.o no.o stack.o -lm -o expressoes

no.o: no.c no.h stack.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c no.c

stack.o: stack.c stack.h no.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c stack.c

expressoes.o: expressoes.c no.h stack.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c expressoes.c

clean:
	rm -rf *.o