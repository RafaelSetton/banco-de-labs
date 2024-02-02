#pragma once

#include "peca.h"
#include "node.h"

typedef struct
{
    int tamanho, usado;
    p_node topo;
} *p_pilha;

p_pilha nova_pilha(int tamanho);

void destroi_pilha(p_pilha pilha);

void push(p_peca x, p_pilha pilha);

p_peca pop(p_pilha pilha);

int pilha_cheia(p_pilha pilha);

int pilha_vazia(p_pilha pilha);