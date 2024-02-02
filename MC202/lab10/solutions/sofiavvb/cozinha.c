#include <stdio.h>
#include "fila_prioridade.h"

int main(){

    int panelas = 0, sobreviventes = 0, operacoes = -1, rodada = 0, id = 0, valor = 0;
    char comando[16];
    scanf("%d %d", &panelas, &sobreviventes);
    /*fila de prioridade com os pedidos acumulados*/
    p_fp fprio = criar_filaprio(sobreviventes);
    /*vetor de clientes(sobreviventes)*/
    for (int i = 0; i < sobreviventes; i++){
        Cliente cliente = criar_cliente(i);
        fprio->clientes[i] = cliente;
    }

    while (scanf("%d", &operacoes) && operacoes != 0){
        rodada++;
        for (int i = 0; i < operacoes; i++){
            scanf("%s %d ", comando, &id);
            /*se for pedido, precisamos inserir no heap*/
            if(eh_pedido(comando)){
                Pedido pedido = criar_pedido(fprio->clientes, id);
                /*insere o pedido no heap e atualiza o seu 
                campo "posicao no heap"*/
                insere(fprio, pedido);
            }
            /*caso contrario, temos uma alteracao*/
            else{
                scanf(" %d", &valor);
                alteracao(fprio, valor, id);
            }
        }
        /*final da rodada*/
        imprimir_rodada(rodada, panelas, fprio);
    }
    /*checar se ainda tem pratos na fila de 
    prioridade para serem processados*/
    while(operacoes == 0  && fprio->n > 0){
        rodada++;
        imprimir_rodada(rodada, panelas, fprio);
    }
    destruir_heap(fprio);
    return 0;
}