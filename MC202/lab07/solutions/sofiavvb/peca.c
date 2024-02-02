#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "peca.h"

p_peca criar_peca(){
    p_peca p = malloc(sizeof(struct peca));
    p->tempo_pilha = 0;
    scanf("%s", p->tamanho);
    scanf(" %d", &p->classe);
    return p;
}

int tempo_class(p_peca p){
    if (strcmp(p->tamanho, "pequena") == 0){
        return 1;
    }else if (strcmp(p->tamanho, "media") == 0){
        return 2;
    }else if (strcmp(p->tamanho, "grande") == 0){
        return 3;
    }
    return 0;
}
//retorna o tempo para embalar a peca
int tempo_embal(p_peca p){
    if (strcmp(p->tamanho, "pequena") == 0){
        if (p->classe == 1){
            return 1;
        }else{
            return 2;
        }
    }else if (strcmp(p->tamanho, "media") == 0 ||strcmp(p->tamanho, "grande") == 0){
        if (p->classe == 1){
            return 2;
        }else{
            return 3;
        }
    }
    return -1;
}
    
void destruir_pecas(p_peca *pecas, int entradas){
    for (int i = 0; i < entradas; i++){
        free(pecas[i]);
    }
}