#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sobrevivente.h"
#include "fila.h"
#include "prato.h"

#define MAX (int)1e5

void executa(p_fp fila, p_sob pessoas[])
{
    // Lẽ e executa uma ação (novo ou altera)
    char acao[100];
    int id, valor;
    char nome_prato[30];
    scanf("%s %d", acao, &id);

    if (strcmp(acao, "novo") == 0)
    {
        fgets(nome_prato, 30, stdin);
        insere(fila, novo_prato(pessoas[id], nome_prato));
    }
    else
    {
        scanf("%d", &valor);
        int idx = acha_prato(fila, id);
        altera(fila->v[idx], valor);
        if (valor > 0)
            sobe_no_heap(fila, idx);
        else
            desce_no_heap(fila, idx);
    }
}

int main()
{
    int p, s;
    scanf("%d %d", &p, &s);

    p_sob pessoas[MAX];
    for (int i = 0; i < s; i++)
        pessoas[i] = novo_sobrevivente(i);

    p_fp fila = nova_fila();

    int n = 1, rodada = 0;

    while (++rodada && (n != 0 || fila->n > 0)) // Para quando n=0 e não houver mais pratos na fila
    {
        // Ações
        if (n != 0)
            scanf("%d", &n);

        for (int i = 0; i < n; i++)
            executa(fila, pessoas);

        if (fila->n == 0)
            continue;

        // Resultados
        printf("---- rodada %d ----\n", rodada);
        p_prato prato;
        for (int i = 0; i < p; i++)
        {
            if (fila->n == 0)
                break;
            prato = extrai_maximo(fila);
            printf("%s %s %s %d\n", prato->dono->nome, prato->dono->sobrenome, prato->nome, prato->prioridade);
            free(prato);
        }
    }

    // Libera a memória
    for (int i = 0; i < s; i++)
        free(pessoas[i]);
    destroi_fila(fila);
}