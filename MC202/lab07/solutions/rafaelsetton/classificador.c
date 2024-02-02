#include <stdlib.h>
#include "classificador.h"
#include "pilha.h"
#include "esteira.h"

int update_classificador(p_operador classificador, p_pilha pilha, p_esteira esteira)
{
    int concluidas = 0;

    if (classificador->tempo_restante > 0)
        classificador->tempo_restante--;

    if (classificador->tempo_restante == 0 && classificador->p != NULL && !pilha_cheia(pilha))
    {
        // Passa a peça para a pilha
        push(classificador->p, pilha);
        classificador->p = NULL;
        concluidas = 1;
    }

    if (classificador->p == NULL && esteira->qtd_pecas > 0)
        pega_peca_classificador(classificador, esteira);

    return concluidas;
}

void pega_peca_classificador(p_operador classificador, p_esteira esteira)
{
    classificador->p = remover(esteira);

    if (classificador->p->tamanho == 'p')
        classificador->tempo_restante = 1;
    else if (classificador->p->tamanho == 'm')
        classificador->tempo_restante = 2;
    else
        classificador->tempo_restante = 3;
}