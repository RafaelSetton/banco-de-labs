#include <stdio.h>
#define MAX 301

int busca_linear(char palavra[], char documento[][MAX], int l, int c, int i, int j, int dl, int dc)
{
    // Procura a palavra a partir de documento[i][j] seguindo a direção definida por dl e dc

    for (int k = 1; k < 21; k++)
    {
        i += dl;
        j += dc;

        if (palavra[k] == '\n')
            return 1;

        if (i < 0 || i >= l || j < 0 || j >= c)
            return 0;

        if (palavra[k] != documento[i][j])
            return 0;
    }
    return 0;
}

int busca_matriz(char palavra[], char documento[][MAX], int l, int c)
{
    // Procura a palavra no documento e retorna 1 se encontrar e 0 caso contrário
    // l e c são respectivamente o número de linhas e colunas do documento
    for (int i = 0; i < l; i++)
        for (int j = 0; j < c; j++)
            if (documento[i][j] == palavra[0])
                if (busca_linear(palavra, documento, l, c, i, j, 0, 1) ||
                    busca_linear(palavra, documento, l, c, i, j, 0, -1) ||
                    busca_linear(palavra, documento, l, c, i, j, 1, 0) ||
                    busca_linear(palavra, documento, l, c, i, j, -1, 0))
                    return 1;
    return 0;
}

int main()
{
    int l, c, p;
    char documento[MAX][MAX], palavra[21];

    scanf("%d %d %d ", &l, &c, &p);
    for (int i = 0; i < l; i++)
        for (int j = 0; j < c; j++)
            scanf("%c ", &documento[i][j]);

    for (int i = 0; i < p; i++)
    {
        fgets(palavra, 21, stdin);
        if (busca_matriz(palavra, documento, l, c))
            printf("A palavra %s está no texto!\n", palavra);
        else
            printf("A palavra %s não está no texto!\n", palavra);
    }

    return 0;
}