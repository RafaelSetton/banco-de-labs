#pragma once

#include "peca.h"

typedef struct
{
    int ini, fim, qtd_pecas, max_pecas, pecas_restantes;
    p_peca *v;
} *p_esteira;

p_esteira nova_esteira(int max_pecas, int total_pecas);

int recebe_nova_peca(p_esteira esteira); // Tenta inserir uma nova peça a partir de stdout. Retorna 1 se houve sucesso e 0 caso contrário

p_peca remover(p_esteira esteira); // Remove a última peça da esteira

int esteira_cheia(p_esteira esteira);

int esteira_vazia(p_esteira esteira);

void destroi_esteira(p_esteira esteira);