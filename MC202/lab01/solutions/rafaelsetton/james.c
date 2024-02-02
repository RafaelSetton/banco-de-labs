#include <stdio.h>
#define MAX (int)1e4 + 2

void le_vendas(int n, int array[])
{
    // Lê o valor das n vendas e armazena no array
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);
}

int main()
{
    int n;
    scanf("%d", &n);
    int vendas[11], saladas[MAX];
    for (int i = 0; i < 11; i++)
        vendas[i] = 0;

    int maior_sequencia = 1, seq_atual = 1, valor_maior_sequencia;

    le_vendas(n, saladas);

    for (int i = 0; i < n; i++)
    {
        vendas[saladas[i]]++;
        if (i == 0)
            valor_maior_sequencia = saladas[0];
        else if (saladas[i] == saladas[i - 1])
        {
            // Incrementa a sequencia de vendas e atualiza a maior sequencia (se necessário)
            seq_atual++;
            if (seq_atual > maior_sequencia)
            {
                maior_sequencia = seq_atual;
                valor_maior_sequencia = saladas[i - 1];
            }
        }
        else
            seq_atual = 1;
    }

    printf("James vendeu %d saladas de 5 reais, %d de 7 reais e %d de 10 reais\n", vendas[5], vendas[7], vendas[10]);
    printf("James vendeu %d saladas de %d reais consecutivamente\n", maior_sequencia, valor_maior_sequencia);
}
