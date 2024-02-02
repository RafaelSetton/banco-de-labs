#ifndef __ARVORE_H__
#define __ARVORE_H__

typedef struct no_arv *p_no_arv;

struct no_arv {
    char dado;
    p_no_arv esq, dir;
};
/*percorre a arvore em inordem imprimindo recursivamente*/
void inordem(p_no_arv raiz);
/*imprime a arvore em inordem*/
void imprimir_arvore(p_no_arv raiz);
/*cria a arvore com a expressao dada*/
p_no_arv criar_arvore(char expressao[]);
/*cria um no da arvore*/
p_no_arv criar_no_arv(char dado);
/*destroi recursivamente a arvore*/
void destruir_arvore(p_no_arv raiz);
/*checa se o dado eh uma variavel*/
int eh_variavel(char dado);
/*checa se o dado eh T ou F*/
int eh_const_logica(char dado);
/*checa se o dado eh um numero*/
int eh_numero(char dado);
/*checa se o dado eh um operador*/
int eh_operador(char dado);
/*otimiza a expressao pra true*/
void eh_true(p_no_arv raiz);
/*otimiza a expressao pra false*/
void eh_false(p_no_arv raiz);
/*otimiza a arvore como um todo, retornando a sua raiz*/
p_no_arv otimizar_arvore(p_no_arv raiz);
/*checar se consegue aplicar alguma otimização na expressao*/
p_no_arv otimizar(p_no_arv raiz);

#endif