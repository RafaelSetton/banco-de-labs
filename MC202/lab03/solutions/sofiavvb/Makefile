all: golfe

golfe: golfe.o circuito.o
	gcc golfe.o circuito.o partida.o -lm -o golfe

golfe.o: golfe.c
	gcc -std=c99 -Wall -Werror -Wvla -c golfe.c

circuito.o: circuito.c circuito.h
	gcc -std=c99 -Wall -Werror -Wvla -c circuito.c

partida.o: partida.c partida.h
	gcc -std=c99 -Wall -Werror -Wvla -c partida.c