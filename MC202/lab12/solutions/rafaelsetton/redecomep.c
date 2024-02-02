#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "path.h"

void read_inputs(int dest[])
{
    // Lê todas as entradas e armazena em um vetor de int's.
    // Separa a parte de leitura do processamento, para naõ ter que lidar com EOF na main

    char *str = malloc(sizeof(char) * 1e6);

    int i = 0, leu;
    while (fgets(str, 1e6, stdin) != NULL)
    {
        int leu = sscanf(str, "%d ", &dest[i]);
        int start = 0;
        do
        {
            start += 2 + (dest[i] > 9);
            i++;
            leu = sscanf(str + start, "%d ", &dest[i]);
        } while (leu > 0);
    }
    dest[i] = -1;
    free(str);
}

int main()
{

    int idx = 0, aux1, aux2;
    int v[1000];
    read_inputs(v);
    p_grafo g = novo_grafo();
    p_path p = novo_caminho();

    while (1)
    {
        switch (v[idx++]) // v[idx++] pega o próximo input e incrementa o contador;
        {
        case 1:
            aux1 = v[idx++];
            add_node(g, aux1);
            break;

        case 2:
            aux1 = v[idx++];
            aux2 = v[idx++];
            connect_nodes(g, aux1, aux2);
            break;

        case 3:
            aux1 = v[idx++];
            aux2 = v[idx++];
            disconnect_nodes(g, aux1, aux2);
            break;

        case 4:
            reseta(p); // Tem que resetar o caminho para usar de novo;

            aux1 = v[idx++];
            aux2 = v[idx++];
            if (dfs(g, aux1, aux2, p))
                printf("Existe conexão entre os nós.\n");
            else
                printf("Não existe conexão entre os nós.\n");
            break;

        case 5:
            reseta(p);

            aux1 = v[idx++];
            aux2 = v[idx++];
            int *pai = bfs(g, aux1);
            if (pai[aux2] == -1)
            {
                printf("Não existe conexão entre os nós.\n");
                break;
            }
            while (aux2 != aux1)
            {
                adiciona(p, aux2);
                aux2 = pai[aux2];
            }

            printf("%d -> ", aux1);
            while (p->n > 1)
                printf("%d -> ", pop(p));
            printf("%d\n", pop(p));
            free(pai);
            break;

        case 6:
            for (int i = 1; i <= g->n_nodes; i++)
            {
                int *con = find_connections(g, i);
                printf("Ponto %d (Pontos diretamente ou indiretamente conectados): ", i);
                for (int j = 0; j < 20; j++)
                    if (con[j] == -1)
                        break;
                    else
                        printf("%d ", con[j]);
                printf("\n");
                free(con);
            }
            break;

        default:
            free(g);
            free(p);
            return 0;
        }
    }
    free(g);
    free(p);
    return 0;
}