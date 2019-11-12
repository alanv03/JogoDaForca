#ifndef FORCA_H_INCLUDED
#define FORCA_H_INCLUDED

/* defini��o de uma Macro para limpeza do console */
#ifdef _WIN32
# define CLEAR_SCREEN system ("cls")
#else
# define CLEAR_SCREEN puts("\x1b[H\x1b[2J")
#endif

struct noSecreto{
    int status;
    char palavra[31];
    char assunto[101];
    struct noSecreto * prox;
};

struct noLetra {
    char letra;
    int status;
    struct noLetra * prox;
};

typedef struct noSecreto NoSecreto;
typedef struct noSorteada NoSorteada;
typedef struct noLetra NoLetra;

int geraAleatorio(int maximo);
NoSecreto * inicializaListaSecreta();
NoSecreto * carregaListaArquivo(NoSecreto *l, char nomeArq[255]);
void imprimeListaSecreta(NoSecreto *l);
NoSecreto * inserePalavraSecreta(NoSecreto *l,char word[31],char subject[100]);
NoSecreto * sorteiaPalavra(NoSecreto *l);
int temPalavraNaoUsada(NoSecreto *l);
NoSecreto * removePalavra (NoSecreto * l, char palavra[31]);
NoLetra * insereLetra (NoLetra * l, char palavra[31], int pos);
void imprimePalavra (NoLetra * palavra);
void buscaLetra (NoLetra * l, char letra, int tentativas);
int venceuOJogo (NoLetra * l);
NoLetra * limpaListaPalavra (NoLetra * l);
int tamanhoPalavra(NoLetra *l);

//retorna no tamanho da lista, para saber o intervalo de valores para gerar uma posicao
//aleatoria, para sortear uma palavra secreta
int tamanhoListaSecreta(NoSecreto *l);

//retorna a palavra que esteja em uma dada posi��o na lista de palavras secretas
NoSecreto * retornaPalavraPos(NoSecreto *l, int pos);

#endif // FORCA_H_INCLUDED
