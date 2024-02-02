#define MAX 1783

typedef struct hash *p_hash;
typedef struct familia *p_familia;

struct familia
{
    char sobrenome[10];
    int qtd_doces;
};

struct hash
{
    p_familia vetor[MAX];
    int utilizado[MAX];
};

p_hash criar_hash();

void destruir_hash(p_hash t);

void inserir(p_hash t, char *sobrenome, int qtd_doces);

void remover(p_hash t, char *sobrenome);

p_familia buscar(p_hash t, char *sobrenome);
