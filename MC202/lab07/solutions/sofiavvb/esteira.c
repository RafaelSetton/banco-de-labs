#include <stdio.h>
#include <stdlib.h>
#include "esteira.h"

p_fila criar_fila(int tamanho){
    p_fila fila;
    fila = malloc(sizeof(struct fila));
    fila->v = malloc(tamanho * sizeof(p_peca));
    fila->ini = 0;
    fila->fim = 0;
    fila->tamanho = tamanho;
    fila->ocupado = 0;
    return fila;
}

int enfileira(p_fila fila, p_peca p){
    if (!fila_cheia(fila)){
        fila->v[fila->fim] = p;
        fila->fim = (fila->fim + 1) % fila->tamanho;
        fila->ocupado++;
        return 1;
    }
    return 0;
}

p_peca desenfileira(p_fila fila){
    p_peca p = fila->v[fila->ini];
    fila->ini = (fila->ini + 1) % fila->tamanho;
    fila->ocupado--;
    return p;
}

int fila_vazia(p_fila fila){
    return(fila->ocupado == 0);
}

void destruir_fila(p_fila fila){
    if(fila_vazia(fila)){
        free(fila->v);
        free(fila);
    }
}

int fila_cheia(p_fila fila){
    return(fila->ocupado == fila->tamanho);
}
