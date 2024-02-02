#include <stdlib.h>
#include <string.h>
#include "prato.h"

p_prato novo_prato(p_sob dono, char nome[])
{
    p_prato prato = malloc(sizeof(*prato));
    prato->dono = dono;
    strcpy(prato->nome, nome);
    prato->prioridade = dono->dias;
}

void altera(p_prato prato, int valor)
{
    prato->prioridade += valor;
}