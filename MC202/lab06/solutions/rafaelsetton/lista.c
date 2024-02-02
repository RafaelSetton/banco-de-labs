#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include <stdio.h>

void inserir(p_lista l, p_livro novo)
{
    if (l->atual == l->ultimo)
        l->ultimo = novo;
    novo->prox = l->atual->prox;
    l->atual->prox = novo;
    l->atual = novo;
}

void remover(p_lista l, char nome[])
{
    p_livro atual, ant;

    for (atual = l->cabeca; strcmp(atual->nome, nome) != 0; atual = atual->prox)
        ant = atual;

    ant->prox = atual->prox;
    if (l->atual == atual)
        l->atual = ant;
    if (l->ultimo == atual)
        l->ultimo = ant;
    free(atual);
}

p_lista nova_lista()
{
    p_lista l = malloc(sizeof(*l));
    p_livro cabeca = malloc(sizeof(*cabeca));
    cabeca->nome[0] = '\0';
    cabeca->prox = NULL;
    l->cabeca = cabeca;
    l->atual = cabeca;
    l->ultimo = cabeca;
    return l;
}