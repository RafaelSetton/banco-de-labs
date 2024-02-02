#pragma once

struct sobrevivente
{
    char nome[20], sobrenome[20];
    int dias, id;
};

typedef struct sobrevivente *p_sob;

p_sob novo_sobrevivente(int id);