#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void adicionar(p_lista l, char linha[])
{
    struct livro *novo = malloc(sizeof(struct livro));
    for (int i = 10; linha[i - 1] != '\0'; i++)
        novo->nome[i - 10] = linha[i];

    inserir(l, novo);
}

void final(p_lista l)
{
    l->atual = l->ultimo;
}

void remover_livro(p_lista l, char linha[])
{
    char nome[50];
    int i;
    for (i = 8; linha[i - 1] != '\0'; i++)
        nome[i - 8] = linha[i];
    nome[i - 8] = '\0';
    remover(l, nome);
}

void inicio(p_lista l)
{
    l->atual = l->cabeca;
}

void imprimir(p_lista l)
{
    struct livro *atual;
    for (atual = l->cabeca->prox; atual->prox != NULL; atual = atual->prox)
        imprime(atual, 1);
    imprime(atual, 0);

    printf("\n");
}

int main()
{
    p_lista l = nova_lista();
    char linha[61];
    char *res = fgets(linha, 60, stdin);
    do
    {
        if (linha[0] == 'a') // Adicionar
            adicionar(l, linha);
        else if (linha[0] == 'f') // Final
            final(l);
        else if (linha[0] == 'r') // Remover
            remover_livro(l, linha);
        else if (linha[1] == 'n') // Inicio
            inicio(l);
        else // Imprimir
            imprimir(l);

        res = fgets(linha, 60, stdin);
    } while (res != NULL);

    p_livro ant = l->cabeca;
    for (p_livro atual = l->cabeca->prox; atual != NULL; atual = atual->prox)
    {
        free(ant);
        ant = atual;
    }
    free(ant);
    free(l);
}