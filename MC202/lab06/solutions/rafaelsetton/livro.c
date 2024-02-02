#include <stdio.h>
#include "livro.h"

void imprime(p_livro l, int virgula)
{
    for (int i = 0; i < 60; i++)
    {
        if (l->nome[i] == '\0' || l->nome[i] == '\n')
            break;
        printf("%c", l->nome[i]);
    }
    if (virgula != 0)
        printf(", ");
}