#include "grafo.h"
#define MAX 200

int main(){
    int codigo = 0;
    p_grafo rede = criar_grafo(21);
    /*vetor que guarda quais pontos estao na rede*/
    int *pontos = calloc(21, sizeof(int));
    while(scanf("%d ", &codigo) != EOF){
        if (codigo == 1){
            adicionar(codigo, pontos);
        }else if(codigo == 2){
            conectar(rede);
        }else if(codigo == 3){
            desconectar(rede);
        }else if(codigo == 4){
            tem_conexao(rede);
        }else if(codigo == 5){
            caminho_minimo(rede);
        }else if(codigo == 6){                                                                                                      
            encontra_conexoes(rede, pontos);
        }
    }
    destruir_grafo(rede);
    free(pontos);
    return 0;
}