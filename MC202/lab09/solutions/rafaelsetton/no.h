typedef struct node *p_no;

enum cor
{
    VERMELHO,
    PRETO
};

struct node
{
    char simbolo[200];
    char tipo[20];
    enum cor cor;
    p_no dir, esq;
};

p_no inserir(p_no raiz, char simbolo[], char tipo[]);

void imprimir(p_no raiz);

p_no buscar(p_no raiz, char simbolo[]);

void destroi(p_no raiz);
