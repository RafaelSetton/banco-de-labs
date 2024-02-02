#include <stdio.h>
#define N 10000

void le_lista(int lista[], int numero_saladas);
void contar_tipos(int lista[], int numero_saladas);
void acha_sequencia(int lista[], int numero_saladas);

int main(){
    int lista[N], numero_saladas = 0;

    scanf("%d", &numero_saladas);
    le_lista(lista, numero_saladas);
    contar_tipos(lista, numero_saladas);
    acha_sequencia(lista, numero_saladas);
    return 0;
}


void le_lista(int lista[], int numero_saladas){
    //cria um vetor com as entradas dos pixs de cada tipo
    for (int i = 0; i < numero_saladas; i++)
        scanf("%d", &lista[i]); 
}


void acha_sequencia(int lista[], int numero_saladas){
    //encontra a maior sequência consecutiva de salada do mesmo
    //tamanho e qual o tipo dela. Em caso de empate, reporta a primeira
    //sequencia encontrada
    int atual = lista[0], ocorr_atual = 1,
    ocorr_maior = 0, maior = 0;

    for (int i = 1; i < numero_saladas; i++){
        if (lista[i] == atual){
            ocorr_atual++;
            if (ocorr_atual > ocorr_maior){
                ocorr_maior = ocorr_atual;
                maior = atual;
            }
        }
        else{
            ocorr_atual = 1;
            atual = lista[i];
        }

    }
    printf("James vendeu %d saladas de %d reais consecutivamente\n", ocorr_maior, maior);
}

void contar_tipos(int lista[], int numero_saladas){
    //conta quantos pix de cada tipo foram realizados
    int salada_barata = 0, salada_meio = 0, salada_cara = 0;

    for(int i = 0; i < numero_saladas; i++){
        if (lista[i] == 5) 
            salada_barata++;
        else if (lista[i] == 7)
            salada_meio++;
        else if (lista[i] == 10)
            salada_cara++;
    }

    printf("James vendeu %d saladas de 5 reais, %d de 7 reais e %d de 10 reais\n",
    salada_barata, salada_meio, salada_cara);
}