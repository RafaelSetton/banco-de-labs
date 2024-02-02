#include "dinamico.h"
#include <stdlib.h>
#include <stdio.h>

int min(int a, int b)
{ // Calcula o mínimo de dois números
    return a < b ? a : b;
}

dinamico novo_vetor_dinamico()
{
    dinamico vetor;
    vetor.alocado = 8;
    vetor.v = malloc(sizeof(int) * 8);
    vetor.inicios = calloc(8, sizeof(int));
    vetor.ocupado = 0;
    return vetor;
}

void copia(dinamico *vetor, int tamanho_antigo)
{ // Realoca o vetor inteiro para alterar seu tamanho
    int *v_velho, *ini_velho;
    v_velho = vetor->v;
    ini_velho = vetor->inicios;
    vetor->v = malloc(sizeof(int) * vetor->alocado);
    vetor->inicios = calloc(vetor->alocado, sizeof(int));

    for (int i = 0; i < min(vetor->alocado, tamanho_antigo); i++)
    {
        vetor->v[i] = v_velho[i];
        vetor->inicios[i] = ini_velho[i];
    }

    free(v_velho);
    free(ini_velho);
}

void aumenta(dinamico *vetor)
{
    vetor->alocado *= 2;
    copia(vetor, vetor->alocado / 2);
}

void otimiza(dinamico *vetor)
{
    for (int i = 0; i < vetor->alocado; i++)
        if ((i + vetor->inicios[i] >= vetor->alocado / 4) && (vetor->inicios[i] != 0))
            return; // Há espaço ocupado depois de um quarto;

    vetor->alocado /= 2;
    copia(vetor, vetor->alocado * 2);
}

int encontra(dinamico *vetor, int tamanho)
{
    int comeco = 0;
    for (int i = 0; i < vetor->alocado; i++)
    {
        if (vetor->inicios[i])
        {
            i += vetor->inicios[i];
            comeco = i + 1;
            continue;
        }
        if (i - comeco >= tamanho)
            return comeco;
    }
    return -1;
}

void libera(dinamico *vetor, int endereco)
{
    vetor->ocupado -= vetor->inicios[endereco] + 1;
    vetor->inicios[endereco] = 0;
}

void insere(dinamico *vetor, int posicao, int tamanho, int *valores)
{
    vetor->ocupado += tamanho + 1;
    vetor->v[posicao] = tamanho;
    vetor->inicios[posicao] = tamanho;
    for (int i = 0; i < tamanho; i++)
        vetor->v[posicao + i + 1] = valores[i];
}
