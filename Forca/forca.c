#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forca.h"

//gera um numero aleatorio entre 1 e 'maximo'
int geraAleatorio(int maximo)
{
    time_t t;
    int n=0;
    srand((unsigned) time(&t));
    n = (rand() % maximo)+1;
    return n;
}

NoSecreto * inicializaListaSecreta()
{
    return NULL;
}

NoSecreto * inserePalavraSecreta(NoSecreto *l,char word[31],char subject[100])
{
    NoSecreto * novo;
    novo = (NoSecreto *) malloc(sizeof(NoSecreto));
    novo->status=0;
    strcpy(novo->assunto,subject);
    strcpy(novo->palavra,word);
    novo->prox = l;
    l=novo;
    return l;
}

void imprimeListaSecreta(NoSecreto *l)
{
    for(NoSecreto *p=l; p!=NULL; p=p->prox)
    {
        printf("%d) %-30s\t%s\n", p->status,p->palavra,p->assunto);
    }
}

NoSecreto * carregaListaArquivo(NoSecreto * l, char nomeArq[255])
{
    const char ch[2]=";";
    char * token;
    int status;
    char palavra[31];
    char assunto[101];
    char * linha[1024];
    FILE * fWords;

    fWords = fopen(nomeArq,"r");
    if(fWords==NULL){
        printf("Falha ao acessar base de dados!!!\n\n");
        exit(0);
    }
    while(fgets(linha,1024,fWords))
    {
        token = strtok(linha,ch);
        if(token!=NULL)
        {
             strcpy(palavra,token);
        }
        token=strtok(NULL,ch);
        if(token!=NULL)
        {
            strcpy(assunto,token);
        }
        l = inserePalavraSecreta(l,palavra, assunto);
    }

    fclose(fWords);
    return l;
}

//
int tamanhoListaSecreta(NoSecreto *l)
{
    int n=0;
    for(NoSecreto *p=l;p!=NULL;p=p->prox,n++);
    return n;
}

int temPalavraNaoUsada(NoSecreto *l)
{
    NoSecreto *p;
    for(p=l;p!=NULL;p=p->prox){
        if(p->status==0) return 1;
    }
    return 0;
}

NoSecreto * sorteiaPalavra(NoSecreto *l)
{
    int tam = tamanhoListaSecreta(l);
    int aleatorio=0;
    int tentativas = 0;
    NoSecreto * p;

    while(temPalavraNaoUsada(l)){
        aleatorio = geraAleatorio(tam);
        p = retornaPalavraPos(l,aleatorio);
        if(p->status==0){
            p->status = 1;
            return p;
        }
    }
    return NULL;
}

//retorna a palavra que está na posicao 'pos' da lisata secreta
NoSecreto * retornaPalavraPos(NoSecreto *l, int pos)
{
    int n=1;
    NoSecreto *p;
    for(p=l; p!=NULL; p=p->prox)
    {
        if(n==pos) break;
        n++;
    }
    return p;
}


//remove a palavra que já foi sorteada da lista principal
NoSecreto * removePalavra (NoSecreto * l, char palavra[31]) {
    NoSecreto * aux = (NoSecreto*)malloc(sizeof(NoSecreto));
    NoSecreto * anterior = (NoSecreto*)malloc(sizeof(NoSecreto));

    for (aux = l; aux != NULL; aux = aux->prox) {
        if ((aux == l) && (palavra == l->palavra)) {
            l = aux->prox;
            free(aux);
            return l;
        } else if (palavra == aux->palavra) {
            anterior->prox = aux->prox;
            free (aux);
            return l;
        }
        anterior = aux;
    }
    return l;
}

NoLetra * insereLetra (NoLetra * l, char palavra[31], int pos) {
    NoLetra * novo;
    novo = (NoLetra *) malloc(sizeof(NoLetra));
    novo->status = 0;
    novo->letra = palavra[pos];
    novo->prox = l;
    l = novo;

    return l;
}

void imprimePalavra (NoLetra * palavra) {
    NoLetra * aux;
    aux = (NoLetra *) malloc(sizeof(NoLetra));

    printf("\n\n");

    for (aux = palavra; aux!=NULL; aux = aux->prox) {
        if (aux->status == 1) {
            printf("%c ", aux->letra);
        } else {
            printf("_ ");
        }
    }

    printf("\n\n");
}

void buscaLetra (NoLetra * l, char letra, int tentativas) {
    NoLetra * aux;
    aux = (NoLetra *) malloc(sizeof(NoLetra));
    int encontrou = 0;

    for (aux = l; aux!=NULL; aux = aux->prox) {
        if (aux->letra == letra) {
            aux->status = 1;
            encontrou = 1;
        }
    }
}

int venceuOJogo (NoLetra * l) {
    NoLetra * aux;
    int venceu = 1;
    aux = (NoSecreto *) malloc(sizeof(NoLetra));

    for (aux = l; aux != NULL; aux = aux->prox) {
        if (aux->status == 0) {
            venceu = 0;
            return venceu;
        }
    }

    return venceu;
}

NoLetra * limpaListaPalavra (NoLetra * l) {
    NoLetra * aux, * no = l;
    aux = (NoLetra *) malloc(sizeof(NoLetra));

    if (l == NULL) return NULL;

    for (aux = l; aux != NULL; aux = aux->prox) {
        no = aux->prox;
        free(aux);
        aux = no;
    }
    l = NULL;

    return l;
}

int tamanhoPalavra(NoLetra *l) {
    NoLetra * aux = (NoLetra *) malloc(sizeof(NoLetra));
    int n = 0;

    for (aux = l; aux != NULL; aux = aux->prox, n++) {}

    return n;
}
