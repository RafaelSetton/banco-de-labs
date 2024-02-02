all: dracarys

dracarys: dracarys.o no.o
	gcc -g dracarys.o no.o -lm -o dracarys

no.o: no.c no.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c no.c

dracarys.o: dracarys.c no.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c dracarys.c

clean:
	rm -rf *.o