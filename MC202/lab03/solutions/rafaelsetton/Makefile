all: golfe

golfe: golfe.o circuito.o partida.o
	gcc golfe.o partida.o circuito.o -lm -o golfe

golfe.o: golfe.c circuito.h partida.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c golfe.c

partida.o: partida.c partida.h circuito.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c partida.c

circuito.o: circuito.c circuito.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c circuito.c

clean:
	rm -rf *.o