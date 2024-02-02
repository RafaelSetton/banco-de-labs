#include "arvore.h"

p_no criar_arvore(){
    p_no raiz = NULL;
    return raiz;
}

int eh_vermelho(p_no x){
    if (x == NULL){
        return 0;
    }
    return x->cor == VERMELHO;
}

int eh_preto(p_no x){
    if (x == NULL){
        return 1;
    }
    return x->cor == PRETO;
}

int eh_tipo(char palavra[]){
    if ((strcmp(palavra, "int") == 0) ||
    (strcmp(palavra, "char") == 0) ||
    (strcmp(palavra, "double") == 0)){
        return 1;
    }
    return 0;
} 

int eh_operacao(char linha[]){
    char *igual, *adicao, *sub, *resto, *div, *mult;
    igual = strchr(linha, '=');
    adicao = strchr(linha, '+');
    sub = strchr(linha, '-');
    resto = strchr(linha, '%');
    div = strchr(linha, '/');
    mult = strchr(linha, '*');

    //se tem igual, tem potencial de ser operacao
    if (igual != NULL){
        //se tbm tem algum operador, eh operacao
        if(adicao != NULL || sub != NULL || resto != NULL
        || div != NULL || mult != NULL){
            return 1;
        }
    }
    return 0;
}

p_no buscar(p_no raiz, char nome[]){
    int comparacao;
    while (raiz != NULL && nome != raiz->simbol.nome){
        comparacao = strcmp(nome, raiz->simbol.nome);
        if (comparacao == 0){
            return raiz;
        }
        else if (comparacao < 0){
            raiz = raiz->esq;
        }else{
            raiz = raiz->dir;
        }
    }
    return raiz;
}

p_no rotaciona_esq(p_no raiz){
    p_no x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

p_no rotaciona_dir(p_no raiz){
    p_no x = raiz ->esq;
    raiz ->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz ->cor;
    raiz ->cor = VERMELHO;
    return x;
}

void sobe_vermelho(p_no raiz){
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

simbolo criar_simbol(char tipo[], char nome[]){
    simbolo novo;
    novo.nome[0] = '\0';
    novo.tipo[0] = '\0';
    strcpy(novo.tipo, tipo);
    strcpy(novo.nome, nome);
    return novo;
}

int erro_declaracao(int cont, p_no raiz, p_no simb1, p_no simb2, p_no simb3){
    //se alguma variavel n ta na arvore, n foi declarada
    if (simb1 == NULL || simb2 == NULL || simb3 == NULL){
        return 1;
    }
    return 0;
}

int operandos_diff(int cont, char operador, p_no raiz, p_no simb2, p_no simb3){
    //se os tipos dos operandos sao incompativeis, tem erro
    if(strcmp(simb2->simbol.tipo, simb3->simbol.tipo) != 0){
        printf("Linha %d: tipos incompatíveis: %s (%s) %c %s (%s).\n",
        cont, simb2->simbol.nome, simb2->simbol.tipo, operador, simb3->simbol.nome,
        simb3->simbol.tipo);
        return 1;
    }
    return 0;
}

int resultado_diff(int cont, p_no raiz, p_no simb1, p_no simb2, p_no simb3){
    char tipo_resultado[10];
    tipo_resultado[0] = '\0';
    strcpy(tipo_resultado, simb2->simbol.tipo);
    if(strcmp(tipo_resultado, simb1->simbol.tipo) != 0){
        printf("Linha %d: tipos incompatíveis: o símbolo %s espera %s, obteve %s.\n",
        cont, simb1->simbol.nome, simb1->simbol.tipo, tipo_resultado);
        return 1;
    }
    return 0;
}

p_no inserir_rec(p_no raiz, simbolo simbol){
    p_no novo;
    if (raiz == NULL) {
        novo = malloc(sizeof(struct no));
        novo->esq = novo->dir = NULL;
        novo->simbol = simbol;
        novo->cor = VERMELHO;
        return novo;
    }
    int comparacao = strcmp(simbol.nome, raiz->simbol.nome);

    if (comparacao < 0){
        raiz->esq = inserir_rec(raiz->esq, simbol);
    }
    else{
        raiz->dir = inserir_rec(raiz->dir , simbol);
    }
    /* corrige a árvore */
    if (eh_vermelho(raiz->dir) && eh_preto(raiz->esq)){
        raiz = rotaciona_esq(raiz);
    }
    if (eh_vermelho(raiz->esq) && eh_vermelho(raiz->esq->esq)){
        raiz = rotaciona_dir(raiz);
    }
    if (eh_vermelho(raiz->esq) && eh_vermelho(raiz->dir)){
        sobe_vermelho(raiz);
    }
    return raiz;
}

p_no inserir(p_no raiz, simbolo simbol){
    raiz = inserir_rec(raiz, simbol);
    raiz->cor = PRETO;
    return raiz;
}

void inordem(p_no raiz){
    if (raiz != NULL){
        inordem(raiz->esq);
        printf("%s %s\n",raiz->simbol.nome, raiz->simbol.tipo);
        inordem(raiz->dir);
    }
}

void imprimir_arvore(p_no raiz){
    inordem(raiz);
}

void destruir_arvore(p_no raiz){
    if(raiz == NULL){
        return;
    }
    destruir_arvore(raiz->esq);
    destruir_arvore(raiz->dir);
    free(raiz);
}