#include "arvore.h"
#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>

void inordem(p_no_arv raiz) {
    if (raiz != NULL) {
        /*se o no é operador printamos parenteses antes*/
        if(eh_operador(raiz->dado)){
            printf("(");
        }
        /*printa em inordem a expressao da sub-arvore esq*/
        inordem(raiz->esq);
        /*se o no é operador printamos ele com espaços*/
        if(eh_operador(raiz->dado)){
            printf(" %c ", raiz ->dado); /* visita raiz */
        }else{
            /*caso contrario, printa o operando*/
            printf("%c", raiz ->dado); /* visita raiz */
        }
        /*printa em inordem a expressao da sub-arvore dir*/
        inordem(raiz ->dir);
        /*se o no é operador printamos parenteses depois*/
        if(eh_operador(raiz->dado)){
            printf(")");
        }
    }
}

void imprimir_arvore(p_no_arv raiz) {
    inordem(raiz);
    printf("\n");
}

p_no_arv criar_no_arv(char dado){
    p_no_arv novo = malloc(sizeof(struct no_arv));
    novo->dado = dado;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

int eh_variavel(char dado){
    return (dado >= 'a' && dado <= 'z');
}

int eh_numero(char dado){
    return (dado >= '0' && dado <= '9');
}

int eh_operador(char dado){
    return (dado == '>' || dado == '<' || dado == '!' ||
    dado == '=' || dado == '|'  || dado == '{' || dado == '}' ||
    dado == '&');
}

int eh_const_logica(char dado){
    return (dado == 'T' || dado == 'F');
}

p_no_arv criar_arvore(char expressao[]){
    p_pilha pilha = criar_pilha();

    for (int i = 0; expressao[i] != '\0'; i++){
        char dado = expressao[i];
        /*se for uma variavel ou um numero*/
        if (!eh_operador(dado)){ 
            p_no_arv no = criar_no_arv(dado);
            push(pilha, no);
        }else{
            p_no_arv no = criar_no_arv(dado);
            no->dir = pop(pilha);
            no->esq = pop(pilha);
            push(pilha, no);
        }
    }
    /*a ultima coisa que sobrar na pilha eh a raiz*/
    p_no_arv raiz = pop(pilha);
    destruir_pilha(pilha);
    return raiz;
}

p_no_arv otimizar_arvore(p_no_arv raiz){
    /*se o no eh NULL, eh numero ou variavel, ele ja ta otimizado*/
    if (raiz == NULL || eh_numero(raiz->dado) || eh_variavel(raiz->dado)|| eh_const_logica(raiz->dado)){
        return NULL;
    }
    /*otimizamos a subarvore esq e dps a direita*/
    otimizar_arvore(raiz->esq);
    otimizar_arvore(raiz->dir);
    
    raiz = otimizar(raiz);
    return raiz;
}

p_no_arv otimizar(p_no_arv raiz){

    /*caso 0: constantes iguais*/
    if(!eh_operador(raiz->esq->dado) && !eh_operador(raiz->dir->dado)){
        if (raiz->esq->dado == raiz->dir->dado){
            if (raiz->dado == '='){
                eh_true(raiz);
                return(raiz);
            }else if(raiz->dado == '!'){
                eh_false(raiz);
                return(raiz);
            }
        }
    }
    /*caso 1: qualquer variavel comparada a 0 ou 9*/
    //variavel na esquerda e 9 na direita
    if (eh_variavel(raiz->esq->dado) && raiz->dir->dado == '9'){
            if(raiz->dado == '{'){
                eh_true(raiz);
                return raiz;
            }else if(raiz->dado == '>'){
                eh_false(raiz);
                return raiz;
            }
    //variavel na direita e 9 na esquerda
    }else if (raiz->esq->dado == '9' && eh_variavel(raiz->dir->dado)){
            if(raiz->dado == '}'){
                eh_true(raiz);
                return raiz;
            }else if(raiz->dado =='<'){
                eh_false(raiz);
                return raiz;
            }
    //variavel na esquerda e 0 na direita
    }else if (eh_variavel(raiz->esq->dado) && raiz->dir->dado == '0'){
            if(raiz->dado == '}'){
                eh_true(raiz);
                return raiz;
            }else if(raiz->dado == '<'){
                eh_false(raiz);
                return raiz;
            }
    //variavel na direita e 0 na esquerda
    }else if (raiz->esq->dado == '0' && eh_variavel(raiz->dir->dado)){
            if(raiz->dado == '{'){
                eh_true(raiz);
                return raiz;
            }else if(raiz->dado =='>'){
                eh_false(raiz);
                return raiz;
            }
    /*caso 2: se os dois sao numeros*/
    }else if(eh_numero(raiz->esq->dado) && eh_numero(raiz->dir->dado)){

        if (raiz->dado == '='){
            if (raiz->esq->dado == raiz->dir->dado){
                eh_true(raiz);
            }else{
                eh_false(raiz);
            }
            return raiz;
        }else if(raiz->dado == '>'){
            if (raiz->esq->dado > raiz->dir->dado){
                eh_true(raiz);
            }else{
                eh_false(raiz);
            }
            return raiz;
        }else if(raiz->dado == '<'){
            if (raiz->esq->dado < raiz->dir->dado){
                eh_true(raiz);
            }else{
                eh_false(raiz);
            }
            return raiz;
        }else if(raiz->dado == '}'){
            if (raiz->esq->dado >= raiz->dir->dado){
                eh_true(raiz);
            }else{
                eh_false(raiz);
            }
            return raiz;
        }else if(raiz->dado == '{'){
            if (raiz->esq->dado <= raiz->dir->dado){
                eh_true(raiz);
            }else{
                eh_false(raiz);
            }
        }else if(raiz->dado == '!'){
            if (raiz->esq->dado != raiz->dir->dado){
                eh_true(raiz);
            }else{
                eh_false(raiz);
            }
        }
    /*caso 3: os dois sao variaveis iguais*/
    }else if(eh_variavel(raiz->esq->dado) && eh_variavel(raiz->dir->dado)){
        if(raiz->esq->dado == raiz->dir->dado){
            if (raiz->dado == '='){
                if (raiz->esq->dado == raiz->dir->dado){
                    eh_true(raiz);
                }else{
                    eh_false(raiz);
                }
                return raiz;
            }else if(raiz->dado == '!'){
                if (raiz->esq->dado != raiz->dir->dado){
                    eh_true(raiz);
                }else{
                    eh_false(raiz);
                }
                return raiz;
            }else if(raiz->dado == '>' || raiz->dado == '<'){
                eh_false(raiz);
                return raiz;
            }else if(raiz->dado == '}' || raiz->dado == '{'){
                eh_true(raiz);
                return raiz;
            }
        }
    /*caso 4: T | (qlqr coisa) ou (qlqr coisa) | T --> TRUE*/
    }else if (raiz->dado == '|'){
        if(raiz->esq->dado == 'T' || raiz->dir->dado == 'T'){
            eh_true(raiz);
            return raiz;
        }
    /*caso 5: F & (qlqr coisa) ou (qlqr coisa) & F --> FALSE*/
    }else if (raiz->dado == '&'){
        if(raiz->esq->dado == 'F' || raiz->dir->dado == 'F'){
            eh_false(raiz);
            return raiz;
        }
    }
    return raiz;
}

void eh_true(p_no_arv raiz){
    raiz->dado = 'T';
    destruir_arvore(raiz->esq);
    destruir_arvore(raiz->dir);
    raiz->esq = raiz->dir = NULL;
}

void eh_false(p_no_arv raiz){
    raiz->dado = 'F';
    destruir_arvore(raiz->esq);
    destruir_arvore(raiz->dir);
    raiz->esq = raiz->dir = NULL;
}

void destruir_arvore(p_no_arv raiz){
    if(raiz == NULL){
        return;
    }
    destruir_arvore(raiz->esq);
    destruir_arvore(raiz->dir);
    free(raiz);
}

