#ifndef _FOGE_H_
#define _FOGE_H_

#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define BOMBA 'b'

int acabou();
void move(char direcao);
int ehdirecao(char direcao);
void fantasmas();
void fantasmas();
int pra_onde_o_fantasma_vai(int xatual, int yatual, int* xdestino, int* ydestino);
void explodepilula();
void explodepilula2(int x, int y, int somax, int somay, int qtd);

#endif