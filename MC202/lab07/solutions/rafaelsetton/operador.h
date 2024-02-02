#pragma once

#include "peca.h"

typedef struct
{
    int tempo_restante;
    p_peca p;
} *p_operador;

p_operador novo_operador();

void destroi_operador(p_operador operador);