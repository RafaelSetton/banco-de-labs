#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

p_pilha criar_pilha(){
    p_pilha pilha = malloc(sizeof(struct pilha));
    pilha->topo = NULL;
    return pilha;
}

int pilha_vazia(p_pilha pilha) {
    return (pilha->topo == NULL);
}

void push(p_pilha pilha, p_no_arv arv){
    p_no_pilha novo = malloc(sizeof(struct no_pilha));
    novo->arvore = arv;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

p_no_arv pop(p_pilha pilha){
    p_no_pilha topo = pilha->topo;
    p_no_arv arv = pilha->topo->arvore;
    pilha->topo = topo->prox;
    free(topo);
    return arv;
}

void destruir_pilha(p_pilha pilha){
    p_no_pilha atual = pilha->topo;
    while (atual != NULL){
        p_no_pilha proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(pilha);
}
