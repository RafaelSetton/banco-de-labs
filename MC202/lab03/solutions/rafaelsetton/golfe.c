#include <stdio.h>
#include <stdlib.h>

#include "partida.h"
#include "circuito.h"

int main()
{
    int n_partidas;
    scanf("%d ", &n_partidas);

    int n_jogadores, n_circuitos, n_equipamentos;
    for (int i = 0; i < n_partidas; i++)
    {
        scanf("%d %d %d ", &n_jogadores, &n_circuitos, &n_equipamentos);
        int id_circuito, *n_jogadas;
        n_jogadas = malloc(n_jogadores * sizeof(int));
        partida p = nova_partida(n_jogadores, n_circuitos, n_equipamentos);
        for (int j = 0; j < n_circuitos; j++)
        {
            scanf("%d", &id_circuito);
            for (int k = 0; k < n_jogadores; k++)
                scanf("%d", &n_jogadas[k]);
            circuito c = novo_circuito(id_circuito, n_jogadores, n_jogadas);
            adiciona_circuito(&p, c);
        }
        free(n_jogadas);
        imprime_dados(p);
        free_partida(&p);
    }
}