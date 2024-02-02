#pragma once

#include "no.h"

typedef struct
{
    p_no items[1000];
    int top;
} *p_stack;

p_stack nova_pilha();

p_no pop(p_stack pilha);

void push(p_stack pilha, p_no novo);
