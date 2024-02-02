#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "no.h"
#include "stack.h"

int eh_operador(char c)
{
    // Verifica se um nó é um operador
    char ops[9] = "><{}&|=!";
    for (int i = 0; i < 9; i++)
        if (c == ops[i])
            return 1;
    return 0;
}

int eh_constante(char c)
{
    // Verifica se um nó é uma constante
    char consts[13] = "TF0123456789";
    for (int i = 0; i < 13; i++)
        if (c == consts[i])
            return 1;
    return 0;
}

int any(int vetor[], int n)
{
    // Retorna 1 se qualquer elemento do vetor for verdadeiro e 0 caso contrário
    for (int i = 0; i < n; i++)
        if (vetor[i])
            return 1;
    return 0;
}

p_no novo_no(char valor)
{
    // Cria um novo nó
    p_no no = malloc(sizeof(*no));
    no->valor = valor;
    no->direito = NULL;
    no->esquerdo = NULL;
    return no;
}

void otimiza(p_no raiz)
{
    if (raiz->esquerdo == NULL)
        return; // É uma folha, não tem como otimizar

    otimiza(raiz->direito);
    otimiza(raiz->esquerdo);

    char val = raiz->valor, esq = raiz->esquerdo->valor, dir = raiz->direito->valor;

    if (eh_operador(esq) && eh_operador(dir))
        return;

    int trues[7] = { // Operações que resultam em 'T'
        (val == '|' && (esq == 'T' || dir == 'T')),
        (val == '{' && dir == '9'),
        (val == '}' && esq == '9'),
        (val == '}' && dir == '0'),
        (val == '{' && esq == '0'),
        (val == '=' && dir == esq),
        ((val == '{' || val == '}') && dir == esq)};

    int falses[7] = { // Operações que resultam em 'F'
        (val == '&' && (esq == 'F' || dir == 'F')),
        (val == '>' && dir == '9'),
        (val == '<' && esq == '9'),
        (val == '<' && dir == '0'),
        (val == '>' && esq == '0'),
        (val == '!' && dir == esq),
        ((val == '>' || val == '<') && dir == esq)};

    if (any(trues, 7))
        raiz->valor = 'T';
    else if (any(falses, 7))
        raiz->valor = 'F';
    else if (eh_constante(dir) && eh_constante(esq))
    {
        // Compara duas constantes
        if (val == '=')
            raiz->valor = dir == esq ? 'T' : 'F';
        else if (val == '!')
            raiz->valor = dir != esq ? 'T' : 'F';
        else if (val == '>')
            raiz->valor = esq > dir ? 'T' : 'F';
        else if (val == '<')
            raiz->valor = esq < dir ? 'T' : 'F';
        else if (val == '}')
            raiz->valor = esq >= dir ? 'T' : 'F';
        else if (val == '{')
            raiz->valor = esq <= dir ? 'T' : 'F';
    }

    if (raiz->valor == 'T' || raiz->valor == 'F')
    {
        // Alguma otimização foi feita
        destroi(raiz->direito);
        destroi(raiz->esquerdo);
        raiz->direito = NULL;
        raiz->esquerdo = NULL;
    }
}

void destroi(p_no raiz)
{
    // Destroi os filhos e, em seguida a raiz
    if (raiz == NULL)
        return;
    destroi(raiz->direito);
    destroi(raiz->esquerdo);
    free(raiz);
}

p_no gera_arvore(char exp[])
{
    // Gera uma árvore a partir da entrada e retorna a raiz
    p_stack pilha = nova_pilha();
    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (eh_operador(exp[i]))
        {
            p_no no = novo_no(exp[i]);
            no->direito = pop(pilha);
            no->esquerdo = pop(pilha);
            push(pilha, no);
        }
        else
            push(pilha, novo_no(exp[i]));
    }
    p_no res = pop(pilha);
    free(pilha);
    return res;
}

void imprime(p_no raiz, int break_line)
{
    // Imprime a árvore. Quebra uma linha no final se break_line!=0
    if (raiz->esquerdo == NULL)
    {
        printf("%c", raiz->valor);
        return;
    }

    printf("(");
    imprime(raiz->esquerdo, 0);
    printf(" %c ", raiz->valor);
    imprime(raiz->direito, 0);
    printf(")");
    if (break_line)
        printf("\n");
}
