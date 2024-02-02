#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "arvore.h"
#define MAX 200

int main(){

    int cont = 0, erro = 0;
    char linha[MAX], tipo[10], nome[MAX], prim_palav[MAX],
    nome1[MAX], nome2[MAX], nome3[MAX];
    char *parenteses;
    char igual, operador;
    p_no raiz = criar_arvore();

    while(fgets(linha, MAX, stdin) != NULL){
        /*se a linha eh vazia*/
        if (linha[0] == '\n'){
            cont++;
            continue;
        }
        parenteses = strchr(linha, '(');
        sscanf(linha, "%s", prim_palav);
        cont++;
        
        /*se tiver parenteses - "parenteses" n eh NULL - ou a primeira palavra nao comeca com uma letra, ignoramos*/
        if(parenteses != NULL || !isalpha(prim_palav[0])){
            continue;
        }
        /*se a primeira palavra eh um tipo, sabemos que temos uma declaracao*/
        else if(eh_tipo(prim_palav)){
            sscanf(linha, "%s %s", tipo, nome);
            /*tira o ;*/
            nome[strlen(nome) - 1] = '\0';
            /*cria o simbolo e add na arvore*/
            simbolo simb = criar_simbol(tipo, nome);
            raiz = inserir(raiz, simb);
        }
        /*se tem operadores na linha, sabemos que eh expressao*/
        else if(eh_operacao(linha)){
            p_no simb1, simb2, simb3;
            /*ler as variaveis*/
            sscanf(linha, "%s %c %s %c %s", nome1, &igual, nome2, &operador, nome3);
            nome3[strlen(nome3) - 1] = '\0';
            simb1 = buscar(raiz, nome1), simb2 = buscar(raiz, nome2), simb3 = buscar(raiz, nome3);
            /*verificacoes: */
            /*se alguma variavel não foi declarada*/
            if(erro_declaracao(cont, raiz, simb1, simb2, simb3)){
                if (simb1 == NULL){
                    printf("Linha %d: o símbolo %s não foi definido.\n", cont, nome1);
                    continue;
                }else if (simb2 == NULL){
                    printf("Linha %d: o símbolo %s não foi definido.\n", cont, nome2);
                    continue;
                }else if (simb3 == NULL){
                    printf("Linha %d: o símbolo %s não foi definido.\n", cont, nome3);
                    continue;
                }
                erro = 1;
            }
            /*se os tipos do segundo símbolo e terceiro são diferentes para serem operados.*/
            else if(operandos_diff(cont, operador, raiz, simb2, simb3)){
                erro = 1;
                continue;
            }
            /*se o resultado da operação possui o mesmo tipo que a variável que o receberá.*/
            else if(resultado_diff(cont, raiz, simb1, simb2, simb3)){
                erro = 1;
                continue;
            }
        }
    }
    /*se não teve erros*/
    if (!erro){
        printf("Não há erros de tipo.\n");
    }
    imprimir_arvore(raiz);
    destruir_arvore(raiz);
    return 0;
}