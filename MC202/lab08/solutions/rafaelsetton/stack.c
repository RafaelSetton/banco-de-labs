#include <stdlib.h>
#include "stack.h"

p_stack nova_pilha()
{
    p_stack pilha = malloc(sizeof(*pilha));
    pilha->top = -1;
    return pilha;
}

p_no pop(p_stack pilha)
{
    return pilha->items[pilha->top--];
}

void push(p_stack pilha, p_no novo)
{
    pilha->items[++pilha->top] = novo;
}