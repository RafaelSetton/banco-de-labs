#include "path.h"
#include <stdlib.h>

p_path novo_caminho()
{
    p_path p = malloc(sizeof(struct path));
    p->n = 0;
    return p;
}

void adiciona(p_path p, int x)
{
    p->v[p->n] = x;
    p->n++;
}

int pop(p_path p)
{
    return p->v[--(p->n)];
}

void reseta(p_path p)
{
    p->n = 0;
}

int contem(p_path p, int x)
{
    // Retorna 1 se x está contido no caminho
    for (int i = 0; i < p->n; i++)
        if (p->v[i] == x)
            return 1;
    return 0;
}