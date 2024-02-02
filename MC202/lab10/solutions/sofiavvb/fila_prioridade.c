#include "fila_prioridade.h"

p_fp criar_filaprio(int alocado){
    p_fp fprio = malloc(sizeof(FP));
    fprio->heap = malloc(alocado * sizeof(Pedido));
    fprio->clientes = malloc(alocado * sizeof(Cliente));
    fprio->n = 0;
    fprio->alocado = alocado;
    return fprio;
}

Cliente criar_cliente(){
    Cliente cliente;
    scanf("%s %s %d", cliente.nome, cliente.sobrenome, &cliente.quantidade);
    return cliente;
}

int eh_pedido(char comando[16]){
    if (strcmp(comando, "novo") == 0){
        return 1;
    }
    return 0;
}

void troca_pedidos(Pedido *a, Pedido *b){
    /*troca as posicoes dos pedidos no heap*/
    Pedido t = *a;
    *a = *b;
    *b = t;
}

void sobe_no_heap(p_fp fprio , int k) {
    if (k > 0 && fprio->heap[PAI(k)].prioridade < fprio->heap[k].prioridade) {
        troca_pedidos(&fprio->heap[k], &fprio->heap[PAI(k)]);
        sobe_no_heap(fprio, PAI(k));
    }
}

void desce_no_heap(p_fp fprio , int k){
    int maior_filho;
    if (F_ESQ(k) < fprio->n) {
        maior_filho = F_ESQ(k);
        if (F_DIR(k) < fprio->n &&
            fprio->heap[F_ESQ(k)].prioridade < fprio->heap[F_DIR(k)].prioridade){
                maior_filho = F_DIR(k);
            }
        if (fprio->heap[k].prioridade < fprio->heap[maior_filho].prioridade) {
            troca_pedidos(&fprio->heap[k], &fprio->heap[maior_filho]);
            desce_no_heap(fprio , maior_filho);
        }
    }
}

void insere(p_fp fprio , Pedido pedido){
    fprio->heap[fprio->n] = pedido;
    fprio->n++;
    sobe_no_heap(fprio, fprio->n - 1);
}

Pedido extrai_maximo(p_fp fprio) {
    Pedido pedido = fprio->heap[0];
    troca_pedidos(&fprio->heap[0], &fprio->heap[fprio->n - 1]);
    fprio->n--;
    desce_no_heap(fprio, 0);
    return pedido;
}

Pedido criar_pedido(Cliente *clientes, int id){
    Pedido pedido;
    pedido.cliente = clientes[id];
    pedido.id = id;
    pedido.nome_prato[0] = '\0';
    pedido.prioridade = clientes[id].quantidade;
    fgets(pedido.nome_prato, 26, stdin);
    pedido.nome_prato[strlen(pedido.nome_prato) - 1] = '\0';
    return pedido;
}

void imprimir_rodada(int rodada, int panelas, p_fp fprio){
    printf("---- rodada %d ----\n", rodada);
    for (int i = 0; i < panelas; i++){
        /*se ainda tem pedidos para serem processados*/
        if(fprio->n > 0){
            Pedido pedido = extrai_maximo(fprio);
            printf("%s %s %s %d\n", pedido.cliente.nome, pedido.cliente.sobrenome,
            pedido.nome_prato, pedido.prioridade);
        }else{
            break;
        }
    }
}

void muda_prioridade(p_fp fprio , int k, int valor){
    if (valor > 0) {
        fprio->heap[k].prioridade += valor;
        sobe_no_heap(fprio , k);
    }else{
        fprio->heap[k].prioridade += valor;
        desce_no_heap(fprio , k);
    }
}

void alteracao(p_fp fprio, int valor, int id){
    /*percorre o heap para achar o pedido com o mesmo id*/
    for (int i = 0; i < fprio->n; i++){
        /*se os ids sao iguais*/
        if(fprio->heap[i].id == id){
            /*muda a prioridade desse pedido*/
            muda_prioridade(fprio, i, valor);
            break;
        }
    }
}

void destruir_heap(p_fp fprio){
    free(fprio->clientes);
    free(fprio->heap);
    free(fprio);
}