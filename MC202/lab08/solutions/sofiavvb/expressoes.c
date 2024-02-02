#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#define MAX 1000

int main(){

    int n_expr = 0;
    char expressao[MAX];
    scanf("%d", &n_expr);

    for (int i = 0; i < n_expr; i++){
        scanf("%s", expressao);
        p_no_arv raiz = criar_arvore(expressao);
        imprimir_arvore(raiz);
        raiz = otimizar_arvore(raiz);
        imprimir_arvore(raiz);
        destruir_arvore(raiz);
        printf("\n");
    }
    return 0;
}