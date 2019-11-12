#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
//#include "forca.c"
#include "forca.h"

char nome[21];

void copyright(){
    system("clear");
    printf("=============================================================\n");
    printf("JOGO DA FORCA\n");
    printf("Desenvolvido por: \n\t18119 - Alan Vinícius de Souza\n");
    printf("\t18148 - Matheus Carriti Del Rey\n");
    printf("=============================================================\n\n");
}

void menu() {
    int digitado;
    printf("Bem vindo ao jogo da forca!\n\n");

    printf("0. Configuração\n");
    printf("1. Jogar\n");
    printf("2. Sair\n\n");

    fflush(stdin);
    char opcao = getch();


    do {
        switch(opcao) {
        case '0':
            printf("Digite seu nome: ");
            scanf("%s", nome);
            CLEAR_SCREEN;
            break;
        case '2':
            exit(-1);
            break;
        default:
            printf("Digite uma opção!");
            break;
        }
    }while(opcao != '0' && opcao != '1' && opcao != '2');

    CLEAR_SCREEN;



    fflush(stdin);

}

int limpaTela() {
    puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return 0;
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL,"Portugues");
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
    int continuar = 0;
    int testeLetra;
    strcpy(fNameArq,"palavras.dat");



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

    do{
        CLEAR_SCREEN;

        menu();

        sorteada = sorteiaPalavra(lstSecreta);
        if (sorteada == NULL) {
            printf("Nao há palavras disponíveis!\n");
            exit(-1);
        }
        int venceu = 0;

        //insere as letras da palavra sorteada em uma lista
        for (int i=strlen(sorteada->palavra)-0.1; i>=0; i--) {
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
            letra = getch();
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

        if (venceu != 0) {
            CLEAR_SCREEN;
            printf("Voce venceu o jogo!\n");
            system("pause");
        } else {
            CLEAR_SCREEN;
            printf("Incapacidade Intelectual\n");
            system("pause");
        }

        if(lstSecreta!=NULL) {
            lstSecreta = removePalavra(lstSecreta, sorteada->palavra);
            letraPalavra = limpaListaPalavra(letraPalavra);
        } else {
            printf("Não tem palavra disponível!\n\n");
        }

        memset(letrasDigitadas, 0, sizeof(letrasDigitadas));

        CLEAR_SCREEN;

        printf("Voce deseja jogar de novo? (Navegação com \"W\" e \"S\"\")\n\n");

        printf("*Sim\n");
        printf(" Nao\n\n");

        continuar = 1;
        testeLetra = 0;
        do {
            fflush(stdin);
            testeLetra = getch();
            if (testeLetra == 0) {
                testeLetra = getch();
            }
            if (testeLetra == 119 || testeLetra == 87) {
                CLEAR_SCREEN;
                printf("Voce deseja jogar de novo? (Navegação com \"W\" e \"S\"\")\n\n");
                printf("*Sim\n");
                printf(" Nao\n\n");
                continuar = 1;
            } else if (testeLetra == 115 || testeLetra == 83) {
                CLEAR_SCREEN;
                printf("Voce deseja jogar de novo? (Navegação com \"W\" e \"S\"\")\n\n");
                printf(" Sim\n");
                printf("*Nao\n\n");
                continuar = 0;
            }
        }while(testeLetra != 13);
    }while(continuar != 0);


    return 0;
}
