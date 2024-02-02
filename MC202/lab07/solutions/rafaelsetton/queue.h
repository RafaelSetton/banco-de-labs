#pragma once

#include "peca.h"

// Cada elemento na esteira

struct queue
{
    p_peca atual;
    struct queue *proximo;
    struct queue *anterior;
};

typedef struct queue *p_queue;
