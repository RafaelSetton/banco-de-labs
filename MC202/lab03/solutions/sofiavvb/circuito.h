//interface
typedef struct circuito{
    int identificacao, participantes;
    int *jogadas;
}circuito;

int acha_dificil(circuito *circuitos, int n_circuitos);

circuito *aloca_circuitos(int n_circuitos);

circuito ler_circuito(int participantes);

int *aloca_jogadas(int participantes);

void libera_jogadas(int *jogadas);