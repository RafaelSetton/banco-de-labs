#include <stdlib.h>
#include "embalador.h"

int update_embalador(p_operador embalador, p_pilha pilha)
{
    int concluidas = 0;

    if (embalador->tempo_restante > 0)
        embalador->tempo_restante--;

    if (embalador->tempo_restante == 0 && embalador->p != NULL)
    {
        // Remove a peça concluida
        free(embalador->p);
        embalador->p = NULL;
        concluidas = 1;
    }

    if (embalador->p == NULL && pilha->usado > 0)
        pega_peca_embalador(embalador, pilha);

    return concluidas;
}

void pega_peca_embalador(p_operador embalador, p_pilha pilha)
{
    embalador->p = pop(pilha);

    if (embalador->p->tamanho == 'p')
    {
        if (embalador->p->tipo == 1)
            embalador->tempo_restante = 1;
        else
            embalador->tempo_restante = 2;
    }
    else
    {
        if (embalador->p->tipo == 1)
            embalador->tempo_restante = 2;
        else
            embalador->tempo_restante = 3;
    }
}