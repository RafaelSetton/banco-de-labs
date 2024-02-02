#pragma once

#include "peca.h"

struct node
{
    p_peca atual;
    struct node *proximo;
};

typedef struct node *p_node;
