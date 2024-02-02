#include "partida.h"
#include <stdlib.h>
#include <stdio.h>

int id_atual = 1;

void imprime_dados(partida p)
{
    /* printf("DEBUG:\n");

    printf("%f %d %d %d %d %d", p.aluguel, p.id, p.idx_proximo_circuito, p.n_circuitos, p.n_equipamentos, p.n_participantes);

    printf("END\n\n"); */
    
    printf("Partida %d\n", p.id);
    printf("Num. de Jogadores: %d - Num. de Circuitos: %d - Num. de Equipamentos: %d\n", p.n_participantes, p.n_circuitos, p.n_equipamentos);
    printf("Valor do Aluguel: R$ %.2f\n", p.aluguel); 
    for (int i = 0; i < p.n_participantes; i++)
    {
        int tot = 0;
        for (int j = 0; j < p.n_circuitos; j++)
            tot += p.circuitos[j].jogadas_participante[i];
        printf("Jogador %d: %d\n", i + 1, tot);
    }

    int dificil, tot = 0, este;
    for (int i = 0; i < p.n_circuitos; i++)
    {
        este = 0;
        for (int j = 0; j < p.n_participantes; j++)
            este += p.circuitos[i].jogadas_participante[j];
        if (este > tot)
        {
            dificil = i;
            tot = este;
        }
    }

    printf("Circuito mais dificil: %d\n", p.circuitos[dificil].id);
    printf("##########\n");
}

partida nova_partida(int n_jogadores, int n_circuitos, int n_equipamentos)
{
    partida p;
    p.id = id_atual++;

    p.n_participantes = n_jogadores;
    p.n_circuitos = n_circuitos;
    p.n_equipamentos = n_equipamentos;
    p.aluguel = 10 * n_circuitos + 17.5 * n_equipamentos;
    p.circuitos = malloc(n_circuitos * sizeof(circuito));
    p.idx_proximo_circuito = 0;

    return p;
}

void adiciona_circuito(partida *p, circuito c)
{
    p->circuitos[p->idx_proximo_circuito] = c;
    p->idx_proximo_circuito++;
}

void free_partida(partida *p)
{ 
    for (int i=0; i<p->n_circuitos; i++)
        free_circuito(&(p->circuitos[i]));
    free(p->circuitos);
}