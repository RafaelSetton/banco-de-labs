#include <stdio.h>
#include <stdlib.h>
/*alocar a matriz dada uma dimensao*/
int **aloca(int dimensao){
    int **matriz = malloc(dimensao * sizeof(int *));
    for (int i = 0; i < dimensao; i++)
        matriz[i] = malloc(dimensao * sizeof(int));
    return matriz;
}
/*libera uma matriz alocada*/
void libera(int dimensao, int **matriz){
    for (int i = 0; i < dimensao; i++)
        free(matriz[i]);
    free(matriz);
}
/*ler os valores e inicializar a matriz*/
void ler_matriz(int dimensao, int **matriz){
    for (int i = 0; i < dimensao; i++){
        for (int j = 0; j < dimensao; j++){
            scanf("%d ", &matriz[i][j]);
        } 
    }
}
/*imprimir a matriz formatada com \t*/
void imprime_matriz(int dimensao, int** matriz){
    for (int i = 0; i < dimensao; i++){
        for (int j = 0; j < dimensao; j++){
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}
/*encontrar a submatriz com maior soma e ela
passa a ser a matriz "original"*/
int **calcula_submatriz(int *dimensao, int** matriz){
    /*aloca um espaco para a submatriz*/
    int **sub = aloca(*dimensao - 1);
    int soma = 0, maior = -273842, maior_i = 0, maior_j = 0;
    
    for (int m = 0; m < 2; m++){
        for (int n = 0; n < 2; n++){
            soma = 0;
            for (int i = m; i < (*dimensao - 1) + m; i++){
                for (int j = n; j < (*dimensao - 1) + n; j++){
                    soma += matriz[i][j];
                }
            }
            if (soma > maior){
                maior = soma;
                maior_i = m;
                maior_j = n;
            }
        }
    }
    /*copia a submatriz de maior soma*/
    int m = 0;
    for(int i = maior_i; i < *dimensao - 1 + maior_i; i++){
        int n = 0;
        for(int j = maior_j; j < *dimensao - 1 + maior_j; j++){
            sub[m][n] = matriz[i][j];
            n++;
        }
        m++;
    }
    /*libera o espaco da matriz "original"*/
    libera(*dimensao, matriz);
    /*atualiza a nova dimensao da matriz*/
    *dimensao = *dimensao - 1;
    return sub;
}
/*altera um valor dado a posicao*/
void alterar(int dimensao, int **matriz){
    int i = 0, j = 0, valor;
    scanf("%d %d %d ", &i, &j, &valor);
    matriz[i][j] = valor;
}

int main(){

    int lc, alt = 1;
    int **matriz;
    /*recebe a dimensao da matriz original - quadra*/
    scanf("%d", &lc);
    /*aloca a matriz original*/
    matriz = aloca(lc);
    /*inicializa ela com os valores dados pelo usuario*/
    ler_matriz(lc, matriz);
    /*imprime ela formatada bonitinha*/
    printf("Quadras:\n");
    imprime_matriz(lc, matriz);
    printf("\n");
    /*calcula a submatriz quadrada de maior soma*/
    matriz = calcula_submatriz(&lc, matriz);

    /*se a dimensao dela for maior que 1x1, checamos se o usuario
    pediu alt, e depois calculamos a submatriz dnv*/
    while(lc >= 1 && alt == 1){
        printf("Conjuntos que precisam de atenção:\n");
        imprime_matriz(lc, matriz);
        printf("\n");
        alt = 0;
        if (lc >= 2)
            scanf("%d", &alt);
        
        if (alt == 1){
            alterar(lc, matriz);
        }
        matriz = calcula_submatriz(&lc, matriz);
    }
    libera(lc, matriz);
    return 0;
}
