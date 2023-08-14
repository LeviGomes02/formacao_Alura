#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "foge.h"
#include "mapa.c"
#include "ui.c"
#include "ui.h"

MAPA m;
POSICAO heroi;

int tempilula = 0;

int pra_onde_o_fantasma_vai(int xatual, int yatual, int* xdestino, int* ydestino)
{
    int opcoes[4][2] = {
        {xatual, yatual + 1},
        {xatual + 1, yatual},
        {xatual, yatual - 1},
        {xatual - 1, yatual}
    };

    srand(time(0));
    for(int i = 0; i < 10; i++)
    {
        int posicao = rand() % 4;
        if(podeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1]))
        {
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];
            
            return 1;
        }

    }   
    return 0;
}

void fantasmas()
{
    MAPA copia;

    copiamapa(&copia, &m);

    for(int i = 0 ; i < copia.linhas; i++)
    {
        for(int j = 0; j < copia.colunas; j++)
        {
            if(copia.matriz[i][j] == FANTASMA)
            {
                int xdestino,ydestino;

                int encontrou = pra_onde_o_fantasma_vai(i, j, &xdestino, &ydestino);

                if(encontrou)
                {
                    andandomapa(&m, i, j, xdestino, ydestino);
                }
            }
        }
    }
    liberamapa(&copia);
}

int acabou()
{
    POSICAO pos;
    int fogefogenomapa = encontramapa(&m, &pos, HEROI);
    return !fogefogenomapa;
}

int ehdirecao(char direcao)
{
       return direcao == CIMA ||
        direcao == ESQUERDA ||
        direcao == BAIXO ||
        direcao == DIREITA;
}

void move(char direcao)
{
    if(!ehdirecao(direcao))
        return;

   int proximox = heroi.x;
   int proximoy = heroi.y;

    switch(direcao)
    {
        //direita
        case ESQUERDA:
           proximoy--;
            break;
        //esquerda
        case DIREITA:
            proximoy++;
            break;
        //cima
        case CIMA:
            proximox--;
            break;
        //baixo
        case BAIXO:
            proximox++;
            break;        
    }

    if(!podeandar(&m, HEROI, proximox, proximoy))
        return;
    
    if(!podeandar(&m, PILULA, proximox, proximoy))
    {
        tempilula = 1;
    }

    andandomapa(&m, heroi.x, heroi.y, proximox, proximoy);
    heroi.x = proximox;
    heroi.y = proximoy;
}

void explodepilula()
{
    if(!tempilula) return;

    explodepilula2(heroi.x,heroi.y,0,1,3);
    explodepilula2(heroi.x,heroi.y,0,-1,3);
    explodepilula2(heroi.x,heroi.y,1,0,3);
    explodepilula2(heroi.x,heroi.y,-1,0,3);

    tempilula = 0;
}

void explodepilula2(int x, int y, int somax, int somay, int qtd)
{  
    int novox = x + somax;
    int novoy = y + somay;

    if(qtd == 0) return; 
    if(!ehvalida(&m, novox, novoy)) return;
    if(ehparede(&m, novox, novoy)) return;

    m.matriz[novox][novoy] = VAZIO;
    explodepilula2(novox, novoy, somax, somay, qtd - 1);       
}

int main()
{
    setlocale(LC_ALL, "");

    lermapa(&m);
    encontramapa(&m, &heroi, HEROI);

    do
    {
        printf("Tem pilula: %s\n",(tempilula ? "SIM" : "NAO"));
        imprimemapa(&m);
        char comando;
        scanf(" %c", &comando);
        move(comando);
        if(comando == BOMBA) explodepilula();
        fantasmas();

    } while (!acabou());
    
    
    liberamapa(&m);

    system("pause");
    return 0;
}