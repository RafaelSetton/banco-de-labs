#include <stdio.h>
#include <stdlib.h>
#include "esteira.h"
#include "funcionario.h"
#include "pilha.h"

int main(){
    int tam_esteira = 0, tam_pilha = 0, entradas = 0, atraso = 0, embaladas = 0, cont = 0,
    entraram_class = 0, sairam_class = 0, entraram_emb = 0, sairam_emb = 0, min = 1;

    scanf("%d %d", &tam_esteira, &tam_pilha);
    scanf("%d", &entradas);

    p_peca p_atual;
    p_fila fila = criar_fila(tam_esteira);
    p_pilha pilha = criar_pilha(tam_pilha);
    funcionario class = criar_funcionario(), embal = criar_funcionario();   
    printf("##### Simulação\n");
    
    //crio um vetor para guardar todas as peças
    p_peca *pecas = malloc(entradas * sizeof(p_peca));
    for (int i = 0; i < entradas; i++){
        pecas[i] = criar_peca();
    }
    p_atual = pecas[cont];

    do{
        entraram_class = 0, sairam_class = 0, entraram_emb = 0, sairam_emb = 0;
        //se o embalador trabalhou tempo suficiente na peça, ela ta pronta
        if (embal.peca_trabalho != NULL){
            if(embal.tempo_ocupado == tempo_embal(embal.peca_trabalho)){
                sairam_emb++;
                embaladas++;
                //o embalador fica livre de novo
                embal.livre = 1;
                embal.tempo_ocupado = 0;
            }
        }

        //se embalador livre, vamos checar se pode embalar
        if (livre(embal)){
            //se a pilha tem coisa e o topo dela ja passou pelo menos 1 min la
            if(!pilha_vazia(pilha)){
                embalar(&embal, pilha);
            }
        }else{
            trabalhando(&embal);
        }
        //se o classificador trabalhou suficiente, ela ta pronta pra mandar pra pilha
        if (class.peca_trabalho != NULL){
            if(class.tempo_ocupado >= tempo_class(class.peca_trabalho)){
                //se a pilha tem espaço
                if (!pilha_cheia(pilha)){
                    //manda peca pra pilha
                    push(pilha, class.peca_trabalho);
                    sairam_class++;
                    entraram_emb++;
                    //fica livre dnv
                    class.livre = 1;
                    class.tempo_ocupado = 0;
                }else{
                    //se a pilha ta cheia, ele fica com a peça na mao
                    trabalhando(&class);
                }
            }
        }
        //se classificador livre, vamos checar se pode classific
        if (livre(class)){
            //se a fila tem coisa
            if(!fila_vazia(fila)){
               classificar(&class, fila);
            }
        }else{
            trabalhando(&class);
        }
        //se a esteira não ta cheia, enfileiramos a peça atual na linha de prod
        if (!fila_cheia(fila)){
            //se ainda tem peça para passar pela esteira
            if (cont < entradas){
                enfileira(fila, p_atual);
                entraram_class++;
                cont++;
                if (cont < entradas){
                    p_atual = pecas[cont];
                }
            }
        }else{
            //caso contrario, há atraso
            if (cont != entradas){
                atraso++;
            }
        }
        printf("Min. %d: Classificação (+%d,-%d) | Embalagem (+%d,-%d).\n", min,
        entraram_class, sairam_class, entraram_emb, sairam_emb);
        min++;
    }while(embaladas != entradas);
    printf("Tempo atraso: %d.", atraso);
    destruir_pecas(pecas, entradas);
    free(pecas);
    destruir_fila(fila);
    destruir_pilha(pilha);
    return 0;
}