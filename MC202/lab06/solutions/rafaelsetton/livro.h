struct livro
{
    char nome[60];
    struct livro *prox;
};

typedef struct livro *p_livro;

void imprime(p_livro l, int virgula);