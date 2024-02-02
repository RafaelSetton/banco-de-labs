//interface
#include "circuito.h"

typedef struct partida{
    float aluguel;
    int identificacao, participantes, n_circuitos,
    equipamentos;
    circuito *circuitos;
}partida;

partida ler_partida(int identificacao);

void imprime_relatorio(partida a);

partida *aloca_partidas(int numero_partidas);

void libera_circuitos(partida a);

float calcula_aluguel(partida a);

