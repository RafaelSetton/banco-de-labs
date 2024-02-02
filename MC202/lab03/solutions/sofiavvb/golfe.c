#include <stdio.h>
#include <stdlib.h>
#include "partida.h"

int main(){
    int n_partidas;
    partida *partidas;

    scanf("%d", &n_partidas);
    //alocando um vetor que guardará as partidas
    partidas = aloca_partidas(n_partidas);
    //organiza cada partida, seus circuitos e todas as infos relacionadas
    for (int i = 0; i < n_partidas; i++){
        partidas[i] = ler_partida(i);
    }
    /*imprime o relatório de cada partida e depois
    libera tudo que foi alocado dinamicamente nelas*/
    for (int i = 0; i < n_partidas; i++){
        imprime_relatorio(partidas[i]);
        libera_circuitos(partidas[i]);
    }
    free(partidas);
    return 0;
}