#include <stdio.h>
#define L 300
#define C 300
#define P 300
#define MAX 21


void le_matriz(char matriz[][C], int linhas, int colunas){
    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            scanf(" %s", &matriz[i][j]);
        }
    }
}


void le_palavras(char palavras[][MAX], int n_palavras){
    for (int i = 0; i < n_palavras; i++){
        scanf("%s", palavras[i]);
    }
}


void imprime_palavra(char palavras[][MAX], int m){
    printf("A palavra ");
    for (int i = 0; palavras[m][i] != '\0'; i++){
        printf("%c", palavras[m][i]);
    }
}


int procura_direita(char palavras[][MAX], char matriz[][C],
int i, int j, int index){
    //proxima letra da palavra e prox coluna da matriz
    int k = 1;
    j ++;

    while (palavras[index][k] != '\0' && matriz[i][j] != '\0'){
        if(palavras[index][k] != matriz[i][j]){
            return 0;
        }
        k++;
        j++;
    }
    /*se a palavra de fato acabou, pq pode ter encontrado matchs
    mas a linha da matriz acabou*/
    if (palavras[index][k] == '\0') {
        return 1;
    }
    return 0;
}


int procura_abaixo(char palavras[][MAX], char matriz[][C],
int i, int j, int index, int linhas, int colunas){
    //proxima letra da palavra e prox linha da matriz
    int k = 1;
    i++;

    while (palavras[index][k] != '\0' && (i < linhas) && (j < colunas)){
        if(palavras[index][k] != matriz[i][j]){
            return 0;
        }
        k++;
        i++;
    }
    /*se a palavra de fato acabou, pq pode ter encontrado matchs
    mas a linha da matriz acabou*/
    if (palavras[index][k] == '\0') {
        return 1;
    }
    return 0;
}


int procura_esquerda(char palavras[][MAX], char matriz[][C],
int i, int j, int index){
    //proxima letra da palavra e coluna anterior da matriz
    int k = 1;
    j--;

    while (palavras[index][k] != '\0' && matriz[i][j] != '\0'){
        if(palavras[index][k] != matriz[i][j]){
            return 0;
        }
        k++;
        j--;
    }
    /*se a palavra de fato acabou, pq pode ter encontrado matchs
    mas a linha da matriz acabou*/
    if (palavras[index][k] == '\0') {
        return 1;
    }
    return 0;
}


int procura_cima(char palavras[][MAX], char matriz[][C],
int i, int j, int index){
    //proxima letra da palavra e linha anterior da matriz
    int k = 1;
    i--;

    while (palavras[index][k] != '\0' && matriz[i][j] != '\0'){
        if(palavras[index][k] != matriz[i][j]){
            return 0;
        }
        k++;
        i--;
    }
    /*se a palavra de fato acabou, pq pode ter encontrado matchs
    mas a linha da matriz acabou*/
    if (palavras[index][k] == '\0') {
        return 1;
    }
    return 0;
}


int busca(char palavras[][MAX], char matriz[][C],
int linhas, int colunas, int index){

    char letra_palavra = palavras[index][0], alvo;

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            alvo = matriz[i][j];
            //se deu match
            if (letra_palavra == alvo){
                if ((procura_direita(palavras, matriz, i, j, index)) && (j != colunas)){
                    return 1;
                }else if ((procura_abaixo(palavras, matriz, i, j, index, linhas, colunas)) && (i != linhas)){
                    return 1;
                }else if ((procura_esquerda(palavras, matriz, i, j, index)) && (j != 0)){
                    return 1;
                }else if ((procura_cima(palavras, matriz, i, j, index)) && (i != 0)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main(){
    int linhas = 0, colunas = 0, n_palavras = 0, achou = 0;
    char matriz[L][C], palavras[P][MAX];

    scanf("%d %d %d", &linhas, &colunas, &n_palavras);
    le_matriz(matriz, linhas, colunas);
    le_palavras(palavras, n_palavras);
    for (int i = 0; i < n_palavras; i++){
        achou = busca(palavras, matriz, linhas, colunas, i);
        if (achou){
            imprime_palavra(palavras, i);
            printf(" está no texto!\n");
        }else{
            imprime_palavra(palavras, i);
            printf(" não está no texto!\n");
        }
    }
    return 0;
}
