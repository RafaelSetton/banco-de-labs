#include <stdlib.h>
#include "prato.h"
#include "fila.h"

p_fp nova_fila()
{
    p_fp fila = malloc(sizeof(*fila));
    fila->n = 0;
    fila->tamanho = 1e5;
    fila->v = malloc(sizeof(p_prato) * fila->tamanho);
    return fila;
}

void troca(p_prato *a, p_prato *b)
{
    p_prato t = *a;
    *a = *b;
    *b = t;
}

void sobe_no_heap(p_fp fprio, int k)
{
    if (k > 0 && fprio->v[PAI(k)]->prioridade < fprio->v[k]->prioridade)
    {
        troca(&fprio->v[k], &fprio->v[PAI(k)]);
        sobe_no_heap(fprio, PAI(k));
    }
}

void desce_no_heap(p_fp fprio, int k)
{
    if (F_ESQ(k) >= fprio->n)
        return;

    int maior_filho = F_ESQ(k);
    if (F_DIR(k) < fprio->n &&
        fprio->v[F_ESQ(k)]->prioridade < fprio->v[F_DIR(k)]->prioridade)
        maior_filho = F_DIR(k);

    if (fprio->v[k]->prioridade < fprio->v[maior_filho]->prioridade)
    {
        troca(&fprio->v[k], &fprio->v[maior_filho]);
        desce_no_heap(fprio, maior_filho);
    }
}

void insere(p_fp fprio, p_prato item)
{
    fprio->v[fprio->n] = item;
    fprio->n++;
    sobe_no_heap(fprio, fprio->n - 1);
}

p_prato extrai_maximo(p_fp fprio)
{
    p_prato item = fprio->v[0];
    troca(&fprio->v[0], &fprio->v[fprio->n - 1]);
    fprio->n--;
    desce_no_heap(fprio, 0);
    return item;
}

int acha_prato(p_fp fila, int id)
{
    for (int i = 0; i < fila->n; i++)
        if (fila->v[i]->dono->id == id)
            return i;
}

void destroi_fila(p_fp fila)
{
    free(fila->v);
    free(fila);
}