#include "hashnopolis.h"

int main(){

    int finalizar = 0;
    p_hash hash = criar_hash();
    char instrucao[30];
    while (!finalizar){
        scanf("%s", instrucao);
        if (strcmp(instrucao, "ENTRAR") == 0){
            p_fam familia = criar_familia();
            entrar(hash, familia);
        }else if (strcmp(instrucao, "SAIR") == 0){
            sair(hash);
        }else if (strcmp(instrucao, "COMPRAR") == 0){
            comprar(hash);
        }else if (strcmp(instrucao, "TRICKORTREAT") == 0){
            trick_or_treat(hash);
        }else{
            finalizar = 1;
        }
    }
    destruir_hash(hash);
    return 0;
}