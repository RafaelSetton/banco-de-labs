#ifndef __PILHA_H__
#define __PILHA_H__

#include "arvore.h"

typedef struct pilha *p_pilha;
typedef struct no_pilha *p_no_pilha;

struct no_pilha {
    p_no_arv arvore;
    p_no_pilha prox;
};

struct pilha{
    p_no_pilha topo;
};
//aloca a pilha e inicializa como vazia
p_pilha criar_pilha();
//insere no inicio
void push(p_pilha pilha, p_no_arv);
//remove do inicio
p_no_arv pop(p_pilha pilha);
//checa se a pilha ta vazia, retornando true se sim
int pilha_vazia(p_pilha pilha);
//destroi a estrutura da pilha, liberando seus nós
void destruir_pilha(p_pilha pilha);

#endif // __PILHA_H__