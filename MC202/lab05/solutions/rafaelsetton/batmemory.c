#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dinamico.h"

void bat_alloc(dinamico *vetor)
{
    int n;
    int *valores;
    scanf("%d", &n);
    valores = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) // Lê os valores para adicionar na memória
        scanf("%d", &valores[i]);

    int pos = encontra(vetor, n);
    if (pos == -1)
    {
        aumenta(vetor);
        pos = encontra(vetor, n);
    }
    insere(vetor, pos, n, valores);
    free(valores);

    printf("%d\n", pos);
}

void bat_free(dinamico *vetor)
{
    int endereco;
    scanf("%d", &endereco);
    libera(vetor, endereco);

    otimiza(vetor);
}

void bat_print(dinamico *vetor)
{
    int endereco;
    scanf("%d", &endereco);

    printf("%d", vetor->v[endereco + 1]); // Esse fica separado para não ficar um espaço no final da linha
    for (int i = endereco + 2; i <= endereco + vetor->v[endereco]; i++)
        printf(" %d", vetor->v[i]);
    printf("\n");
}

void bat_uso(dinamico *vetor)
{
    printf("%d de %d\n", vetor->ocupado, vetor->alocado);
}

int main()
{
    int n;
    scanf("%d", &n);
    dinamico bat_vetor = novo_vetor_dinamico();
    for (int i = 0; i < n; i++)
    {
        char comando[15];
        scanf("%s", comando);

        if (strcmp(comando, "bat-alloc") == 0)
            bat_alloc(&bat_vetor);
        else if (strcmp(comando, "bat-free") == 0)
            bat_free(&bat_vetor);
        else if (strcmp(comando, "bat-print") == 0)
            bat_print(&bat_vetor);
        else if (strcmp(comando, "bat-uso") == 0)
            bat_uso(&bat_vetor);
    }
    free(bat_vetor.inicios);
    free(bat_vetor.v);
}