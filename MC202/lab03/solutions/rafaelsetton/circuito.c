#include "circuito.h"
#include <stdlib.h>

circuito novo_circuito(int id, int n_participantes, int *v)
{
    circuito c;
    c.id = id;
    c.n_participantes = n_participantes;
    c.jogadas_participante = malloc(n_participantes * sizeof(int));
    for (int i = 0; i < n_participantes; i++)
        c.jogadas_participante[i] = v[i];
    return c;
}

void free_circuito(circuito *c) {
    free(c->jogadas_participante);
}