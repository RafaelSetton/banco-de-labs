#include "fila.h"

p_fila criar_fila(int tamanho){
    p_fila fila;
    fila = malloc(sizeof(struct fila));
    fila->v = malloc(tamanho * sizeof(int));
    fila->ini = 0;
    fila->fim = 0;
    fila->tamanho = tamanho;
    fila->ocupado = 0;
    return fila;
}

int enfileira(p_fila fila, int p){
    if (!fila_cheia(fila)){
        fila->v[fila->fim] = p;
        fila->fim = (fila->fim + 1) % fila->tamanho;
        fila->ocupado++;
        return 1;
    }
    return 0;
}

int desenfileira(p_fila fila){
    int p = fila->v[fila->ini];
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