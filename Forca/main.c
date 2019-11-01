#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
//#include "forca.c"
#include "forca.h"

void copyright(){
    system("clear");
    printf("=============================================================\n");
    printf("JOGO DA FORCA\n");
    printf("Desenvolvido por: \n\t18119 - Alan Vinícius de Souza\n");
    printf("\t18148 - Matheus Carriti Del Rey\n");
    printf("=============================================================\n\n");
}

/*void menu() {
    int digitado;
    printf("Bem vindo ao jogo da forca!\n\n");

    printf("Jogar (1)\t\tSair (0)\n");

    fflush(stdin);

    do {
        digitado = getchar();

        if (digitado == 0) {
            CLEAR_SCREEN;
        }

    } while(digitado != 10);
}

int limpaTela() {
    puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return 0;
}*/

int main(int argc, char *argv[]) {
    NoSecreto * lstSecreta = inicializaListaSecreta();
    NoLetra * letraPalavra = inicializaListaSecreta();
    char fNameArq[255];
    char letra;
    char letrasDigitadas [101] = "";
    char nome[21];
    NoSecreto * sorteada;
    int posSorteada=0;
    int tamanhoLista=0;
    int acertou = 0;
    int tentativas;
    strcpy(fNameArq,"palavras.dat");

    setlocale(LC_ALL, "Portuguese");

    if(argc>1){
      strcpy(fNameArq,argv[1]);
    }

    printf("Arquivo de dados: %s\n\n",fNameArq);

    copyright();
    printf("Pressione qualquer tecla para continuar...");
    getch();

    lstSecreta = carregaListaArquivo(lstSecreta,fNameArq);
    imprimeListaSecreta(lstSecreta);
    tamanhoLista = tamanhoListaSecreta(lstSecreta);

    //do{
        CLEAR_SCREEN;

        /*printf("Digite seu nome: ");
        scanf("%s", &nome);
        printf("Seja bem-vindo, %s!\n\n", nome);
        printf("Pressione qualquer tecla para continuar...");
        getch();*/

        sorteada = sorteiaPalavra(lstSecreta);
        int venceu = 0;

        //insere as letras da palavra sorteada em uma lista
        for (int i=strlen(sorteada->palavra)-1; i>=0; i--) {
            letraPalavra = insereLetra(letraPalavra, sorteada->palavra, i);
        }

        tentativas = tamanhoPalavra(letraPalavra)*3;
        fflush(stdin);

        do {
            CLEAR_SCREEN;
            printf("Letras digitadas: ");
            for (int i=0; i<strlen(letrasDigitadas); i++) {
                printf("%c ", letrasDigitadas[i]);
            }
            printf("\nAssunto: %s\n", sorteada->assunto);
            printf("Voce tem %d tentativas restantes", tentativas);
            imprimePalavra(letraPalavra);
            printf("\n\nDigite uma letra: ");
            letra = getchar();
            fflush(stdin);
            int teste = 0;
            for (int i=0; i<strlen(letrasDigitadas); i++) {
                if (letra == letrasDigitadas[i]) {
                    teste = 1;
                    break;
                }
            }

            if (teste == 0) {
                letrasDigitadas[strlen(letrasDigitadas)] = letra;
                buscaLetra(letraPalavra, letra, tentativas);
                CLEAR_SCREEN;
                imprimePalavra(letraPalavra);

                tentativas--;
                venceu = venceuOJogo(letraPalavra);
            }
        } while((venceu==0) && (tentativas>0));

        if (venceu == 1) {
            CLEAR_SCREEN;
            printf("Voce venceu o jogo!\n", nome);
            //printf("Pressione qualquer tecla para continuar...\n");
            getchar();
        } else {
            CLEAR_SCREEN;
            printf("Incapacidade Intelectual\n");
            //printf("Pressione qualquer tecla para continuar...\n");
            getchar();
        }

        if(sorteada!=NULL){
            lstSecreta = removePalavra(lstSecreta, sorteada->palavra);
            letraPalavra = limpaListaPalavra(letraPalavra);
        }else{
            printf("Não tem palavra disponível!\n\n");
        }

        for (int i=0; i<strlen(letrasDigitadas); i++) {
            letrasDigitadas[i] = "";
        }
    //}while(loop<1);


    return 0;
}
