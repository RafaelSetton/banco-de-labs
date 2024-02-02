#pragma once

typedef struct
{
    int ini, fim;
    int v[21];
} *p_fila;

p_fila criar_fila();

int fila_vazia(p_fila f);

void enfileira(p_fila f, int x);

int desenfileira(p_fila f);