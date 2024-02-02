#include <stdlib.h>
#include "fila.h"

p_fila criar_fila()
{
    p_fila f = malloc(sizeof(*f));
    f->ini = 0;
    f->fim = 0;
    return f;
}

int fila_vazia(p_fila f)
{
    return f->ini == f->fim;
}

void enfileira(p_fila f, int x)
{
    f->v[f->fim] = x;
    f->fim = (f->fim + 1) % 21;
}

int desenfileira(p_fila f)
{
    int res = f->v[f->ini];
    f->ini = (f->ini + 1) % 21;
    return res;
}