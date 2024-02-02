#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 200

enum cor {VERMELHO, PRETO};
typedef struct no *p_no;
/*simbolo: contem tipo e nome da variavel*/
typedef struct simbolo{
    char tipo[10];
    char nome[MAX];
}simbolo;

/*no da arvore rubro negra, ordenada por ordem alfabetica*/
struct no{
    simbolo simbol;
    enum cor cor;
    p_no esq, dir;
};

/*cria a arvore*/
p_no criar_arvore();
/*retorna se o no eh vermelho*/
int eh_vermelho(p_no x);
/*retorna se o no eh preto*/
int eh_preto(p_no x);
/*retorna se a palavra eh um tipo*/
int eh_tipo(char palavra[]);
/*retorna se a linha possui uma expressao/operacao*/
int eh_operacao(char linha[]);
/*cria o simbolo: contem o tipo e o nome da variavel*/
simbolo criar_simbol(char tipo[], char nome[]);
/*retorna o no buscado e se não está na arvore, retorna NULL*/
p_no buscar(p_no raiz , char nome[]);
/*rotaciona a arvore para a esquerda*/
p_no rotaciona_esq(p_no raiz);
/*rotaciona a arvore para a direita*/
p_no rotaciona_dir(p_no raiz);
/*sobe a cor vermelha na arvore*/
void sobe_vermelho(p_no raiz);
/*insere um no na arvore recursivamente*/
p_no inserir_rec(p_no raiz, simbolo simbol);
/*chama a insercao recursiva e ajeita a cor da raiz para preto*/
p_no inserir(p_no raiz, simbolo simbol);
/*checa se as variaveis estao declaradas, indicando erro se alguma não está.
retorna 1 se teve erro, 0 se nao teve erro*/
int erro_declaracao(int cont, p_no raiz, p_no simb1, p_no simb2, p_no simb3);
/*checa se os operandos possuem tipos diferentes, retornando 1. caso contrario, n teve erro,
retornando 0*/
int operandos_diff(int cont, char operador, p_no raiz, p_no simb2, p_no simb3);
/*checa se o resultado da operacao tem tipo compativel com os dos operandos.
retorna 1 se nao sao compativeis, caso contrario, retorna 0*/
int resultado_diff(int cont, p_no raiz, p_no simb1, p_no simb2, p_no simb3);
/*printa a arvore em ordem alfabetica*/
void inordem(p_no raiz);
/*chama a impressao da arvore em inordem*/
void imprimir_arvore(p_no raiz);
/*destroi a arvore, liberando sua memoria*/
void destruir_arvore(p_no raiz);