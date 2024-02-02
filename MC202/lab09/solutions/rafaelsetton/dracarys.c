#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include "no.h"

#define MAX 210

int eh_tipo(char *tipo)
{
    // Retorna 1 se a string for o nome de um tipo e 0 caso contrário
    char *tipos[3] = {
        "int", "char", "double"};
    for (int i = 0; i < 3; i++)
        if (strcmp(tipo, tipos[i]) == 0)
            return 1;
    return 0;
}

int eh_declaracao(char *linha, char simbolo[], char tipo[])
{
    // Retorna 1 se a linha for a declaração de uma variável e armazena o simbolo e o tipo nos respectivos ponteiros
    tipo[0] = '\0';
    simbolo[0] = '\0';
    sscanf(linha, "%s %s", tipo, simbolo);

    return eh_tipo(tipo);
}

int eh_operacao(char *linha, char v1[], char v2[], char v3[], char op[])
{
    // Retorna 1 se a linha for uma operação entre variáveis e armazena as informações nos ponteiros v1, v2, v3 e op
    int n = sscanf(linha, "%s = %s %c %s", v1, v2, op, v3);

    return n == 4;
}

int ignora(char *linha)
{
    // Retorna 1 se a linha deve ser ignorada
    char primeira_palavra[100];
    sscanf(linha, "%s", primeira_palavra);
    return (!isalpha(primeira_palavra[0])) || (strchr(linha, '(') != NULL) || (strchr(linha, ')') != NULL);
}

int main()
{
    char linha[MAX];
    int line_num = 0, erros = 0;
    p_no raiz = NULL;
    char simbolo[MAX], tipo[MAX];
    char v1[MAX], v2[MAX], v3[MAX], op[MAX];

    while (++line_num) // Contagem da linha
    {
        linha[0] = '\0';
        fgets(linha, MAX, stdin);
        if (feof(stdin))
            break;

        if (ignora(linha))
            continue;

        if (eh_declaracao(linha, simbolo, tipo))
            raiz = inserir(raiz, simbolo, tipo);
        else if (eh_operacao(linha, v1, v2, v3, op))
        {
            erros++; // Inicialmente presume que há um erro nessa linha

            v3[strlen(v3) - 1] = '\0'; // Remover o ; no final
            p_no var1, var2, var3;
            var1 = buscar(raiz, v1);
            var2 = buscar(raiz, v2);
            var3 = buscar(raiz, v3);

            // Verifica se todas as variaveis estão definidas
            if (var1 == NULL)
                printf("Linha %d: o símbolo %s não foi definido.\n", line_num, v1);
            else if (var2 == NULL)
                printf("Linha %d: o símbolo %s não foi definido.\n", line_num, v2);
            else if (var3 == NULL)
                printf("Linha %d: o símbolo %s não foi definido.\n", line_num, v3);
            // Checagem de tipos
            else if (strcmp(var2->tipo, var3->tipo) != 0)
                printf("Linha %d: tipos incompatíveis: %s (%s) %s %s (%s).\n", line_num, var2->simbolo, var2->tipo, op, var3->simbolo, var3->tipo);
            else if (strcmp(var1->tipo, var2->tipo) != 0)
                printf("Linha %d: tipos incompatíveis: o símbolo %s espera %s, obteve %s.\n", line_num, var1->simbolo, var1->tipo, var2->tipo);
            else
                erros--; // Se não houver erro, desconta o acréscimo que foi feito
        }
    }

    if (erros == 0)
        printf("Não há erros de tipo.\n");
    imprimir(raiz);
}