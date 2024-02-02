#pragma once

#include "peca.h"
#include "esteira.h"
#include "pilha.h"
#include "operador.h"

int update_classificador(p_operador classificador, p_pilha pilha, p_esteira esteira); // Atualiza o classificador em 1 minuto

void pega_peca_classificador(p_operador classificador, p_esteira esteira); // Pega a próxima peça da esteira e define o tempo para classificá-la