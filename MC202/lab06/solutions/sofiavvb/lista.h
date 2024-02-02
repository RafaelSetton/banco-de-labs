typedef struct lista_ligada *p_lista;
typedef struct no *p_no;

struct lista_ligada{
    p_no inicio, fim;
};

struct no{
    char livro[45];
    p_no ant, prox;
};
//constroi a lista ligada
p_lista criar_lista();
//destroi os nós
void destruir(p_no lista);
//organiza a entrada, separa o comando e o livro
void separar_entrada(char entrada[], char comando[], char livro[]);
//adiciona o livro na lista de leitura, retorna o livro adicionado
p_no adicionar(p_lista lista, char livro[], int *inicio, int *fim, p_no ultimo);
//imprime a lista na ordem de prioridade correta
void imprimir(p_lista lista);
//busca o livro na lista e o retorna
p_no busca(p_lista lista, char livro[]);
//remove um livro da lista
void remover(p_lista lista, char livro[], p_no ultimo, int *inicio, int *final);