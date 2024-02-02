#include "prato.h"

struct FP
{
    p_prato *v;
    int n, tamanho;
};

typedef struct FP *p_fp;

#define PAI(i) ((i - 1) / 2)
#define F_ESQ(i) (2 * i + 1)
#define F_DIR(i) (2 * i + 2)

p_fp nova_fila();

void troca(p_prato *a, p_prato *b);

void sobe_no_heap(p_fp fprio, int k);

void desce_no_heap(p_fp fprio, int k);

void insere(p_fp fprio, p_prato item);

p_prato extrai_maximo(p_fp fprio);

int acha_prato(p_fp fila, int id); // Retorna o índice do prato cujo dono tem id=id

void destroi_fila(p_fp fila);