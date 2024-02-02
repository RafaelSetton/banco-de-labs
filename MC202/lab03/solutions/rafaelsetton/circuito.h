#ifndef CIRCUITO_H
#define CIRCUITO_H

typedef struct
{
    int id;
    int n_participantes;
    int *jogadas_participante;
} circuito;

circuito novo_circuito(int id, int n_participantes, int *v);

void free_circuito(circuito *c);

#endif