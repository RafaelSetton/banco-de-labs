#pragma once
#include "sobrevivente.h"

struct prato
{
    p_sob dono;
    char nome[30];
    int prioridade;
};

typedef struct prato *p_prato;

p_prato novo_prato(p_sob dono, char nome[]); // Cria um prato

void altera(p_prato prato, int valor); // Altera a prioriade do prato
