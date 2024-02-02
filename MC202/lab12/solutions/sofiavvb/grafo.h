#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct grafo {
    int **adj;
    int n;
}Grafo;

typedef Grafo *p_grafo;
/*cria e inicializa o grafo*/
p_grafo criar_grafo(int n);
/*destroi o grafo, liberando a memoria*/
void destruir_grafo(p_grafo g);
/*insere aresta entre u e v na matriz de adjacencia*/
void inserir_aresta(p_grafo g, int u, int v);
/*remove aresta entre u e v na matriz de adjacencia*/
void remover_aresta(p_grafo g, int u, int v);
/*operação 1: guarda os pontos que ja foram adicionados na rede*/
void adicionar(int codigo, int *pontos);
/*operação 2: conecta dois pontos (u,v) da rede*/
void conectar(p_grafo g);
/*operação 3: desconecta dois pontos (u,v) da rede*/
void desconectar(p_grafo g);
/*operação 4: checar se há conexão direta ou indireta entre os pontos u e v da rede.*/
void tem_conexao(p_grafo g);
/*efetua busca em largura, retorna a arvore de caminhos minimos do ponto s*/
int * busca_em_largura(p_grafo g, int s);
/*operação 5: encontra a conexão mais curta entre os pontos u e v da rede*/
void caminho_minimo(p_grafo g);
/*busca em profundidade, retorna 1 se há conexão entre o pontos v e t. 
retorna 0 se não há conexão*/
int busca_rec(p_grafo g, int *visitado , int v, int t);
/*chama a busca_rec, verifica se há conexão entre v e t*/
int existe_caminho(p_grafo g, int s, int t);
/*imprime o caminho mínimo entre os pontos da mesma componente conexa*/
void imprimir_caminho(int final, int v, int *pai);
/*operação 6: para cada ponto u da rede, encontra todos os pontos v
para os quais existe conexão direta ou indireta para u.*/
void encontra_conexoes(p_grafo g, int *pontos);
/*implementa a operação 6, utilizando a busca em profundidade*/
int * encontra_caminhos(p_grafo g, int s);
/*busca em profundidade, obtem os pontos na mesma componente conexa*/
void busca_em_profundidade(p_grafo g, int *pai , int p, int v);

#endif // __GRAFO_H__