#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1783

typedef struct familia{
    char nome[11];
    int doces, removida;
}Familia;

typedef struct crianca{
    char nome[11], sobrenome[11];
    int casas;
}Crianca;

typedef Familia *p_fam;

typedef struct hash{
    p_fam *familias;
}Hash;

typedef Hash *p_hash;
/*cria o hash*/
p_hash criar_hash();
/*inicializa a familia*/
p_fam criar_familia();
/*inicializa a crianca*/
Crianca criar_crianca();
/*realiza toda a operacao de trick or treat*/
void trick_or_treat(p_hash hash);
/*atualiza a quantidade de doces de uma familia*/
void comprar(p_hash hash);
/*exclui uma familia do sistema*/
void sair(p_hash hash);
/*adiciona a familia no sistema*/
void entrar(p_hash hash, p_fam familia);
/*calcula a funcao de hash*/
int hash(char *nome);
/*busca no hash, devolve o ponteiro para a familia buscada,
retorna NULL se nao encontrou*/
p_fam buscar(p_hash fams, char nome[]);
/*insere no hash*/
void inserir(p_hash fams, p_fam fam);
/*remove do hash*/
void remover(p_hash fams, char nome[]);
/*converte a nota para um valor numerico*/
int converter_nota(char nota[]);
/*destroi o hash*/
void destruir_hash(p_hash hash);
