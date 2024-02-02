#include <string.h>
#include <stdlib.h>
#include "hash.h"

int hash(char *chave)
{
    int i, n = 0;

    for (i = 0; chave[i] != '\0'; i++)
        n = (256 * n + chave[i]) % MAX;
    return n;
}

p_hash criar_hash()
{
    p_hash t = malloc(sizeof(*t));
    for (int i = 0; i < MAX; i++)
        t->utilizado[i] = 0;
    return t;
}

void destruir_hash(p_hash t)
{
    for (int i = 0; i < MAX; i++)
        if (t->utilizado[i])
            free(t->vetor[i]);

    free(t);
}

void inserir(p_hash t, char *sobrenome, int qtd_doces)
{
    p_familia nova = malloc(sizeof(struct familia));
    nova->qtd_doces = qtd_doces;
    for (int i = 0; i < 10; i++)
        nova->sobrenome[i] = sobrenome[i];

    for (int i = hash(sobrenome); 1; i = (i + 1) % MAX)
        if (!t->utilizado[i])
        {
            t->utilizado[i] = 1;
            t->vetor[i] = nova;
            return;
        }
}

void remover(p_hash t, char *sobrenome)
{
    for (int i = hash(sobrenome); 1; i = (i + 1) % MAX)
        if (t->utilizado[i] && strcmp(t->vetor[i]->sobrenome, sobrenome) == 0)
        {
            t->utilizado[i] = 0;
            free(t->vetor[i]);
            return;
        }
}

p_familia buscar(p_hash t, char *sobrenome)
{
    for (int i = hash(sobrenome); 1; i = (i + 1) % MAX)
        if (t->utilizado[i] && strcmp(t->vetor[i]->sobrenome, sobrenome) == 0)
            return t->vetor[i];
}