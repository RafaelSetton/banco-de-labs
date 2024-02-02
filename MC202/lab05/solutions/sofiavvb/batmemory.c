#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batmemory.h"

int main(){

    int instr = 0;
    char comandos[15];
    p_vetor batmemory, inicios;

    batmemory = criar_vetor(8);
    inicios = criar_vetor(8);
    scanf("%d", &instr);

    while (instr > 0){
        scanf("%s", comandos);

        if (strcmp(comandos, "bat-alloc") == 0){
            bat_alloc(batmemory, inicios);
        }
        else if (strcmp(comandos, "bat-print") == 0){
            bat_print(batmemory, inicios);
        }
        else if (strcmp(comandos, "bat-uso") == 0){
            bat_uso(batmemory);
        }
        else if (strcmp(comandos, "bat-free") == 0){
            bat_free(batmemory, inicios);
        }
        instr--;
    }
    destruir_vetor(inicios);
    destruir_vetor(batmemory);
    return 0;
}