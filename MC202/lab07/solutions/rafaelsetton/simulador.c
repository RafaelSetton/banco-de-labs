#include <stdio.h>
#include "pilha.h"
#include "esteira.h"
#include "classificador.h"
#include "embalador.h"
#include "operador.h"
#include "peca.h"

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    int x;
    scanf("%d", &x);

    p_esteira esteira = nova_esteira(a, x);
    p_pilha pilha = nova_pilha(b);
    p_operador embalador = novo_operador(), classificador = novo_operador();

    int in, next, out; // Peças que entram para classificação, vão para embalagem e saem da embalagem, respectivamente
    int fim = 0;
    int atraso = 0;
    printf("##### Simulação\n");
    for (int minuto = 1; !fim; minuto++)
    {
        out = update_embalador(embalador, pilha);
        next = update_classificador(classificador, pilha, esteira);
        in = recebe_nova_peca(esteira);

        if (in == 0 && esteira->pecas_restantes > 0)
            atraso++;

        fim = pilha_vazia(pilha) && esteira_vazia(esteira) && classificador->p == NULL && embalador->p == NULL;
        printf("Min. %d: Classificação (+%d,-%d) | Embalagem (+%d,-%d).\n", minuto, in, next, next, out);
    }
    printf("Tempo atraso: %d.\n", atraso);

    destroi_esteira(esteira);
    destroi_pilha(pilha);
    destroi_operador(classificador);
    destroi_operador(embalador);
}