#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int n;          // Tamanho
    int t, b, l, r; // Indices de: Top, Bottom, Left, Right
    int **m;        // A matriz em si
} matriz;

int min(int a, int b, int c, int d)
{
    // Retorna o mínimo entre os 4 inteiros
    if (a < b && a < c && a < d)
        return a;
    if (b < c && b < d)
        return b;
    if (c < d)
        return c;
    return d;
}

void le_matriz(int n, matriz *mtz)
{
    // Inicializa a matriz com tamanho n a partir da entrada padrão
    mtz->m = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        mtz->m[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            scanf("%d", &(mtz->m[i][j]));
    }

    mtz->t = 0;
    mtz->l = 0;
    mtz->r = n - 1;
    mtz->b = n - 1;
    mtz->n = n;
}

void atualiza(matriz *mtz, int i, int j, int val)
{
    // Altera o valor em (i, j) para val e encontra a submatriz com maior soma

    mtz->m[mtz->t + i][mtz->l + j] = val;

    int sl = 0, sr = 0, st = 0, sb = 0; // Somas das linhas e colunas dos extremos
    for (int k = mtz->l; k <= mtz->r; k++)
    {
        st += mtz->m[mtz->t][k];
        sb += mtz->m[mtz->b][k];
    }
    for (int k = mtz->t; k <= mtz->b; k++)
    {
        sl += mtz->m[k][mtz->l];
        sr += mtz->m[k][mtz->r];
    }

    // Somas dos pares: Top-Left, Top-Right, Bottom-Left, Bottom-Right
    int tl = st + sl - mtz->m[mtz->t][mtz->l];
    int tr = st + sr - mtz->m[mtz->t][mtz->r];
    int bl = sb + sl - mtz->m[mtz->b][mtz->l];
    int br = sb + sr - mtz->m[mtz->b][mtz->r];

    int min_sum = min(tl, tr, bl, br);

    // Atualiza os limites da matriz
    if (min_sum == tl)
    {
        mtz->t++;
        mtz->l++;
    }
    else if (min_sum == tr)
    {
        mtz->t++;
        mtz->r--;
    }
    else if (min_sum == bl)
    {
        mtz->b--;
        mtz->l++;
    }
    else
    {
        mtz->b--;
        mtz->r--;
    }
    mtz->n--;
}

void imprime(matriz *mtz)
{
    // Imprime a matriz
    for (int i = mtz->t; i <= mtz->b; i++)
    {
        for (int j = mtz->l; j <= mtz->r; j++)
            printf("%d\t", mtz->m[i][j]);
        printf("\n");
    }
}

int main()
{
    int cl;
    matriz mtz;
    scanf("%d", &cl);
    le_matriz(cl, &mtz);

    printf("Quadras:\n");
    imprime(&mtz);

    int alt;
    int i = 0, j = 0, val = mtz.m[0][0]; // Inicializa com valores que não alteram
                                         // a matriz para apenas buscar a submatriz de maior soma

    while (mtz.n > 1)
    {
        atualiza(&mtz, i, j, val);
        printf("\nConjuntos que precisam de atenção:\n");
        imprime(&mtz);

        scanf("%d", &alt);
        if (alt == 0)
            break;
        scanf("%d %d %d", &i, &j, &val);
    }

    for (int i = 0; i < cl; i++)
        free(mtz.m[i]);
    free(mtz.m);

    return 0;
}