#include "grafo.h"

p_grafo criar_grafo(int n){
    p_grafo g = malloc(sizeof(Grafo));
    g->n = n;
    g->adj = malloc(n * sizeof(int *));
    /*inicializa a matriz de adj com 0*/
    for (int i = 1; i < n; i++){
        g->adj[i] = calloc(n, sizeof(int));
    }
    return g;
}

void destruir_grafo(p_grafo g){
    for(int i = 1; i < g->n; i++){
        free(g->adj[i]);
    }
    free(g->adj);
    free(g);
}

void adicionar(int codigo, int *pontos){
    int ponto = 0;
    scanf("%d ", &ponto);
    pontos[ponto] = 1;
}

void inserir_aresta(p_grafo g, int u, int v){
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

void remover_aresta(p_grafo g, int u, int v){
    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
}

void conectar(p_grafo g){
    int u = 0, v = 0;
    scanf("%d %d ", &u, &v);
    inserir_aresta(g, u, v);
}

void desconectar(p_grafo g){
    int u = 0, v = 0;
    scanf("%d %d ", &u, &v);
    remover_aresta(g, u, v);
}

void tem_conexao(p_grafo g){
    int u = 0, v = 0, achou = 0;
    scanf("%d %d ", &u, &v);
    achou = existe_caminho(g, u, v);
    if (achou){
        printf("Existe conexão entre os nós.\n");
    }else{
        printf("Não existe conexão entre os nós.\n");
    }
}

int existe_caminho(p_grafo g, int s, int t){
    int encontrou, *visitado = calloc(g->n, sizeof(int));
    encontrou = busca_rec(g, visitado , s, t);
    free(visitado);
    return encontrou;
}

int busca_rec(p_grafo g, int *visitado , int v, int t){
    if (v == t)
        return 1; /* sempre existe caminho de t para t*/
    visitado[v] = 1;
    /*começa do 1, pois nao existe ponto 0*/
    for (int w = 1; w < g->n; w++)
        if (g->adj[v][w] && !visitado[w])
            if (busca_rec(g, visitado , w, t))
                return 1;
    return 0;
}

int * busca_em_largura(p_grafo g, int s){
    int w, v;
    int *pai = malloc(g->n * sizeof(int));
    int *visitado = malloc(g->n * sizeof(int));
    p_fila f = criar_fila (g->n);
    for (v = 1; v < g->n; v++) {
        pai[v] = -1;
        visitado[v] = 0;
    }
    enfileira(f,s);
    pai[s] = s;
    visitado[s] = 1;
    while (! fila_vazia(f)) {
        v = desenfileira(f);
        for (w = 1; w < g->n; w++){
            if (g->adj[v][w] && !visitado[w]) {
                visitado[w] = 1;/* evita repetição na fila*/
                pai[w] = v;
                enfileira(f, w);
            }
        }
    }
    destruir_fila(f);
    free(visitado);
    return pai;
}

void caminho_minimo(p_grafo g){
    int u = 0, v = 0;
    scanf("%d %d ", &u, &v);
    /*primeiro, checar se tem caminho minimo*/
    if (existe_caminho(g, u, v)){
        /*arvore de caminhos minimos com a raiz sendo o ponto u*/
        int *pai = busca_em_largura(g, u);
        /*imprime o caminho minimo de u ate v*/
        imprimir_caminho(v, v, pai);
        printf("\n");
        free(pai);
    }else{
        printf("Não existe conexão entre os nós.\n");
    }
}

void imprimir_caminho(int final, int v, int *pai){
    if(pai[v] != v){
        imprimir_caminho(final, pai[v], pai);
    }
    if(v != final){
        printf("%d -> ", v);
    }else{
        printf("%d", final);
    }
}

void encontra_conexoes(p_grafo g, int *pontos){
    for(int i = 1; i < g->n; i++){
        /*para cada ponto da rede, vamos obter os pontos que tem conexao com ele*/
        if(pontos[i] == 1){
            int *pai = encontra_caminhos(g, i);
            printf("Ponto %i (Pontos diretamente ou indiretamente conectados): ", i);
            for (int j = 1; j < g->n; j++){
                if (pai[j] != -1){
                    printf("%d ", j);
                }
            }
            printf("\n");
            free(pai);
        }
    }
}

int * encontra_caminhos(p_grafo g, int s){
    int *pai = malloc(g->n * sizeof(int));
    for(int i = 1; i < g->n; i++){
        pai[i] = -1;
    }
    busca_em_profundidade(g, pai, s, s);
    return pai;
}

void busca_em_profundidade(p_grafo g, int *pai , int p, int v){
    pai[v] = p;
    for (int w = 1; w < g->n; w++){
        if (g->adj[v][w] && pai[w] == -1){
            busca_em_profundidade(g, pai , v, w);
        }
    }
}