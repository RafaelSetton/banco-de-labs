#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#define MAX 60

int main(){

    char entrada[MAX], comando[15], livro[45];
    //variaveis que controlam onde tem que inserir
    int inicio = 0, final = 0;
    p_lista lista = criar_lista();
    p_no ultimo = NULL;

    //lemos entradas e mexemos na lista de livros até EOF
    while (fgets(entrada, MAX, stdin) != NULL){
        //separo o comando e o livro
        separar_entrada(entrada, comando, livro);
        if (strcmp(comando, "inicio") == 0){
            //controlo q é pra adicionar no inicio
            inicio = 1;
            final = 0;
        }else if(strcmp(comando,"final") == 0){
            //controlo q é pra adicionar no final
            inicio = 0;
            final = 1;
        }else{
            if(strcmp(comando, "adicionar") == 0){
                ultimo = adicionar(lista, livro, &inicio, &final, ultimo);
            }else if(strcmp(comando, "remover") == 0){
                remover(lista, livro, ultimo, &inicio, &final);
            }else if(strcmp(comando, "imprimir") == 0){
                imprimir(lista);
                printf("\n");
            }
        }
    }
    destruir(lista->inicio);
    free(lista);
    return 0;
}