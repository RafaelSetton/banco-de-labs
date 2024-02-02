#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "no.h"

p_no novo_no(char simbolo[], char tipo[])
{
    p_no no = malloc(sizeof(*no));

    no->dir = NULL;
    no->esq = NULL;

    for (int i = 0; i < 200; i++)
        if (simbolo[i] == ';')
        {
            no->simbolo[i] = '\000';
            break;
        }
        else
            no->simbolo[i] = simbolo[i];

    for (int i = 0; i < 20; i++)
        no->tipo[i] = tipo[i];

    return no;
}

int ehVermelho(p_no no)
{
    if (no == NULL)
        return 0;
    return no->cor == VERMELHO;
}

int ehPreto(p_no no)
{
    if (no == NULL)
        return 1;
    return no->cor == PRETO;
}

p_no rotaciona_para_esquerda(p_no raiz)
{
    p_no x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

p_no rotaciona_para_direita(p_no raiz)
{
    p_no x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

void sobe_vermelho(p_no raiz)
{
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

int nocmp(p_no no1, p_no no2)
{
    return strcmp(no1->simbolo, no2->simbolo);
}

p_no inserir_rec(p_no raiz, p_no novo)
{
    if (raiz == NULL)
        return novo;

    if (nocmp(novo, raiz) < 0)
        raiz->esq = inserir_rec(raiz->esq, novo);
    else
        raiz->dir = inserir_rec(raiz->dir, novo);

    if (ehVermelho(raiz->dir) && ehPreto(raiz->esq))
        raiz = rotaciona_para_esquerda(raiz);
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->esq->esq))
        raiz = rotaciona_para_direita(raiz);
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->dir))
        sobe_vermelho(raiz);

    return raiz;
}

p_no inserir(p_no raiz, char simbolo[], char tipo[])
{
    raiz = inserir_rec(raiz, novo_no(simbolo, tipo));
    raiz->cor = PRETO;
    return raiz;
}

void imprimir(p_no raiz)
{
    if (raiz == NULL)
        return;
    imprimir(raiz->esq);
    printf("%s %s\n", raiz->simbolo, raiz->tipo);
    imprimir(raiz->dir);
}

p_no buscar(p_no raiz, char simbolo[])
{
    if (raiz == NULL)
        return raiz;

    int cmp = strcmp(raiz->simbolo, simbolo);
    if (cmp == 0)
        return raiz;
    else if (cmp > 0)
        return buscar(raiz->esq, simbolo);
    else
        return buscar(raiz->dir, simbolo);
}

void destroi(p_no raiz)
{
    if (raiz == NULL)
        return;
    destroi(raiz->dir);
    destroi(raiz->esq);
    free(raiz);
}
