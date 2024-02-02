#include "hashnopolis.h"

p_hash criar_hash(){
    p_hash hash = malloc(sizeof(Hash));
    hash->familias = calloc(MAX, sizeof(p_fam));
    return hash;
}

p_fam criar_familia(){
    p_fam familia = malloc(sizeof(Familia));
    scanf(" %s %d", familia->nome, &familia->doces);
    familia->removida = 0;
    return familia;
}

Crianca criar_crianca(){
    Crianca kid;
    scanf("%s %s %d", kid.nome, kid.sobrenome, &kid.casas);
    return kid;
}

void trick_or_treat(p_hash fams){
    char nome[11], nota[11];
    int valor, recebido = 0;
    Crianca kid = criar_crianca();
    /*para cada familia visitada, trick or treat?!*/
    for(int i = 0; i < kid.casas; i++){
        scanf(" %s %s", nome, nota);
        valor = converter_nota(nota);
        p_fam fam = buscar(fams, nome);
        if (fam->doces != 0){
            if (fam->doces >= valor){
                fam->doces -= valor;
                recebido += valor;
            }else{
                /*recebe o maximo que a familia puder dar*/
                recebido += fam->doces;
                fam->doces = 0;
            }
            /*se a familia fica sem doces*/
            if (fam->doces == 0){
                printf("A familia %s ficou sem doces.\n", nome);
            }
        }
    }
    if (recebido){
        printf("%s %s recebeu %d doce(s) das familias.\n", kid.nome, kid.sobrenome, recebido);
    }else{
        printf("%s %s recebeu 10 doces da prefeitura.\n", kid.nome, kid.sobrenome);
    }
}

void comprar(p_hash fams){
    char nome[11];
    int quant;
    scanf(" %s %d", nome, &quant);
    /*to supondo que so familias que estao no sistema estao comprando doces*/
    p_fam fam = buscar(fams, nome);
    fam->doces += quant;
    printf("A familia %s agora possui %d doces.\n", nome, fam->doces);
}

void sair(p_hash hash){
    char nome[11];
    scanf(" %s", nome);
    remover(hash, nome);
}

void entrar(p_hash hash, p_fam familia){
    inserir(hash, familia);
}

int hash(char *nome){
    int i = 0, n = 0;
    while(nome[i] != '\0'){
        n = (256 * n + nome[i]) % MAX;
        i++;
    }
    return n;
}

p_fam buscar(p_hash fams, char nome[]){
    int n = hash(nome);
    int og = n;

    while(fams->familias[n % MAX] != NULL){
        /*se encontrou a familia e ela nao foi removida*/
        if(strcmp(fams->familias[n % MAX]->nome, nome) == 0 && !fams->familias[n % MAX]->removida){
            return fams->familias[n % MAX];
        }
        n++;
        /*cuidado para nao ciclar. se
        voltou pra posicao inicial, sai*/
        if (n % MAX == og) {
            break;
        }
    }
    /*caso nao ache a familia*/
    return NULL;
}

void inserir(p_hash fams, p_fam fam){
    int n = hash(fam->nome);
    int og = n;
    /*busca uma posicao vazia ou com familia removida para inserir*/
    while(fams->familias[n % MAX] != NULL && !fams->familias[n % MAX]->removida){
        n++;
        if (og == n % MAX){
            break;
        }
    }
    /*insere na posicao encontrada*/
    fams->familias[n % MAX] = fam;
}

void remover(p_hash fams, char nome[]){
    p_fam familia = buscar(fams, nome);
    /*marca a familia como removida*/
    if (familia != NULL){
        familia->removida = 1;
    }
    printf("A familia %s saiu com %d doce(s) sobrando.\n", nome, familia->doces);
}

int converter_nota(char nota[]){
    if (strcmp(nota, "Boa") == 0){
        return 3;
    }else if (strcmp(nota, "Media") == 0){
        return 2;
    }
    return 1;
}

void destruir_hash(p_hash fams){
    for (int i = 0; i < MAX; i++){
        free(fams->familias[i]);
    }
    free(fams->familias);
    free(fams);
}
