#ifndef PARTIDA_H
#define PARTIDA_H

#include "circuito.h"

typedef struct
{
    float aluguel;
    int id;
    int n_participantes;
    int n_circuitos;
    int n_equipamentos;
    circuito *circuitos;
    int idx_proximo_circuito;
} partida;

void imprime_dados(partida p);

partida nova_partida(int n_jogadores, int n_circuitos, int n_equipamentos);

void adiciona_circuito(partida *p, circuito c);

void free_partida(partida *p);

#endif