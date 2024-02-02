//implementacao
#include <stdio.h>
#include <stdlib.h>
#include "partida.h"

/*aloca dinamicamente um vetor de partidas*/
partida *aloca_partidas(int n_partidas){
    /*aloca um vetor de partidas - organizando o todo*/
    partida *partidas = malloc(n_partidas * sizeof(partida));
    if (partidas == NULL) {
        printf("Nao ha memoria suficiente !\n");
        exit (1);
    }
    return partidas;
}

/*calcula o aluguel da partida e o retorna*/
float calcula_aluguel(partida a){
    float aluguel;
    aluguel = (10 * a.n_circuitos) + (17.50 * a.equipamentos);
    return aluguel;
}

/*le, organiza e inicializa uma partida, a retornando*/
partida ler_partida(int identificacao){
    partida a;
    a.identificacao = identificacao + 1;
    
    scanf("%d %d %d", &a.participantes, &a.n_circuitos, &a.equipamentos);
    a.circuitos = aloca_circuitos(a.n_circuitos);
    for (int i = 0; i < a.n_circuitos; i++){
        a.circuitos[i] = ler_circuito(a.participantes);
    }
    a.aluguel = calcula_aluguel(a);
    return a;
}

/*libera o vetor de circuitos alocados dinamicamente*/
void libera_circuitos(partida a){
    for (int i = 0; i < a.n_circuitos; i++){
        free(a.circuitos[i].jogadas);
    }
    free(a.circuitos);
}

/*imprime o relatorio da partida*/
void imprime_relatorio(partida a){
    int total;

    printf("Partida %d\n", a.identificacao);
    printf("Num. de Jogadores: %d - Num. de Circuitos: %d - Num. de Equipamentos: %d\n",
    a.participantes, a.n_circuitos, a.equipamentos);
    printf("Valor do Aluguel: R$ %.2f\n", a.aluguel);
    for (int i = 0; i < a.participantes; i++){
        total = 0;
        for (int j = 0; j < a.n_circuitos; j++){
            total += a.circuitos[j].jogadas[i];
        }
        printf("Jogador %d: %d\n", i+1, total);
    }
    printf("Circuito mais dificil: %d\n", acha_dificil(a.circuitos, a.n_circuitos));
    printf("##########\n");
}
