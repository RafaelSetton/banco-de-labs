#ifndef __PECA_H__
#define __PECA_H__


#define MAX 10

typedef struct peca *p_peca;

struct peca{
    int classe;
    char tamanho[MAX];
    int tempo_pilha;
};
/*cria a peça*/
p_peca criar_peca();
/*retorna o tempo para classificar a peca*/
int tempo_class(p_peca p);
/*retorna o tempo para embalar a peça*/
int tempo_embal(p_peca p);
/*destroi as pecas*/
void destruir_pecas(p_peca *pecas, int entradas);

#endif // __PECA_H__