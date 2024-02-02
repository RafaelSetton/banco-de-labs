#include "livro.h"

typedef struct
{
    p_livro cabeca;
    p_livro ultimo;
    p_livro atual;
} *p_lista;

void inserir(p_lista l, p_livro novo);

void remover(p_lista l, char nome[]);

p_lista nova_lista();
