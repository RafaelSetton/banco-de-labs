#pragma once

#include "peca.h"
#include "esteira.h"
#include "pilha.h"
#include "operador.h"

int update_embalador(p_operador embalador, p_pilha pilha); // Atualiza o embalador em 1 minuto

void pega_peca_embalador(p_operador embalador, p_pilha pilha); // Pega a próxima peça da pilha e define o tempo para embalá-la