#pragma once

typedef struct node *p_no;

struct node
{
    char valor;
    p_no esquerdo;
    p_no direito;
};

p_no novo_no(char valor);

void otimiza(p_no raiz);

void destroi(p_no raiz);

p_no gera_arvore(char exp[]);

void imprime(p_no raiz, int break_line);
