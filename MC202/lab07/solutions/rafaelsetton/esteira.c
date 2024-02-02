#include <stdlib.h>
#include <stdio.h>
#include "esteira.h"
#include "peca.h"

p_esteira nova_esteira(int max_pecas, int total_pecas)
{
    p_esteira esteira = malloc(sizeof(*esteira));
    esteira->v = malloc(max_pecas * sizeof(p_peca));
    esteira->ini = 0;
    esteira->fim = 0;
    esteira->max_pecas = max_pecas;
    esteira->qtd_pecas = 0;
    esteira->pecas_restantes = total_pecas;

    return esteira;
}

void inserir(p_esteira esteira, p_peca nova)
{
    esteira->v[esteira->fim] = nova;
    esteira->fim = (esteira->fim + 1) % esteira->max_pecas;

    esteira->qtd_pecas++;
}

int recebe_nova_peca(p_esteira esteira)
{
    int res = 0;

    if (!esteira_cheia(esteira) && esteira->pecas_restantes > 0)
    {
        char tamanho[10];
        int tipo;
        scanf("%s %d", tamanho, &tipo);
        inserir(esteira, nova_peca(tamanho[0], tipo));
        esteira->pecas_restantes--;
        res = 1;
    }
    return res;
}

p_peca remover(p_esteira esteira)
{
    p_peca p = esteira->v[esteira->ini];
    esteira->ini = (esteira->ini + 1) % esteira->max_pecas;

    esteira->qtd_pecas--;
    return p;
}

int esteira_cheia(p_esteira esteira)
{
    return esteira->qtd_pecas == esteira->max_pecas;
}

int esteira_vazia(p_esteira esteira)
{
    return esteira->qtd_pecas == 0;
}

void destroi_esteira(p_esteira esteira)
{
    free(esteira->v);
    free(esteira);
}