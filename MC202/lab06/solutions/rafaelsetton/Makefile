all: livros

livros: livros.o lista.o livro.o
	gcc -g livros.o lista.o livro.o -lm -o livros

livros.o: livros.c lista.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c livros.c

lista.o: lista.c lista.h livro.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c lista.c

livro.o: livro.c livro.h
	gcc -g -std=c99 -Wall -Werror -Wvla -c livro.c

clean:
	rm -rf *.o