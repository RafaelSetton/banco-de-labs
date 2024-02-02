#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

p_lista criar_lista(){
    p_lista lista = malloc(sizeof(struct lista_ligada));
    lista->inicio = NULL;
    lista->fim = NULL;
    return lista;
}

void destruir(p_no lista){
    if (lista->prox != NULL)
        destruir(lista->prox);
    free(lista);
}

void separar_entrada(char entrada[], char comando[], char livro[]){
    int tam = 0, pos = 0, i = 0;
    //sobrescreve o \n com \0
    entrada[strlen(entrada) - 1] = '\0';
    //tamanho do comando inicial
    for (tam = 0; entrada[tam] != ' ' && entrada[tam] != '\0'; tam++);
    //separo o comando
    strncpy(comando, entrada, tam);
    comando[tam] = '\0';
    //separo o livro
    for (pos = tam + 1; entrada[pos] != '\0'; pos++){
        livro[i] = entrada[pos];
        i++;
    }
    livro[i] = '\0';
}

p_no adicionar(p_lista lista, char livro[], int *inicio, int *final, p_no ultimo){
    p_no novo = malloc(sizeof(struct no));
    strcpy(novo->livro, livro);
    //lista vazia
    if (ultimo == NULL){
        lista->fim = novo;
        novo->prox = NULL;
        novo->ant = NULL;
        lista->inicio = novo;
        return novo;
    }
    //se ela quer adicionar no inicio
    else if(*inicio == 1 && *final == 0){
        lista->inicio->ant = novo;
        novo->prox = lista->inicio;
        novo->ant = NULL;
        lista->inicio = novo;
        //ja adicionou, seta inicio pra 0 dnv
        *inicio = 0;
        return novo;
    }
    //se ela quer adicionar no fim
    else if (*final == 1 && *inicio == 0){
        lista->fim->prox = novo;
        novo->ant = lista->fim;
        novo->prox = NULL;
        lista->fim = novo;
        //ja adicionou, seta final pra 0 dnv
        *final = 0;
        return novo;
    }
    //insere na frente do ultimo adicionado
    //quando final e inicio sao 0
    novo->ant = ultimo;
    novo->prox = ultimo->prox;
    if (ultimo->prox != NULL){
        ultimo->prox->ant = novo;
    }else{
        //se o prox nó é null, entao o fim passa a ser o que estamos inserindo
        lista->fim = novo;
    }
    ultimo->prox = novo;
    return novo;   
}

p_no busca(p_lista lista, char livro[]){
    p_no atual = lista->inicio;
    while(atual != NULL){
        if(strcmp(atual->livro, livro) == 0){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void remover(p_lista lista, char livro[], p_no ultimo, int *inicio, int *final){
    p_no alvo = busca(lista, livro);
    //se o no que queremos remover é o inicial
    if (alvo == lista->inicio){
        //se estamos removendo o ultimo nó adicionado
        if (ultimo == alvo){
            *inicio = 1;
        }
        //se a lista fica vazia quando removemos
        if (alvo->prox == NULL){
            lista->inicio = lista->fim = NULL;
        }else{
            lista->inicio = alvo->prox;
            lista->inicio->ant = NULL;
        }
    //se o nó for o último
    }else if(alvo == lista->fim){
        //se estamos removendo o ultimo nó adicionado
        if (ultimo == alvo){
            *final = 1;
        }
        //se a lista fica vazia quando removemos
        if (alvo->ant == NULL){
            lista->inicio = lista->fim = NULL;
        }else{
            lista->fim = alvo->ant;
            lista->fim->prox = NULL;
        }
    //se o nó ta no meio
    }else{
        if (ultimo == alvo){
            ultimo = ultimo->ant;
        }
        alvo->ant->prox = alvo->prox;
        alvo->prox->ant = alvo->ant;
    }
    free(alvo);
}

void imprimir(p_lista lista){
    p_no atual;
    for (atual = lista->inicio; atual != NULL; atual = atual->prox){
        if (atual->prox != NULL){
            printf("%s, ", atual->livro);
        }
        else{
            printf("%s", atual->livro);
        }
    }
}