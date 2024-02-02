#include <stdlib.h>
#include "operador.h"

p_operador novo_operador()
{
    p_operador operador = malloc(sizeof(*operador));
    operador->p = NULL;
    operador->tempo_restante = 0;
    return operador;
}

void destroi_operador(p_operador operador)
{
    free(operador->p);
    free(operador);
}