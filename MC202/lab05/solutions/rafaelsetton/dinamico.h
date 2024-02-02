typedef struct
{
    int alocado;
    int ocupado;
    int *v;
    int *inicios;
} dinamico;

dinamico novo_vetor_dinamico(); // Cria um novo vetor dinâmico com 8 espaços

void aumenta(dinamico *vetor); // Dobra o tamanho do vetor, mantendo os dados antigos

void otimiza(dinamico *vetor); // Verifica se menos de um quarto do vetor está ocupado e, se este for o caso, reduz seu tamanho pela metade

int encontra(dinamico *vetor, int tamanho); // Retorna a primeira posição para armazenar um vetor de tamanho "tamanho" ou -1 se não houver

void libera(dinamico *vetor, int endereco); // Libera a sequencia armazenada a partir da posição "endereço"

void insere(dinamico *vetor, int posicao, int tamanho, int *valores); // Insere uma sequencia de dados na posição "posição"