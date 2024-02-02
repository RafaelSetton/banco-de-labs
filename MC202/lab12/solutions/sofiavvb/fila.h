#ifndef __FILA_H__
#define __FILA_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct fila *p_fila;

struct fila{
    int *v;
    int ini, fim, tamanho, ocupado;
};
//cria a fila
p_fila criar_fila(int tamanho);
//adiciona no final da fila
int enfileira(p_fila fila, int p);
//remove do inicio da fila
int desenfileira(p_fila fila);
//checa se a fila esta vazia, retorna true nesse caso
int fila_vazia(p_fila fila);
//destroi a fila
void destruir_fila(p_fila fila);
//checa se a fila ta cheia
int fila_cheia(p_fila fila);

#endif // __FILA_H__