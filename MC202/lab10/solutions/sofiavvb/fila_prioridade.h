#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAI(i) ((i-1)/2) /*Pai de i*/
#define F_ESQ(i) (2*i+1) /* Filho esquerdo de i*/
#define F_DIR(i) (2*i+2) /* Filho direito de i*/

typedef struct{
    int quantidade;
    char nome[16], sobrenome[16];
}Cliente;

typedef struct{
    char nome_prato[26];
    int prioridade, id;
    Cliente cliente;
}Pedido;

typedef struct{
    Cliente *clientes;
    Pedido *heap;
    int n, alocado;
}FP;

typedef FP *p_fp;
/*cria a fila de prioridade para organizar os pedidos*/
p_fp criar_filaprio(int alocado);
/*insere o pedido na fila de prioridade*/
void insere(p_fp fprio , Pedido pedido);
/*extrai o elemento(pedido) com maior prioridade*/
Pedido extrai_maximo(p_fp fprio);
/*sobe o elemento no heap garantindo a propriedade dele*/
void sobe_no_heap(p_fp fprio , int indice);
/*desce o elemento no heap garantindo a propriedade dele*/
void desce_no_heap(p_fp fprio , int indice);
/*troca os pedidos de posicao no heap*/
void troca_pedidos(Pedido *a, Pedido *b);
/*inicializa o cliente*/
Cliente criar_cliente();
/*inicializa o pedido*/
Pedido criar_pedido(Cliente *clientes, int id);
/*retorna se é um novo pedido para adicionar na fila*/
int eh_pedido(char comando[16]);
/*imprime os pratos prontos em cada rodada*/
void imprimir_rodada(int rodada, int panelas, p_fp fprio);
/*muda a prioridade do pedido no heap e garante que ele continue com 
suas propriedades*/
void muda_prioridade(p_fp fprio , int k, int valor);
/*chamada quando temos uma alteracao de prioridade no pedido de id 'k'*/
void alteracao(p_fp fprio, int valor, int id);
/*libera a memoria utilizada*/
void destruir_heap(p_fp fprio);