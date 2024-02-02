#include <stdlib.h>
#include "peca.h"

p_peca nova_peca(char tamanho, int tipo)
{
    p_peca p = malloc(sizeof(*p));
    p->tamanho = tamanho;
    p->tipo = tipo;
    return p;
}