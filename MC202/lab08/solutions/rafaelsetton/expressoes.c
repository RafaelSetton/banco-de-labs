#include <stdio.h>
#include "no.h"
#include "stack.h"

int main()
{
    int n;
    scanf("%d", &n);
    char exp[100];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", exp);
        p_no raiz = gera_arvore(exp);

        imprime(raiz, 1);
        otimiza(raiz);
        imprime(raiz, 1);
        printf("\n");

        destroi(raiz);
    }
}