#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "forca.h"

char palavrasecreta[TAM];
char chutes[26];
int chutes_dados = 0;


void abertura(){
    printf("***********************\n");
    printf("*    Jogo da Forca    *\n");
    printf("***********************\n\n");
}

void adicionapalavra(){ 

    char quer;

    printf("Voce gostaria de adicionar uma nova palavra no jogo? (S/N)");
    scanf(" %c",&quer);

    if(quer == 'S'){

        char novapalavra[TAM];
        printf("Qual a nova palavra?");
        scanf("%s",&novapalavra);

        FILE* f;

        f = fopen("C:\\Users\\User\\Desktop\\coisas da vida\\EXERCICIOS EM C\\Alura\\FORCA\\palavra.txt","r+");

        if(f == NULL){
            printf("Erro na leitura 2.0");
            system("pause");
            exit(1);
        }

        int qtd;
        fscanf(f,"%d",&qtd);
        qtd++;

        fseek(f,0,SEEK_SET);
        fprintf(f,"%d",qtd);
        
        fseek(f,0,SEEK_END);
        fprintf(f,"\n%s",novapalavra);
        fclose(f);
    }
}

void ecolhepalavra(){
    FILE* f;

    f = fopen("C:\\Users\\User\\Desktop\\coisas da vida\\EXERCICIOS EM C\\Alura\\FORCA\\palavra.txt ","r");

    if(f == NULL){
        printf("Erro na leitura\n");
        system("pause");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f,"%d",&qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++){
        fscanf(f,"%s",palavrasecreta);
    }


    fclose(f);
}

void chuta(){
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    chutes[chutes_dados] = chute;
    chutes_dados++;

}

int jachutou(char palavrasecreta[TAM]){
    int achou = 0;

        for(int j = 0; j < chutes_dados; j++) {
            if(chutes[j] == palavrasecreta) {
                achou = 1;
                break;
            }
        }
     return achou;
}

void desenhaforca(){

    int erros = chutes_errados();

    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %s     \n",(erros >= 1 ? "(_)" : " "));
    printf(" |      %c%c%c  \n",(erros >= 3 ? '\\' : ' '),(erros >= 2 ? '|' : ' '),(erros >= 4 ? '/' : ' '));
    printf(" |       %c     \n",(erros >= 5 ? '|' : ' '));
    printf(" |      %c %c   \n",(erros >= 6 ? '/' : ' '),(erros >= 7 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");

    for(int i = 0; i < strlen(palavrasecreta); i++) {

        int achou = jachutou(palavrasecreta[i]);

        if(achou) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int chutes_errados ()
{
    int erros = 0;
    for(int i = 0; i < chutes_dados; i++) {
        int existe = 0;
        for(int j = 0; j < strlen(palavrasecreta); j++) {
            if(chutes[i] == palavrasecreta[j]) {

                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }
    return erros;    
}

int acertou(){
    for(int i = 0; i < strlen(palavrasecreta); i++){
        if(!jachutou(palavrasecreta[i])){
            return 0;
        }
    }
    return 1;
}

int main() {

    setlocale(LC_ALL, "Portuguese");

    ecolhepalavra();

    abertura();

do {

      desenhaforca(palavrasecreta);
      chuta();

    } while (!acertou() && !enforcou());
    
    if(acertou())
    {
        printf("PARABENS!!! Voce ganhou!\n\n");

        printf("        ___________   \n");
        printf("       '._==_==_=_.'  \n");
        printf("       .-\\:      /-. \n");
        printf("      | (|:.     |) | \n");
        printf("       '-|:.     |-'  \n");
        printf("         \\::.    /   \n");
        printf("          '::. .'     \n");
        printf("            ) (       \n");
        printf("          _.' '._     \n");
        printf("         '-------'    \n\n");
    }else
    {
        printf("Voce foi enforcado!\n");
        printf("A palavra secreta era: %s\n\n",palavrasecreta);

        printf("    _______________         \n");
        printf("   /               \\      \n"); 
        printf("  /                 \\     \n");
        printf("//                   \\/\\ \n");
        printf("\\|   XXXX     XXXX   | /  \n");
        printf(" |   XXXX     XXXX   |/    \n");
        printf(" |   XXX       XXX   |     \n");
        printf(" |                   |     \n");
        printf(" \\__      XXX      __/    \n");
        printf("   |\\     XXX     /|      \n");
        printf("   | |           | |       \n");
        printf("   | I I I I I I I |       \n");
        printf("   |  I I I I I I  |       \n");
        printf("   \\_             _/      \n");
        printf("     \\_         _/        \n");
        printf("       \\_______/          \n\n");
    }

    adicionapalavra();

}

int enforcou() {
    return chutes_errados() >= 8;
}
