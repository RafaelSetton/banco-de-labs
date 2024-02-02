#include "sobrevivente.h"
#include <stdlib.h>
#include <stdio.h>

p_sob novo_sobrevivente(int id)
{
    p_sob sob = malloc(sizeof(*sob));

    scanf("%s ", sob->nome);
    scanf("%s ", sob->sobrenome);
    scanf("%d", &(sob->dias));
    sob->id = id;

    return sob;
}
