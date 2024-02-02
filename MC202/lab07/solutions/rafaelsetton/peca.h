#pragma once

typedef struct
{
    char tamanho;
    int tipo;
} *p_peca;

p_peca nova_peca(char tamanho, int tipo);