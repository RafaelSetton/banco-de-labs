#include <stdlib.h>
#include "pilha.h"
#include "peca.h"
#include "node.h"

p_pilha nova_pilha(int tamanho)
{
    p_pilha pilha = malloc(sizeof(*pilha));
    pilha->tamanho = tamanho;
    pilha->usado = 0;
    pilha->topo = NULL;
    return pilha;
}

void destroi_pilha(p_pilha pilha)
{
    free(pilha);
}

void push(p_peca x, p_pilha pilha)
{
    p_node novo = malloc(sizeof(*novo));
    novo->atual = x;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->usado++;
}

p_peca pop(p_pilha pilha)
{
    p_peca p = pilha->topo->atual;
    p_node ant = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    free(ant);

    pilha->usado--;
    return p;
}

int pilha_cheia(p_pilha pilha)
{
    return pilha->usado == pilha->tamanho;
}

int pilha_vazia(p_pilha pilha)
{
    return pilha->usado == 0;
}