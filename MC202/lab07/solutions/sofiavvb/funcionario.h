#ifndef __FUNCIONARIO_H__
#define __FUNCIONARIO_H__

#include "peca.h"
#include "pilha.h"
#include "esteira.h"

typedef struct funcionario funcionario;

struct funcionario{
    int tempo_ocupado;
    p_peca peca_trabalho;
    int livre;
};

/*se ele ta livre retorna 1*/
int livre(funcionario f);
/*inicializa o funcionario*/
funcionario criar_funcionario();
/*atualiza o tempo dele ocupado*/
void trabalhando(funcionario *f);
/*embalador recebe a peça, fica ocupado*/
void embalar(funcionario *emb, p_pilha pilha);
/*classificador recebe peça, fica ocupado*/
void classificar(funcionario *class, p_fila );

#endif // __FUNCIONARIO_H__