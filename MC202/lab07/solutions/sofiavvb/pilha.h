#ifndef __PILHA_H__
#define __PILHA_H__

#include "peca.h"

typedef struct pilha *p_pilha;
typedef struct no *p_no;

struct no {
    p_peca peca;
    p_no prox;
};

struct pilha{
    p_no topo;
    int ocupado, tamanho;
};
//aloca a pilha e inicializa como vazia
p_pilha criar_pilha(int tamanho);
//insere no inicio
void push(p_pilha pilha, p_peca p);
//remove do inicio
p_peca pop(p_pilha pilha);
//checa se a pilha ta vazia, retornando true se sim
int pilha_vazia(p_pilha pilha);
//checa se a pilha esta cheia, retornando true se sim
int pilha_cheia(p_pilha pilha);
//destroi a estrutura da pilha, liberando seus nós
void destruir_pilha(p_pilha pila);

#endif // __PILHA_H__