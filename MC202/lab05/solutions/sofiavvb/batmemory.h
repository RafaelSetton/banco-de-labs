typedef struct vetor *p_vetor;

struct vetor{
    int *dados;
    int uso, alocado, bat_uso;
};
/*cria o vetor e instancia os seus campos*/
p_vetor criar_vetor(int tam);
/*destroi o vetor liberando o que foi alocado*/
void destruir_vetor(p_vetor v);
/*atualiza o uso da batmemory*/
void atualiza_batuso(p_vetor batmemory, int tamanho);
/*printa o quanto da batmemory esta sendo usada*/
void bat_uso(p_vetor batmemory);
/*dobra o tamanho do vetor*/
void dobrar(p_vetor v);
/*reduz o tamanho do vetor na metade*/
void reduzir(p_vetor v);
/*realiza a operacao de bat-alloc*/
void bat_alloc(p_vetor batmemory, p_vetor inicios);
/*printa o vetor que foi alocado na batmemory*/
void bat_print(p_vetor batmemory, p_vetor inicios);
/*libera um vetor alocado na batmemory*/
void bat_free(p_vetor batmemory, p_vetor inicios);
/*busca sequencial no vetor, retorna o indice do elemento
ou -1 se nao achou*/
int busca(p_vetor v, int x);
/*remove um elemento dado um indice do vetor*/
void remover_elemento(p_vetor v, int index);
/*checa os espaços continuos que tem para alocar vetores na batmemoria,
retorna o endereco, se achou. retorna -1 se nao tem espaço continuo pra
alocar*/
int checar_espaco(p_vetor batmemory, p_vetor inicios, int tamanho);