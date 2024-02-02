#include <stdio.h>
#include <stdlib.h>
#include "batmemory.h"

p_vetor criar_vetor(int tam){
    p_vetor v;
    v = malloc(sizeof(struct vetor));
    v->dados = malloc(tam * sizeof(int));
    v->uso = 0;
    v->alocado = tam;
    return v;
}

void destruir_vetor(p_vetor v){
    free(v->dados);
    free(v);
}

void atualiza_batuso(p_vetor batmemory, int tamanho){
    batmemory->uso = batmemory->uso + tamanho;
}

void bat_uso(p_vetor batmemory){
    printf("%d de %d\n", batmemory->uso, batmemory->alocado);
}

void dobrar(p_vetor v){
    int *temp = v->dados;
    v->alocado *= 2;
    v->dados = malloc(v->alocado * sizeof(int));
    for (int i = 0; i < v->alocado / 2; i++){
        v->dados[i] = temp[i];
    }
    free(temp);
}

void reduzir(p_vetor v){
    int *temp = v->dados;
    v->alocado /= 2;
    v->dados = malloc(v->alocado * sizeof(int));
    for (int i = 0; i < v->alocado; i++){
        v->dados[i] = temp[i];
    }
    free(temp);
}

int checar_espaco(p_vetor batmemory, p_vetor inicios, int tamanho){
    int cont = 0, inicio;
    for (int i = 0; i <= batmemory->alocado; i++){
            /*se o indice que ele ta olhando da batmemory n ta
            vetor de inicios, somo um no contador*/
            if (busca(inicios, i) == -1){
                cont++;
                if (cont == tamanho + 1){
                    inicio = abs(cont - i - 1);
                    return inicio;
                }
            }
            else{
                cont = 0;
                i += batmemory->dados[i];
            }
    }
    return -1;
}

void bat_alloc(p_vetor batmemory, p_vetor inicios){
    int tamanho = 0;
    scanf(" %d", &tamanho);
    /*se a batmemory ta vazia*/
    if (inicios->uso == 0){
        inicios->dados[0] = 0;
        batmemory->dados[0] = tamanho;
        inicios->uso++;
        for (int i = 1; i <= tamanho; i++){
            scanf(" %d", &(batmemory->dados[i]));
        }
        atualiza_batuso(batmemory, tamanho + 1);
        printf("0\n");
    }else{
        //dobro se n tem espaço continuo que caiba o vetor que quero alocar
        int aux = checar_espaco(batmemory, inicios, tamanho);
        if (aux == -1){
            dobrar(batmemory);
        }
        aux = checar_espaco(batmemory, inicios, tamanho);
        printf("%d\n", aux);
        batmemory->dados[aux] = tamanho;
        if (inicios->uso == inicios->alocado)
            dobrar(inicios);
        inicios->dados[inicios->uso] = aux;
        inicios->uso++;
        for (int j = aux + 1; j <= aux + tamanho; j++){
            scanf(" %d", &(batmemory->dados[j]));
        }
        atualiza_batuso(batmemory, tamanho + 1);
    }
}

void bat_free(p_vetor batmemory, p_vetor inicios)
{
    int endereco, reduz = 1;
    scanf(" %d", &endereco);
    int index = busca(inicios, endereco);
    remover_elemento(inicios, index);
    atualiza_batuso(batmemory, -(batmemory->dados[endereco] + 1));
    /*checa se tem algum elemento no vetor de inicios maior que o primeiro quarto*/
    for (int i = 0; i < inicios->uso; i++){
        if (inicios->dados[i] > (batmemory->alocado / 4) - 1){
            reduz = 0;
        }
    }
    if (reduz && batmemory->alocado > 16){
        reduzir(batmemory);
    }
}

int busca(p_vetor v, int x){
    int i;
    for (i = 0; i < v->uso; i++)
        if (v->dados[i] == x)
            return i;
    return -1;
}

void remover_elemento(p_vetor v, int index){
    /*passa todo mundo para a esquerda*/
    for (int i = index; i < (v->uso) - 1; i++){
        v->dados[i] = v->dados[i + 1];
    }
    /*reduz um do espaço usado*/
    v->uso--;
    /*se ta 1/4 cheio, reduzimos ele a metade*/
    if (v->uso <= v->alocado / 4 && v->alocado > 16){
        reduzir(v);
    }
}

void bat_print(p_vetor batmemory, p_vetor inicios){
    int endereco;
    scanf(" %d", &endereco);
    for (int i = 1; i <= batmemory->dados[endereco]; i++){
        printf("%d ", batmemory->dados[endereco + i]);
    }
    printf("\n");
}
