#pragma once
#include "path.h"
#include "fila.h"

struct grafo
{
    int nodes[20];
    int n_nodes;
    int adj[21][21];
};

typedef struct grafo *p_grafo;

p_grafo novo_grafo();

void add_node(p_grafo g, int n);

void connect_nodes(p_grafo g, int n1, int n2);

void disconnect_nodes(p_grafo g, int n1, int n2);

int dfs(p_grafo g, int from, int to, p_path passou);

int *bfs(p_grafo g, int from);

int *find_connections(p_grafo g, int n);