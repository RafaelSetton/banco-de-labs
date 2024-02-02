#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

void entrar(p_hash t)
{
    char sobrenome[15];
    int qtd_doces;
    scanf("%s %d", sobrenome, &qtd_doces);
    inserir(t, sobrenome, qtd_doces);
}

void sair(p_hash t)
{
    char sobrenome[15];
    scanf("%s", sobrenome);
    p_familia fam = buscar(t, sobrenome);
    printf("A familia %s saiu com %d doce(s) sobrando.\n", sobrenome, fam->qtd_doces);
    remover(t, sobrenome);
}

void comprar(p_hash t)
{
    char sobrenome[15];
    int qtd_doces;
    scanf("%s %d", sobrenome, &qtd_doces);
    p_familia fam = buscar(t, sobrenome);
    fam->qtd_doces += qtd_doces;
    printf("A familia %s agora possui %d doces.\n", sobrenome, fam->qtd_doces);
}

void trick_or_treat(p_hash t)
{
    char nome_crianca[12], sobrenome_crianca[12], sobrenome_familia[12], nota[10];
    int qtd_casas, doces = 0, max;
    p_familia fam;

    scanf("%s %s %d ", nome_crianca, sobrenome_crianca, &qtd_casas);

    for (int i = 0; i < qtd_casas; i++)
    {
        scanf("%s %s", sobrenome_familia, nota);

        if (nota[0] == 'B') // "Boa"
            max = 3;
        else if (nota[0] == 'M') // "Media"
            max = 2;
        else // "Ruim"
            max = 1;

        fam = buscar(t, sobrenome_familia);
        if (fam->qtd_doces > max)
        {
            fam->qtd_doces -= max;
            doces += max;
        }
        else if (fam->qtd_doces > 0) // Se já tiver 0 doces, não precisa fazer nada
        {
            doces += fam->qtd_doces;
            fam->qtd_doces = 0;
            printf("A familia %s ficou sem doces.\n", sobrenome_familia);
        }
    }

    if (doces > 0)
        printf("%s %s recebeu %d doce(s) das familias.\n", nome_crianca, sobrenome_crianca, doces);
    else
        printf("%s %s recebeu 10 doces da prefeitura.\n", nome_crianca, sobrenome_crianca);
}

int main()
{
    p_hash t = criar_hash();
    char comando[15];
    while (1)
    {
        scanf("%s ", comando);
        if (strcmp(comando, "ENTRAR") == 0)
            entrar(t);
        else if (strcmp(comando, "SAIR") == 0)
            sair(t);
        else if (strcmp(comando, "COMPRAR") == 0)
            comprar(t);
        else if (strcmp(comando, "TRICKORTREAT") == 0)
            trick_or_treat(t);
        else
            break;
    }
    destruir_hash(t);
}