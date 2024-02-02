#include <stdlib.h>
#include "grafo.h"
#include "path.h"

p_grafo novo_grafo()
{
    p_grafo g = malloc(sizeof(struct grafo));
    g->n_nodes = 0;
    for (int i = 0; i < 21; i++)
        for (int j = 0; j < 21; j++)
            g->adj[i][j] = 0;
    return g;
}

void add_node(p_grafo g, int n)
{
    g->nodes[g->n_nodes] = n;
    g->n_nodes += 1;
}

void connect_nodes(p_grafo g, int n1, int n2)
{
    g->adj[n1][n2] = g->adj[n2][n1] = 1;
}

void disconnect_nodes(p_grafo g, int n1, int n2)
{
    g->adj[n1][n2] = g->adj[n2][n1] = 0;
}

int dfs(p_grafo g, int from, int to, p_path passou)
{
    if (from == to)
        return 1;

    adiciona(passou, from);

    for (int i = 0; i < 21; i++)
        if (g->adj[from][i] && (!contem(passou, i)) && dfs(g, i, to, passou))
            return 1;

    return 0;
}

int *bfs(p_grafo g, int from)
{
    int w, v;
    int *pai = malloc((1 + g->n_nodes) * sizeof(int));
    int *visitado = malloc((1 + g->n_nodes) * sizeof(int));
    p_fila f = criar_fila();
    for (v = 1; v <= g->n_nodes; v++)
    {
        pai[v] = -1;
        visitado[v] = 0;
    }
    enfileira(f, from);
    pai[from] = from;
    visitado[from] = 1;
    while (!fila_vazia(f))
    {
        v = desenfileira(f);
        for (w = 1; w <= g->n_nodes; w++)
            if (g->adj[v][w] && !visitado[w])
            {
                visitado[w] = 1; /*evita repetição na fila*/
                pai[w] = v;
                enfileira(f, w);
            }
    }
    free(f);
    free(visitado);
    return pai;
}

int *find_connections(p_grafo g, int n)
{
    // Encontra todos os vértices conectados a n;
    int *v = malloc(sizeof(int) * 20), x = 0;
    p_path p = novo_caminho();
    for (int i = 1; i < 21; i++)
    {
        reseta(p);
        if (dfs(g, n, i, p))
            v[x++] = i;
    }

    free(p);
    v[x] = -1;
    return v;
}