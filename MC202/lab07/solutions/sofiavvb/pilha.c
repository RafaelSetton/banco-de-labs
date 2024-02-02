#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

p_pilha criar_pilha(int tamanho){
    p_pilha pilha = malloc(sizeof(struct pilha));
    pilha->topo = NULL;
    pilha->tamanho = tamanho;
    pilha->ocupado = 0;
    return pilha;
}

void push(p_pilha pilha, p_peca p){
    p_no novo = malloc(sizeof(struct no));
    novo->peca = p;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->ocupado++;
}

p_peca pop(p_pilha pilha){
    p_no topo = pilha->topo;
    p_peca p = topo->peca;
    pilha->topo = pilha->topo->prox;
    pilha->ocupado--;
    free(topo);
    return p;
}

int pilha_vazia(p_pilha pilha){
    return(pilha->topo == NULL);
}

int pilha_cheia(p_pilha pilha){
    return(pilha->ocupado == pilha->tamanho);
}

void destruir_pilha(p_pilha pilha){
    p_no atual = pilha->topo;
    while (atual != NULL){
        p_no proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(pilha);
}
