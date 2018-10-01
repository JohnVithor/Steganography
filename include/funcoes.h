#ifndef STEG_H
#define STEG_H
#include "structs.h"
#include <stdio.h>

void abreImgPPM(char *nomeImg, imgPPM *imagemLida);

void salvaImgPPM(char *nomeImg, imgPPM *imagemLida);

int escondeMsgPPM(char *mensagem, int tamanhoDaMsg, imgPPM *imagemLida);

int descobreMsgPPM(char saida, imgPPM *imagemLida, char *arquivoTexto);

/////////////////////////////////////////////////

void lerHeaderBMP(imgBMP *imagemLida, FILE* arqEntrada);

void lerInfoBMP(imgBMP *imagemLida, FILE* arqEntrada);

void escreverHeaderBMP(imgBMP *imagemLida, FILE* arqSaida);

void escreverInfoBMP(imgBMP *imagemLida, FILE* arqSaida);

void abreImgBMP(char *nomeImg, imgBMP *imagemLida);

void salvaImgBMP(char *nomeImg, imgBMP *imagemLida);

int escondeMsgBMP(char *mensagem, int tamanhoDaMsg, imgBMP *imagemLida);

int descobreMsgBMP(char saida, imgBMP *imagemLida, char *arquivoTexto);

/////////////////////////////////////////////////

char* abreMsg(char *nomeMsg, unsigned long *tamanhoMsg);

void salvaChar(FILE *arqSaida, char caractere);

void escondeChar(unsigned char char_esconder, pixel** pixelMap, int largura, int *i, int *j);

unsigned char descobreChar(pixel** pixelMap, int largura, int *i, int *j);

#endif