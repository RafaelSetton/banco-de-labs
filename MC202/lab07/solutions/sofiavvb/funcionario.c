#include <stdio.h>
#include "funcionario.h"

funcionario criar_funcionario(){
    funcionario f;
    f.tempo_ocupado = 0;
    f.livre = 1;
    f.peca_trabalho = NULL;
    return f;
}

int livre(funcionario f){
    return f.livre == 1;
}

void trabalhando(funcionario *f){
    f->tempo_ocupado++;
}

void embalar(funcionario *emb, p_pilha pilha){
    emb->peca_trabalho = pop(pilha);
    emb->tempo_ocupado = 1;
    emb->livre = 0;
}

void classificar(funcionario *class, p_fila fila){
    class->peca_trabalho = desenfileira(fila);
    class->livre = 0;
    class->tempo_ocupado = 1;
}