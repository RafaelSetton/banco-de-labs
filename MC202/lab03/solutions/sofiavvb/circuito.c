//implementacao
#include <stdio.h>
#include <stdlib.h>
#include "circuito.h"

/*aloca dinamicamente um vetor que guarda as jogadas de cada participante*/
int *aloca_jogadas(int participantes){
    int *jogadas = malloc(participantes * sizeof(int));
    if (jogadas == NULL) {
        printf("Nao ha memoria suficente !\n");
        exit (1);
    }
    return jogadas;
}

/*aloca dinamicamente um vetor de circuitos*/
circuito *aloca_circuitos(int n_circuitos){
    /*aloca um vetor de circuitos - organizando para cada partida*/
    circuito *circuitos = malloc(n_circuitos * sizeof(circuito));
    if (circuitos == NULL) {
        printf("Nao ha memoria suficente !\n");
        exit (1);
    }
    return circuitos;
}

/*le as informacoes de cada circuito o retornando*/
circuito ler_circuito(int participantes){
    circuito c;
    c.participantes = participantes;
    
    c.jogadas = aloca_jogadas(participantes);
    for (int i = 0; i < participantes + 1; i++){
        if (i == 0){
            scanf(" %d", &c.identificacao);
        }else{
            scanf(" %d", &c.jogadas[i-1]);
        }
    }
    return c;
}

/*encontra o circuito mais dificil e retorna sua identificacao*/
int acha_dificil(circuito *circuitos, int n_circuitos){
    int mais_dificil;
    int soma = 0, maior = 0;
    /*percorre pra cada circuito da partida*/
    for (int i = 0; i < n_circuitos; i++){
        /*percorre para cada jogada do circuito*/
        soma = 0;
        for (int j = 0; j < circuitos[i].participantes; j++){
            soma += circuitos[i].jogadas[j];
        }
        if (soma > maior){
            maior = soma;
            mais_dificil = circuitos[i].identificacao;
        }
    }
    return mais_dificil;
}

/*libera o vetor alocado dinamicamente de jogadas*/
void libera_jogadas(int *jogadas){
    free(jogadas);
}
