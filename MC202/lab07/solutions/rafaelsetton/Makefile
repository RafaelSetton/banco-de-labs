all: simulador

simulador: simulador.o pilha.o esteira.o embalador.o classificador.o operador.o peca.o
	gcc -g simulador.o pilha.o esteira.o embalador.o classificador.o operador.o peca.o -lm -o simulador

pilha.o: pilha.c pilha.h peca.h node.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c pilha.c

esteira.o: esteira.c esteira.h peca.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c esteira.c

embalador.o: embalador.c embalador.h pilha.h operador.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c embalador.c

classificador.o: classificador.c classificador.h pilha.h esteira.h operador.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c classificador.c

operador.o: operador.c operador.h peca.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c operador.c

peca.o: peca.c peca.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c peca.c

simulador.o: simulador.c esteira.h pilha.h embalador.h classificador.h operador.h peca.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c simulador.c

clean:
	rm -rf *.o