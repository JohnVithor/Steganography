#ifndef STEG_H
#define STEG_H
#include "structs.h"
#include <stdio.h>

void abreImgPPM(char *nomeImg, imgPPM *imagemLida);

void salvaImgPPM(char *nomeImg, imgPPM *imagemLida);

/////////////////////////////////////////////////

void lerHeaderBMP(imgBMP *imagemLida, FILE* arqEntrada);

void lerInfoBMP(imgBMP *imagemLida, FILE* arqEntrada);

void escreverHeaderBMP(imgBMP *imagemLida, FILE* arqSaida);

void escreverInfoBMP(imgBMP *imagemLida, FILE* arqSaida);

void abreImgBMP(char *nomeImg, imgBMP *imagemLida);

void salvaImgBMP(char *nomeImg, imgBMP *imagemLida);

/////////////////////////////////////////////////

char* abreMsg(char *nomeMsg, unsigned long *tamanhoMsg);

void salvaMsg(char *nomeMsg, char *mensagem);

void escondeChar(char caractere, pixel** pixelMap, int largura, int *i, int *j);

char descobreChar(pixel** pixelMap, int largura, int i, int j);

void adicionaChar(char *mensagem, char c);

int escondeMsgPPM(char *mensagem, int tamanhoDaMsg, imgPPM *imagemLida);

int descobreMsgPPM(char *mensagem, imgPPM *imagemLida);

#endif